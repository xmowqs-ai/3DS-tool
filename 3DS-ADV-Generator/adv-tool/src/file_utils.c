#include "file_utils.h"

int file_exists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int create_directory(const char *path) {
#ifdef _WIN32
    return mkdir(path) == 0;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

int write_file(const char *path, const char *content) {
    FILE *file = fopen(path, "w");
    if (!file) return 0;

    size_t written = fwrite(content, 1, strlen(content), file);
    fclose(file);
    return written > 0;
}

char *read_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }

    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    return content;
}

int copy_file(const char *src, const char *dest) {
    FILE *source = fopen(src, "rb");
    if (!source) return 0;

    FILE *destination = fopen(dest, "wb");
    if (!destination) {
        fclose(source);
        return 0;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, destination);
    }

    fclose(source);
    fclose(destination);
    return 1;
}

int get_file_size(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);
    return size;
}
