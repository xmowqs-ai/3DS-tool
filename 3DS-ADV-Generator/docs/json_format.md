# JSON形式仕様

## 全体構造

```json
{
  "title": "ゲームタイトル",
  "version": "1.0.0",
  "author": "作者名",
  "screen_width": 320,
  "screen_height": 240,
  "characters": [],
  "scenes": [],
  "variables": {}
}
```

## キャラクター定義

```json
{
  "id": "unique_character_id",
  "name": "表示名",
  "sprite": "assets/sprites/character.png",
  "voice_set": "assets/sounds/voice_set/"
}
```

## シーン定義

```json
{
  "id": "scene_001",
  "type": "normal",
  "background": "assets/backgrounds/bg_001.png",
  "music": "assets/sounds/bgm_001.ogg",
  "dialogs": [
    {
      "character": "heroine",
      "text": "ここにセリフが入ります。",
      "emotion": "normal",
      "voice": "assets/sounds/voice_001.ogg"
    }
  ],
  "choices": [
    {
      "id": "choice_1",
      "text": "選択肢1",
      "next_scene": "scene_002",
      "flag_set": "flag_choice_1"
    },
    {
      "id": "choice_2",
      "text": "選択肢2",
      "next_scene": "scene_003",
      "flag_set": "flag_choice_2"
    }
  ]
}
```

## アセット管理

### ディレクトリ構造

```
assets/
├── sprites/
│   ├── character_01_normal.png
│   ├── character_01_happy.png
│   └── character_02_sad.png
├── backgrounds/
│   ├── school_classroom.png
│   ├── park_day.png
│   └── night_sky.png
└── sounds/
    ├── bgm/
    │   ├── bgm_001.ogg
    │   └── bgm_002.ogg
    ├── se/
    │   ├── click.wav
    │   └── select.wav
    └── voice/
        ├── char_01_001.ogg
        └── char_01_002.ogg
```

## 変数とフラグシステム

```json
{
  "variables": {
    "affection_level": 0,
    "story_progress": "beginning"
  }
}
```

シーン内でのフラグ設定:

```json
{
  "id": "scene_010",
  "dialogs": [...],
  "on_end": {
    "set_variable": { "affection_level": 5 },
    "set_flag": ["met_character_01"]
  }
}
```
