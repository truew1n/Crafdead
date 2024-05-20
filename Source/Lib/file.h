#ifndef CFD_LIB_FILE_H
#define CFD_LIB_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct string_t {
    char *data;
    size_t size;
} string_t;

inline char *read_file(const char *FILEPATH)
{
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", FILEPATH);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char*) malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read < file_size) {
        fclose(file);
        free(content);
        fprintf(stderr, "Error reading File %s\n", FILEPATH);
        return 0;
    }

    content[file_size] = '\0';

    fclose(file);

    return content;
}

inline string_t read_file_string(const char *FILEPATH)
{
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", FILEPATH);
        return {NULL, 0};
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    string_t content = {};
    content.size = file_size;

    content.data = (char*) malloc(file_size);
    if (content.data == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return {NULL, 0};
    }

    size_t bytes_read = fread(content.data, 1, file_size, file);
    if (bytes_read < file_size) {
        fclose(file);
        free(content.data);
        fprintf(stderr, "Error reading File %s\n", FILEPATH);
        return {NULL, 0};
    }

    fclose(file);

    return content;
}

#ifdef __cplusplus
}
#endif

#endif

