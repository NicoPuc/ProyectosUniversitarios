// src/file_manager/manager.c
#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPLIT 255
#define BUFFER_SIZE 4096

// Función para dividir una cadena por un separador
static char **split_by_sep(char *str, char *sep)
{
    char **new_str = (char **)calloc(MAX_SPLIT, sizeof(char *));
    int index = 0;

    char *token = strtok(str, sep);
    while (token != NULL && index < MAX_SPLIT)
    {
        new_str[index] = (char *)calloc(BUFFER_SIZE, sizeof(char));
        strcpy(new_str[index++], token);
        token = strtok(NULL, sep);
    }
    return new_str;
}

InputFile *read_file(char *filename)
{
    FILE *file_pointer = fopen(filename, "r");
    if (!file_pointer)
    {
        perror("Failed to open input file");
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    if (!fgets(buffer, BUFFER_SIZE, file_pointer))
    {
        fclose(file_pointer);
        return NULL;
    }

    InputFile *input_file = (InputFile *)malloc(sizeof(InputFile));
    input_file->len = atoi(buffer);
    input_file->lines = (char ***)calloc(input_file->len, sizeof(char **));

    int index = 0;
    while (fgets(buffer, BUFFER_SIZE, file_pointer) && index < input_file->len)
    {
        buffer[strcspn(buffer, "\n")] = 0;
        buffer[strcspn(buffer, "\r")] = 0;
        input_file->lines[index++] = split_by_sep(buffer, " ");
    }

    fclose(file_pointer);
    return input_file;
}

void input_file_destroy(InputFile *input_file)
{
    for (int i = 0; i < input_file->len; i++)
    {
        for (int j = 0; j < MAX_SPLIT && input_file->lines[i][j] != NULL; j++)
        {
            free(input_file->lines[i][j]);
        }
        free(input_file->lines[i]);
    }
    free(input_file->lines);
    free(input_file);
}
