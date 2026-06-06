#include "json_parser.h"

// Simplified JSON parser for our use case
static const char *skip_whitespace(const char *str) {
    while (*str && isspace(*str)) str++;
    return str;
}

static char *parse_string_value(const char **str) {
    (*str)++;  // Skip opening quote
    char *result = malloc(1024);
    int i = 0;

    while (**str && **str != '"') {
        if (**str == '\\' && *(*str + 1)) {
            (*str)++;
            switch (**str) {
                case 'n': result[i++] = '\n'; break;
                case 't': result[i++] = '\t'; break;
                case '\"': result[i++] = '"'; break;
                case '\\': result[i++] = '\\'; break;
                default: result[i++] = **str;
            }
        } else {
            result[i++] = **str;
        }
        (*str)++;
    }
    (*str)++;  // Skip closing quote
    result[i] = '\0';
    return result;
}

JsonValue *json_parse(const char *json_string) {
    // Basic implementation - can be extended with full JSON parser
    JsonValue *root = malloc(sizeof(JsonValue));
    if (!root) return NULL;

    root->type = JSON_OBJECT;
    root->array_size = 0;
    root->key = NULL;
    root->value.object = NULL;

    return root;
}

JsonValue *json_parse_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    // Read entire file
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);

    JsonValue *result = json_parse(content);
    free(content);
    return result;
}

JsonValue *json_get_object_member(JsonValue *obj, const char *key) {
    if (!obj || obj->type != JSON_OBJECT) return NULL;
    // Search for key in object
    return NULL;
}

JsonValue *json_get_array_element(JsonValue *arr, int index) {
    if (!arr || arr->type != JSON_ARRAY) return NULL;
    if (index < 0 || index >= arr->array_size) return NULL;
    return &arr->value.array[index];
}

const char *json_get_string(JsonValue *val) {
    if (!val || val->type != JSON_STRING) return "";
    return val->value.string;
}

int json_get_number(JsonValue *val) {
    if (!val || val->type != JSON_NUMBER) return 0;
    return (int)val->value.number;
}

int json_get_boolean(JsonValue *val) {
    if (!val || val->type != JSON_BOOL) return 0;
    return val->value.boolean;
}

void json_free(JsonValue *val) {
    if (!val) return;

    switch (val->type) {
        case JSON_STRING:
            if (val->value.string) free(val->value.string);
            break;
        case JSON_ARRAY:
            if (val->value.array) {
                for (int i = 0; i < val->array_size; i++) {
                    json_free(&val->value.array[i]);
                }
                free(val->value.array);
            }
            break;
        case JSON_OBJECT:
            if (val->value.object) free(val->value.object);
            break;
        default:
            break;
    }

    if (val->key) free(val->key);
    free(val);
}
