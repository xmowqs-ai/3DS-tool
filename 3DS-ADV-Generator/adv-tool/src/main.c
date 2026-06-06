#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"
#include "file_utils.h"

void print_usage(const char *program_name) {
    printf("Usage: %s <command> [options]\n", program_name);
    printf("\nCommands:\n");
    printf("  generate <story.json> -o <output_dir>   Generate C code from JSON\n");
    printf("  validate <story.json>                    Validate JSON format\n");
    printf("  version                                  Show version\n");
    printf("  help                                     Show this help\n");
    printf("\nExample:\n");
    printf("  %s generate story.json -o game_src/\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "version") == 0) {
        printf("3DS ADV Generator v1.0.0\n");
        return 0;
    }

    if (strcmp(command, "help") == 0) {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(command, "generate") == 0) {
        if (argc < 4) {
            printf("Error: Missing arguments for 'generate' command\n");
            printf("Usage: %s generate <story.json> -o <output_dir>\n", argv[0]);
            return 1;
        }

        const char *json_path = argv[2];
        const char *output_dir = argv[4];

        printf("🎮 3DS ADV Generator\n");
        printf("=====================\n");
        printf("Loading JSON: %s\n", json_path);

        // Check if JSON file exists
        if (!file_exists(json_path)) {
            printf("Error: JSON file not found: %s\n", json_path);
            return 1;
        }

        // Create output directory
        if (!file_exists(output_dir)) {
            printf("Creating output directory: %s\n", output_dir);
            if (!create_directory(output_dir)) {
                printf("Error: Failed to create output directory\n");
                return 1;
            }
        }

        GameProject project;
        memset(&project, 0, sizeof(GameProject));

        // Parse JSON
        printf("Parsing JSON...\n");
        if (parse_json_to_game(json_path, &project) != 0) {
            printf("Error: Failed to parse JSON\n");
            return 1;
        }

        printf("✓ Project loaded: %s v%s\n", project.title, project.version);
        printf("  - Characters: %d\n", project.character_count);
        printf("  - Scenes: %d\n", project.scene_count);

        // Generate C code
        printf("\nGenerating C code...\n");
        if (generate_c_code(&project, output_dir) != 0) {
            printf("Error: Failed to generate C code\n");
            return 1;
        }

        printf("✓ Code generation complete!\n");
        printf("\nGenerated files:\n");
        printf("  - main.c (game main program)\n");
        printf("  - game_data.c (story and character data)\n");
        printf("  - game_structs.h (data structures)\n");
        printf("  - Makefile (build configuration)\n");
        printf("\nNext steps:\n");
        printf("  1. Copy assets to: %s/assets/\n", output_dir);
        printf("  2. Run: cd %s && make\n", output_dir);
        printf("  3. Run on 3DS with game.3dsx\n");

        return 0;
    }

    if (strcmp(command, "validate") == 0) {
        if (argc < 3) {
            printf("Error: Missing JSON file argument\n");
            return 1;
        }

        const char *json_path = argv[2];
        printf("Validating: %s\n", json_path);

        if (!file_exists(json_path)) {
            printf("Error: File not found\n");
            return 1;
        }

        GameProject project;
        memset(&project, 0, sizeof(GameProject));

        if (parse_json_to_game(json_path, &project) == 0) {
            printf("✓ JSON is valid!\n");
            printf("  Title: %s\n", project.title);
            printf("  Characters: %d\n", project.character_count);
            printf("  Scenes: %d\n", project.scene_count);
            return 0;
        } else {
            printf("✗ JSON validation failed\n");
            return 1;
        }
    }

    printf("Error: Unknown command '%s'\n", command);
    print_usage(argv[0]);
    return 1;
}
