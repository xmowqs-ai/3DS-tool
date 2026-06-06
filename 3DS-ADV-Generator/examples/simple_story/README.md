# Simple Story Example

3DS ADV Generator の最も簡単なサンプルプロジェクトです。

## 概要

このプロジェクトは、主人公とヒロインの簡単なストーリーを実装しています。

### ストーリー概要

1. **オープニング**: 学校で主人公とヒロインが出会う
2. **選択肢**: プレイヤーが「勉強する」か「遊ぶ」か選択
3. **エンディング**: 選択に応じた2つのエンディング

## セットアップ

### 1. アセットの準備

以下のディレクトリを作成し、必要な画像ファイルを配置してください：

```
assets/
├── sprites/
│   ├── protagonist.png (200x240px)
│   └── heroine.png (200x240px)
└── backgrounds/
    ├── school.png (320x240px)
    ├── library.png (320x240px)
    └── park.png (320x240px)
```

### 2. コード生成

```bash
cd ..
../../../adv-tool/bin/adv-tool generate simple_story/story.json -o simple_story/game_src
```

### 3. ビルド

```bash
cd game_src
make
```

## 運用

### エミュレータで実行 (Citra)

```bash
citra-qt game.3dsx
```

### 実機で実行

1. `game.3dsx` を3DSのSDカード `/3ds/` フォルダにコピー
2. Homebrew Launcher で実行

## カスタマイズ

### ストーリーの編集

`story.json` を編集してストーリーを変更できます：

- **キャラクター追加**: `characters` 配列に新しいキャラを追加
- **シーン追加**: `scenes` 配列に新しいシーンを追加
- **選択肢変更**: `choices` 配列を編集

### 画像の変更

`assets/` フォルダ内の画像ファイルを置き換えることで、ビジュアルを変更できます。

## トラブルシューティング

### 画像が表示されない場合

- ファイルパスが正しいか確認
- 画像形式がPNGであることを確認
- ファイルサイズが大きすぎないか確認

### テキストが文字化けする場合

- `story.json` がUTF-8で保存されているか確認

## 次のステップ

- より複雑なストーリーを作成
- キャラクターボイスを追加
- BGMを追加
- より複雑な分岐ストーリーを実装
