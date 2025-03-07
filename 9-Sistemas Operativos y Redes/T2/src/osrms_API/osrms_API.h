#pragma once
#include "../osrms_File/Osrms_File.h"


// En este archivo definiremos las funciones 

// Funciones generales
void os_mount(char* memory_path);
void os_ls_processes();
int os_exists(int process_id, char* file_name);
void os_ls_files(int process_id);
void os_frame_bitmap();
void os_tp_bitmap();

// Funciones para procesos
void os_start_process(int process_id, char* process_name);
void os_finish_process(int process_id);

// Funciones para archivos
osrmsFile* os_open(int process_id, char* file_name, char mode);
int os_read_file(osrmsFile* file_desc, char* dest);
int os_write_file(osrmsFile* file_desc, char* src);
void os_close(osrmsFile* file_desc);