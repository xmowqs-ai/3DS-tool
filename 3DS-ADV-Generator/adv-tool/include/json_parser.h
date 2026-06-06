#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    JSON_NULL,
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char *string;
        struct JsonValue *array;      // For arrays
        struct JsonValue *object;     // For objects (key-value pairs)
    } value;
    int array_size;                    // Size for arrays
    char *key;                        // Key for object members
} JsonValue;

// Function prototypes
JsonValue *json_parse(const char *json_string);
JsonValue *json_parse_file(const char *filename);
JsonValue *json_get_object_member(JsonValue *obj, const char *key);
JsonValue *json_get_array_element(JsonValue *arr, int index);
const char *json_get_string(JsonValue *val);
int json_get_number(JsonValue *val);
int json_get_boolean(JsonValue *val);
void json_free(JsonValue *val);

#endif // JSON_PARSER_H
