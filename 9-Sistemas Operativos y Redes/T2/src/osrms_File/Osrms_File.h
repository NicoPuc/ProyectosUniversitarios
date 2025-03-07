#pragma once
#include <stdint.h>

// Definimos la estructura

typedef struct
{
    int process_id;               // id del proceso
    char file_name[15];           // nombre del archivo, 14 bytes + terminator null
    char mode;                    // modo
    unsigned int file_size;       // tamaño
    unsigned int virtual_address; // ubicacion virtual
} osrmsFile;

#define PCB_TABLE_START 0
#define PCB_ENTRY_SIZE 256
#define PCB_TABLE_SIZE (32 * PCB_ENTRY_SIZE)
#define FILE_TABLE_OFFSET 2 // Desplazamiento en bytes dentro de la entrada PCB
#define FILE_TABLE_SIZE 115
#define FILE_ENTRY_SIZE 23
#define MAX_FILES 5
#define PAGE_SIZE (32 * 1024)                   // 32 KB por página
#define VIRTUAL_MEMORY_SIZE (128 * 1024 * 1024) // 128 MB

#define BITMAP_TP_START (8 * 1024)
#define BITMAP_TP_SIZE 128
#define SPT_SPACE_START (8 * 1024 + 128)
#define SPT_ENTRY_SIZE 128
#define SPT_COUNT 1024

#define FRAME_BITMAP_START (8 * 1024 + 128 + 128 * 1024)
#define FRAME_BITMAP_SIZE (8 * 1024)

#define FRAME_START (8 * 1024 + 128 + 128 * 1024 + 8 * 1024)
#define FRAME_SIZE (32 * 1024)
#define TOTAL_FRAMES 65536

#define PAGE_TABLE_FIRST_ORDER_SIZE 128
#define PAGE_TABLE_SECOND_ORDER_SIZE 128

osrmsFile *os_open(int process_id, char *file_name, char mode);
int os_read_file(osrmsFile *file_desc, char *dest);
int os_write_file(osrmsFile *file_desc, char *src);
void os_close(osrmsFile *file_desc);