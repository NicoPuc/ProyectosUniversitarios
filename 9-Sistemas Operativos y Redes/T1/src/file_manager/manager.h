// src/file_manager/manager.h
#pragma once

typedef struct inputfile
{
    int len;
    char ***lines; // Array de arrays de strings
} InputFile;

// Prototipos de funciones
InputFile *read_file(char *filename);
void input_file_destroy(InputFile *input_file);
