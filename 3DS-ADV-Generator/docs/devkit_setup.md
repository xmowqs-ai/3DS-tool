# devkitPro セットアップガイド

## 概要

devkitProは、ニンテンドー3DS向けのホームブリュゲーム開発キットです。このガイドでは、3DS ADV Generatorで使用するためのセットアップ手順を説明します。

## システム要件

- **Linux**: Ubuntu 18.04以上、または他の主流なディストリビューション
- **macOS**: 10.13以上
- **Windows**: Windows 10以上 (WSL2推奨)
- **ディスク容量**: 最小5GB

## インストール手順

### Linux (Ubuntu/Debian)

```bash
# パッケージマネージャーを更新
sudo apt-get update
sudo apt-get upgrade

# 必要なツールをインストール
sudo apt-get install -y \
    git \
    build-essential \
    libssl-dev \
    libffi-dev \
    python3 \
    python3-dev \
    wget

# devkitProをダウンロード
wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.2/devkitpro-pacman.deb

# インストール
sudo dpkg -i devkitpro-pacman.deb

# 3DS開発ツールをインストール
sudo dkp-pacman -S 3ds-dev
```

### macOS

```bash
# Homebrewをインストール (未インストール時)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# devkitProをインストール
brew install devkitpro/devkitpro/devkitarm
brew install devkitpro/devkitpro/3ds-dev
```

### Windows (WSL2)

```bash
# WSL2を有効化（管理者PowerShellで実行）
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# Ubuntu 20.04 LTSをインストール
# Microsoft Storeから "Ubuntu" をインストール

# WSL2内でLinux手順を実行
```

## 環境変数の設定

### Linux/macOS

`.bashrc` または `.zshrc` に以下を追加:

```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export PATH=$DEVKITPRO/tools/bin:$PATH
```

シェルを再起動:

```bash
source ~/.bashrc  # Bash
# または
source ~/.zshrc   # Zsh
```

### Windows (WSL2)

WSL2内で上記のLinux手順を実行してください。

## インストール確認

```bash
# arm-none-eabiが使用可能か確認
arm-none-eabi-gcc --version

# makeが使用可能か確認
make --version

# 3dsxtoolが使用可能か確認
3dsxtool --version
```

## 3DS開発ツール

### 3dsxtool

ELFファイルを3DSX形式に変換します:

```bash
3dsxtool input.elf output.3dsx
```

### Makerom

ROMファイルを生成します:

```bash
makerom -f cxi -o output.cxi -DAPP_ENCRYPTED=false input.elf
```

## トラブルシューティング

### 環境変数が見つからない

```bash
# 環境変数を確認
echo $DEVKITPRO

# 正しく設定されているか確認
ls $DEVKITPRO
```

### arm-none-eabi-gccが見つからない

```bash
# パスを確認
which arm-none-eabi-gcc

# または手動でパスを設定
export PATH=$DEVKITPRO/devkitARM/bin:$PATH
```

### ビルドエラー

```bash
# devkitProを最新に更新
sudo dkp-pacman -Syu

# 3DS開発ツールを再インストール
sudo dkp-pacman -S 3ds-dev --overwrite '*'
```

## サンプルプロジェクトのビルド

```bash
# devkitProのサンプルを入手
git clone https://github.com/devkitPro/3ds_examples.git

# サンプルをビルド
cd 3ds_examples/hello_world
make

# 3DSXファイルが生成されたか確認
ls -la hello_world.3dsx
```

## リソース

- **公式サイト**: https://devkitpro.org/
- **ドキュメント**: https://devkitpro.org/wiki/
- **GitHub**: https://github.com/devkitPro
- **フォーラム**: https://devkitpro.org/forum/
