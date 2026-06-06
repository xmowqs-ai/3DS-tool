#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function prototypes
int file_exists(const char *path);
int create_directory(const char *path);
int write_file(const char *path, const char *content);
char *read_file(const char *path);
int copy_file(const char *src, const char *dest);
int get_file_size(const char *path);

#endif // FILE_UTILS_H
