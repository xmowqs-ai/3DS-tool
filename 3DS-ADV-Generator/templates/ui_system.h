#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include <3ds.h>
#include <stdint.h>

// UI Element types
typedef enum {
    UI_TEXT,
    UI_BUTTON,
    UI_CHOICE_MENU,
    UI_SPRITE,
    UI_BACKGROUND
} UIElementType;

// Text rendering
struct TextElement {
    int x, y;
    const char *text;
    uint32_t color;
};

// Button element
struct ButtonElement {
    int x, y, width, height;
    const char *label;
    uint32_t bg_color;
    uint32_t text_color;
    int is_selected;
};

// Choice menu
struct ChoiceMenu {
    struct ButtonElement *choices;
    int choice_count;
    int selected_index;
};

// Sprite rendering
struct SpriteElement {
    int x, y;
    int width, height;
    uint8_t *pixel_data;
};

// Function prototypes
void ui_draw_text(int x, int y, const char *text, uint32_t color);
void ui_draw_button(int x, int y, int width, int height, const char *label, int selected);
void ui_draw_choice_menu(struct ChoiceMenu *menu, int x, int y);
void ui_draw_sprite(struct SpriteElement *sprite);
void ui_clear_screen(uint32_t color);

#endif // UI_SYSTEM_H
