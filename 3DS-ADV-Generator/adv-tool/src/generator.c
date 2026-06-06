#include "generator.h"
#include "file_utils.h"

int parse_json_to_game(const char *json_path, GameProject *project) {
    // TODO: Implement full JSON parsing
    // For now, return a basic project structure
    strcpy(project->title, "Sample Project");
    strcpy(project->version, "1.0.0");
    project->screen_width = 320;
    project->screen_height = 240;
    project->character_count = 0;
    project->scene_count = 0;

    char *json_content = read_file(json_path);
    if (!json_content) return 1;

    // Parse JSON (simplified for now)
    // In a full implementation, use a proper JSON library

    free(json_content);
    return 0;
}

int generate_makefile(GameProject *project, const char *output_dir) {
    char makefile_path[512];
    sprintf(makefile_path, "%s/Makefile", output_dir);

    const char *makefile_content = 
"#---------------------------------------------------------------------------\n"
"# Project specific settings\n"
"#---------------------------------------------------------------------------\n"
"TARGET := game\n"
"BUILD := build\n"
"SOURCES := .\n"
"DATA := data\n"
"INCLUDES := include\n"
"\n"
"ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard\n"
"CFLAGS := -g -Wall -O2 -mword-relocations $(ARCH) $(DEFINES)\n"
"CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions\n"
"ASFLAGS := -g $(ARCH)\n"
"LDFLAGS = -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)\n"
"\n"
"LIBS := -lctru -lm\n"
"\n"
"#---------------------------------------------------------------------------\n"
"# Setup environment variables\n"
"#---------------------------------------------------------------------------\n"
"export LD := $(CC)\n"
"export ODIR := $(BUILD)\n"
"export DEPSDIR := $(BUILD)\n"
"\n"
"CFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))\n"
"CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))\n"
"SFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))\n"
"BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))\n"
"\n"
"OFILES := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(SFILES:.s=.o)\n"
"TARGET_LIBS := $(BUILD)/$(TARGET).a\n"
"TARGET_ELF := $(BUILD)/$(TARGET).elf\n"
"TARGET_3DSX := $(TARGET).3dsx\n"
"\n"
".PHONY: all clean\n"
"\n"
"all: $(TARGET_3DSX)\n"
"\n"
"$(TARGET_3DSX): $(TARGET_ELF)\n"
"\t@echo building ... $(notdir $@)\n"
"\t@3dsxtool $(TARGET_ELF) $@\n"
"\n"
"$(TARGET_ELF): $(TARGET_LIBS)\n"
"\t@echo linking ... $(notdir $@)\n"
"\t@$(LD) $(LDFLAGS) $(TARGET_LIBS) $(LIBS) -o $@\n"
"\n"
"$(TARGET_LIBS): $(OFILES)\n"
"\t@$(AR) -rcs $@ $^\n"
"\n"
"$(BUILD)/%.o: %.c\n"
"\t@mkdir -p $(@D)\n"
"\t@echo $(notdir $<)\n"
"\t@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@\n"
"\n"
"$(BUILD)/%.o: %.cpp\n"
"\t@mkdir -p $(@D)\n"
"\t@echo $(notdir $<)\n"
"\t@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) -c $< -o $@\n"
"\n"
"$(BUILD)/%.o: %.s\n"
"\t@mkdir -p $(@D)\n"
"\t@echo $(notdir $<)\n"
"\t@$(AS) -MMD -MP -MF $(DEPSDIR)/$*.d $(ASFLAGS) -c $< -o $@\n"
"\n"
"clean:\n"
"\t@echo clean ...\n"
"\t@rm -rf $(BUILD) $(TARGET_3DSX)\n"
"\n"
"-include $(DEPSDIR)/*.d\n";

    return write_file(makefile_path, makefile_content);
}

