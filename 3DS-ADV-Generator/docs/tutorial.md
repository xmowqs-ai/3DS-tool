# 3DS ADV Generator チュートリアル

## ステップ1: 簡単なシナリオを作成

### 1-1. プロジェクトフォルダを作成

```bash
mkdir my_first_adv
cd my_first_adv
mkdir assets/sprites assets/backgrounds assets/sounds
```

### 1-2. story.json を作成

`story.json`:

```json
{
  "title": "My First Adventure",
  "version": "1.0.0",
  "author": "Your Name",
  "screen_width": 320,
  "screen_height": 240,
  "characters": [
    {
      "id": "protagonist",
      "name": "主人公",
      "sprite": "assets/sprites/protagonist.png"
    },
    {
      "id": "friend",
      "name": "友人",
      "sprite": "assets/sprites/friend.png"
    }
  ],
  "scenes": [
    {
      "id": "opening",
      "background": "assets/backgrounds/school.png",
      "dialogs": [
        {
          "character": "protagonist",
          "text": "おはよう！今日も学校か。"
        },
        {
          "character": "friend",
          "text": "よ！今日は何か面白いことあるかな？"
        }
      ]
    },
    {
      "id": "choice_scene",
      "background": "assets/backgrounds/school.png",
      "dialogs": [
        {
          "character": "protagonist",
          "text": "どうしよう...？"
        }
      ],
      "choices": [
        {
          "id": "study_choice",
          "text": "勉強する",
          "next_scene": "study_end"
        },
        {
          "id": "play_choice",
          "text": "遊ぶ",
          "next_scene": "play_end"
        }
      ]
    },
    {
      "id": "study_end",
      "background": "assets/backgrounds/library.png",
      "dialogs": [
        {
          "character": "protagonist",
          "text": "勉強頑張った！テストで良い点が取れそうだ。"
        }
      ]
    },
    {
      "id": "play_end",
      "background": "assets/backgrounds/park.png",
      "dialogs": [
        {
          "character": "protagonist",
          "text": "楽しかった！でもテストが心配だ..."
        }
      ]
    }
  ]
}
```

## ステップ2: 画像アセットを準備

### 必要なファイル:

1. `assets/sprites/protagonist.png` - 主人公のキャラクター画像
2. `assets/sprites/friend.png` - 友人のキャラクター画像
3. `assets/backgrounds/school.png` - 学校の背景画像
4. `assets/backgrounds/library.png` - 図書館の背景画像
5. `assets/backgrounds/park.png` - 公園の背景画像

推奨サイズ:
- スプライト: 200x240px
- 背景: 320x240px
- 形式: PNG

## ステップ3: コード生成

```bash
# adv-toolのビルド (初回のみ)
cd ../3DS-ADV-Generator/adv-tool
make
cd ../../my_first_adv

# C言語コード生成
../3DS-ADV-Generator/adv-tool/bin/adv-tool generate story.json -o game_src
```

## ステップ4: ビルド

```bash
cd game_src
make
```

## ステップ5: 実行

### 3DSエミュレータで実行 (Citra)

```bash
# game.3dsx ファイルをCitlaで開く
citra-qt game.3dsx
```

### 実機で実行

1. `game.3dsx` をSDカード `/3ds/` フォルダにコピー
2. 3DSで Homebrew Launcher を起動
3. `game.3dsx` を実行

## トラブルシューティング

### JSONパースエラーが出る場合

- JSONの形式が正しいか確認
- JSONバリデータで検証: https://jsonlint.com/

### ビルドエラーが出る場合

- devkitProが正しくインストールされているか確認
- 環境変数 `DEVKITPRO` が設定されているか確認

```bash
echo $DEVKITPRO
# /opt/devkitpro のように表示されるはず
```

### アセットが読み込まれない場合

- ファイルパスが正しいか確認 (相対パスで指定)
- 画像形式がPNGか確認
- ファイルサイズが大きすぎないか確認
