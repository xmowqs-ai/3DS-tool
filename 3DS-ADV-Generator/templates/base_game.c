#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include "game_structs.h"

// Game configuration
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FPS 60

// Game state
static int current_scene_id = 0;
static int current_dialog_index = 0;
static int game_running = 1;

// Forward declarations
void init_game(void);
void update_game(u32 keys);
void render_game(void);
void cleanup_game(void);

void init_game(void) {
    current_scene_id = 0;
    current_dialog_index = 0;
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
}

void update_game(u32 keys) {
    if (keys & KEY_START) {
        game_running = 0;
    }
    
    if (keys & KEY_A) {
        current_dialog_index++;
        // TODO: Handle scene transitions
    }
    
    if (keys & KEY_B) {
        current_dialog_index--;
        if (current_dialog_index < 0) current_dialog_index = 0;
    }
}

void render_game(void) {
    consoleClear();
    
    // TODO: Render current scene
    printf("Scene %d\n", current_scene_id);
    printf("Dialog %d\n", current_dialog_index);
}

void cleanup_game(void) {
    gfxExit();
}

int main(void) {
    init_game();
    
    while (aptMainLoop() && game_running) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        
        update_game(kDown);
        render_game();
        
        gfxFlushBuffers();
        gfxSwapBuffers();
    }
    
    cleanup_game();
    return 0;
}