int generate_main_c(GameProject *project, const char *output_dir) {
    char main_c_path[512];
    sprintf(main_c_path, "%s/main.c", output_dir);

    char content[8192];
    snprintf(content, sizeof(content),
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"#include <3ds.h>\n"
"\n"
"#include \"game_structs.h\"\n"
"\n"
"// Game state\n"
"static int current_scene = 0;\n"
"static GameState game_state;\n"
"\n"
"void init_game() {\n"
"    memset(&game_state, 0, sizeof(game_state));\n"
"    current_scene = 0;\n"
"}\n"
"\n"
"void render_scene() {\n"
"    // Clear screen\n"
"    consoleInit(GFX_TOP, NULL);\n"
"    consoleClear();\n"
"\n"
"    printf(\"\\x1b[2;2H%s\\n\", game_state.scenes[current_scene].name);\n"
"\n"
"    // Render dialog\n"
"    if (game_state.scenes[current_scene].dialog_count > 0) {\n"
"        Dialog *dialog = &game_state.scenes[current_scene].dialogs[0];\n"
"        printf(\"\\x1b[5;2H%s: %s\\n\", dialog->character, dialog->text);\n"
"    }\n"
"}\n"
"\n"
"int main() {\n"
"    // Initialize services\n"
"    gfxInitDefault();\n"
"    consoleInit(GFX_TOP, NULL);\n"
"\n"
"    init_game();\n"
"\n"
"    // Main game loop\n"
"    while (aptMainLoop()) {\n"
"        hidScanInput();\n"
"        u32 kDown = hidKeysDown();\n"
"\n"
"        if (kDown & KEY_START) break;  // Exit on START\n"
"        if (kDown & KEY_A) {\n"
"            current_scene++;\n"
"            if (current_scene >= SCENE_COUNT) current_scene = 0;\n"
"        }\n"
"\n"
"        render_scene();\n"
"        gfxFlushBuffers();\n"
"        gfxSwapBuffers();\n"
"    }\n"
"\n"
"    gfxExit();\n"
"    return 0;\n"
"}\n");

    return write_file(main_c_path, content);
}

int generate_game_structs_h(GameProject *project, const char *output_dir) {
    char structs_h_path[512];
    sprintf(structs_h_path, "%s/game_structs.h", output_dir);

    char content[4096];
    snprintf(content, sizeof(content),
"#ifndef GAME_STRUCTS_H\n"
"#define GAME_STRUCTS_H\n"
"\n"
"#include <stdint.h>\n"
"\n"
"#define SCENE_COUNT %d\n"
"#define CHARACTER_COUNT %d\n"
"#define MAX_DIALOGS 32\n"
"#define MAX_CHOICES 8\n"
"\n"
"typedef struct {\n"
"    char character[64];\n"
"    char text[256];\n"
"} Dialog;\n"
"\n"
"typedef struct {\n"
"    char text[128];\n"
"    int next_scene;\n"
"} Choice;\n"
"\n"
"typedef struct {\n"
"    char name[64];\n"
"    char background[256];\n"
"    Dialog dialogs[MAX_DIALOGS];\n"
"    int dialog_count;\n"
"    Choice choices[MAX_CHOICES];\n"
"    int choice_count;\n"
"} Scene;\n"
"\n"
"typedef struct {\n"
"    char id[64];\n"
"    char name[128];\n"
"} Character;\n"
"\n"
"typedef struct {\n"
"    Scene scenes[SCENE_COUNT];\n"
"    Character characters[CHARACTER_COUNT];\n"
"} GameState;\n"
"\n"
"extern Scene game_scenes[SCENE_COUNT];\n"
"extern Character game_characters[CHARACTER_COUNT];\n"
"\n"
"#endif // GAME_STRUCTS_H\n"
            , project->scene_count
            , project->character_count);

    return write_file(structs_h_path, content);
}

int generate_game_data_c(GameProject *project, const char *output_dir) {
    char game_data_c_path[512];
    sprintf(game_data_c_path, "%s/game_data.c", output_dir);

    char content[8192];
    snprintf(content, sizeof(content),
"#include \"game_structs.h\"\n"
"\n"
"// Character data\n"
"Character game_characters[CHARACTER_COUNT] = {\n"
"    // Characters will be populated from JSON\n"
"};\n"
"\n"
"// Scene data\n"
"Scene game_scenes[SCENE_COUNT] = {\n"
"    // Scenes will be populated from JSON\n"
"};\n");

    return write_file(game_data_c_path, content);
}

int generate_c_code(GameProject *project, const char *output_dir) {
    // Create subdirectories
    char include_dir[512], src_dir[512], assets_dir[512];
    sprintf(include_dir, "%s/include", output_dir);
    sprintf(src_dir, "%s/src", output_dir);
    sprintf(assets_dir, "%s/assets", output_dir);

    create_directory(include_dir);
    create_directory(src_dir);
    create_directory(assets_dir);

    // Generate Makefile
    if (!generate_makefile(project, output_dir)) return 1;

    // Generate game_structs.h
    if (!generate_game_structs_h(project, include_dir)) return 1;

    // Generate main.c
    if (!generate_main_c(project, src_dir)) return 1;

    // Generate game_data.c
    if (!generate_game_data_c(project, src_dir)) return 1;

    return 0;
}
