# 3DS ADV Generator

3DSで遊べるADVゲームを直感的に作成できるツールです。シナリオをJSON形式で定義するだけで、自動的にC言語コードを生成し、devkitProでコンパイルして3DSXファイルを生成できます。

## 🎮 機能

- **直感的なシナリオエディタ**: JSON形式でゲームシナリオを定義
- **自動C言語生成**: シナリオからC言語ソースコードを自動生成
- **devkitPro統合**: ワンコマンドでビルド＆3DSX生成
- **キャラクター・背景管理**: スプライトシステム対応
- **分岐ストーリー**: 複数のエンディングに対応
- **BGM・効果音**: オーディオシステム統合
- **UIシステム**: メニュー・選択肢・ダイアログ表示

## 📋 プロジェクト構成

```
3DS-ADV-Generator/
├── adv-tool/                 # メインツール
│   ├── src/
│   │   ├── main.c           # ツールのメインプログラム
│   │   ├── generator.c      # C言語コード生成エンジン
│   │   ├── json_parser.c    # JSON解析
│   │   └── file_utils.c     # ファイル操作ユーティリティ
│   ├── include/
│   │   ├── generator.h
│   │   ├── json_parser.h
│   │   └── file_utils.h
│   └── Makefile
├── templates/               # C言語テンプレート
│   ├── base_game.c         # ゲームベーステンプレート
│   ├── ui_system.h         # UIシステムヘッダ
│   └── game_structs.h      # ゲーム構造体定義
├── examples/               # サンプルプロジェクト
│   ├── simple_story/
│   │   ├── story.json      # シナリオ定義
│   │   ├── assets/
│   │   │   ├── sprites/
│   │   │   ├── backgrounds/
│   │   │   └── sounds/
│   │   └── Makefile        # 生成されたMakefile
│   └── branching_story/
├── docs/                   # ドキュメント
│   ├── tutorial.md         # チュートリアル
│   ├── json_format.md      # JSON形式仕様
│   └── devkit_setup.md     # devkitPro セットアップ
└── scripts/                # ビルドスクリプト
    ├── build.sh            # ビルドスクリプト
    └── clean.sh            # クリーンスクリプト
```

## 🚀 クイックスタート

### 1. devkitProのセットアップ

```bash
# devkitPro をインストール
# https://devkitpro.org/wiki/Getting_Started

# 環境変数の設定
export DEVKITPRO=/opt/devkitpro
export PATH=$DEVKITPRO/tools/bin:$PATH
```

### 2. ADVツールのビルド

```bash
cd adv-tool
make
```

### 3. シナリオを定義

`story.json` を作成:

```json
{
  "title": "My First ADV",
  "version": "1.0.0",
  "characters": [
    {
      "id": "heroine",
      "name": "ヒロイン",
      "sprite": "assets/sprites/heroine.png"
    }
  ],
  "scenes": [
    {
      "id": "scene_1",
      "background": "assets/bg/classroom.png",
      "dialogs": [
        {
          "character": "heroine",
          "text": "おはよう！"
        }
      ]
    }
  ]
}
```

### 4. C言語コード生成

```bash
./adv-tool generate story.json -o game_src/
```

### 5. ビルド＆実行

```bash
cd game_src/
make
# game.3dsx が生成されます
```

## 📖 JSON形式仕様

シナリオJSONの完全な仕様は [json_format.md](docs/json_format.md) を参照してください。

## 🔧 使用技術

- **C言語**: ゲーム本体とツール
- **devkitPro**: 3DS開発
- **libctru**: 3DS標準ライブラリ
- **JSON**: シナリオ定義

## 📝 ライセンス

MIT License
