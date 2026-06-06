#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_parser.h"

#define MAX_OUTPUT_SIZE 1024 * 1024  // 1MB
#define MAX_SCENES 256
#define MAX_CHARACTERS 64
#define MAX_DIALOGS 512
#define MAX_CHOICES 16

typedef struct {
    char character_id[64];
    char text[512];
    char emotion[32];
    char voice[256];
} Dialog;

typedef struct {
    char text[256];
    char next_scene[64];
    char flag_set[64];
} Choice;

typedef struct {
    char id[64];
    char background[256];
    char music[256];
    Dialog dialogs[MAX_DIALOGS];
    int dialog_count;
    Choice choices[MAX_CHOICES];
    int choice_count;
} Scene;

typedef struct {
    char id[64];
    char name[128];
    char sprite[256];
    char voice_set[256];
} Character;

typedef struct {
    char title[256];
    char version[32];
    char author[128];
    int screen_width;
    int screen_height;
    Character characters[MAX_CHARACTERS];
    int character_count;
    Scene scenes[MAX_SCENES];
    int scene_count;
} GameProject;

// Function prototypes
int parse_json_to_game(const char *json_path, GameProject *project);
int generate_c_code(GameProject *project, const char *output_dir);
int generate_makefile(GameProject *project, const char *output_dir);
int generate_main_c(GameProject *project, const char *output_dir);
int generate_game_data_c(GameProject *project, const char *output_dir);
int generate_game_structs_h(GameProject *project, const char *output_dir);

#endif // GENERATOR_H
