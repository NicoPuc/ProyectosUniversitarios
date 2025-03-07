#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "osrms_API.h"

//Funcion void os_mount(char* memory_path)   funcion que monta la memoria, se arega una variable global con la ruta local donde esta el .bin que luego se usa en las otras funciones
static char memory_path_global[256];     

void os_mount(char* memory_path) {
    strcpy(memory_path_global, memory_path);
}

//Funcion void os_ls_processes()  Muestra en pantalla los procesos en ejecucion en la memoria,, nombre e ID

void os_ls_processes() {
    // Abrimos el archivo de memoria como binario
    FILE *memory_file = fopen(memory_path_global, "rb");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }

    unsigned int pcb_table_offset = 0;
    unsigned int pcb_entry_size = 256; 
    printf("Procesos en ejecucion:\n");

    for (int i = 0; i < 32; i++) {
        unsigned int entry_offset = pcb_table_offset + i * pcb_entry_size;
        fseek(memory_file, entry_offset, SEEK_SET);

        // Leemos el byte de estado 
        unsigned char state;
        fread(&state, sizeof(unsigned char), 1, memory_file);

        if (state == 0x01) {
            unsigned char process_id;
            fread(&process_id, sizeof(unsigned char), 1, memory_file);
            // Leemos el nombre del proceso
            char process_name[12] = {0};
            fread(process_name, sizeof(char), 11, memory_file);
            process_name[11] = '\0'; // Aseguramos la terminacion nula 
            
            printf("Process ID: %d, Nombre: %s\n", process_id, process_name);
        } else {
            // Se sigue avanzando el reto de bytes
            fseek(memory_file, pcb_entry_size - 1, SEEK_CUR);
        }
    }
    fclose(memory_file);
}

// Funcion int os_exists(int process_id, char* file_name) Funci´on que verifica si un archivo con nombre file name existe en la memoria del proceso con id process id. Retorna 1 si existe y 0 en ca- so contrario
//Tenia como 20 errores pero ya está
int os_exists(int process_id, char* file_name) {
    //Abrimos el archivo de memoria como binario
    FILE *memory_file = fopen(memory_path_global, "rb");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return 0; //Retorna 0 si no se pudo abrir el archivo
    }
    unsigned int pcb_table_offset = 0;
    unsigned int pcb_entry_size = 256;
    int file_exists = 0;

    for (int i = 0; i < 32; i++) {
        unsigned int entry_offset = pcb_table_offset + i * pcb_entry_size;
        fseek(memory_file, entry_offset, SEEK_SET);

        //Leer el estado del proceso
        unsigned char state;
        fread(&state, sizeof(unsigned char), 1, memory_file);

        if (state == 0x01) {
            // Leer el ID del proceso
            unsigned char pid;
            fread(&pid, sizeof(unsigned char), 1, memory_file);

            if (pid == (unsigned char) process_id) {   //Esto indica que el proceso se encontro 
                 fseek(memory_file, 11, SEEK_CUR);

                // Leemos la Tabla de Archivos 
                int file_table_entries = 5;
                
                for (int j = 0; j < file_table_entries; j++) {
                    // Leemos el byte de validez
                    unsigned char valid;
                    fread(&valid, sizeof(unsigned char), 1, memory_file);

                    if (valid == 0x01) {
                        // Leemos el nombre del archivo 
                        char fname[15] = {0};
                        fread(fname, sizeof(char), 14, memory_file);
                        fname[14] = '\0';
                        if (strncmp(fname, file_name, 14) == 0) {
                            // El archivo existe yay!
                            file_exists = 1;
                            break;
                        }
                        // Saltamos tamaño y dirección virtual
                        fseek(memory_file, 8, SEEK_CUR);
                    } else {
                        // Saltamos el resto de la entrada
                        fseek(memory_file, 22, SEEK_CUR);
                    }
                }
                break;
            } else {
                fseek(memory_file, 254, SEEK_CUR);
            }
        } else {
            fseek(memory_file, 255, SEEK_CUR);
        }
    }
    fclose(memory_file);
    return file_exists;
}

//Funcion void os_ls_files(int process_id)

void os_ls_files(int process_id) {
    //Abrimos el archivo de memoria como binario igual que antes 
    FILE *memory_file = fopen(memory_path_global, "rb");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }

    unsigned int pcb_table_offset = 0;
    unsigned int pcb_entry_size = 256;
    int process_found = 0;

    for (int i = 0; i < 32 ; i++) {
        unsigned int entry_offset = pcb_table_offset + i * pcb_entry_size;
        fseek(memory_file, entry_offset , SEEK_SET);

        //Leemos el estado del proceso 
        unsigned char state;
        fread(&state, sizeof(unsigned char), 1, memory_file);

        if (state == 0x01) {
            //Se lee el id del proceso
            unsigned char pid;
            fread(&pid, sizeof(unsigned char), 1, memory_file);

            if (pid == (unsigned char)process_id) {
                process_found = 1;
                // Nos saltamos el nombre del proceso que ocupa 11 bytes
                fseek(memory_file, 11, SEEK_CUR);

                printf("Archivos en el proceso %d:\n", process_id);

                // Leemos la tabla de archivos 
                int file_table_entries = 5;

                for (int j = 0; j < file_table_entries; j++) {
                    //Leemos el bit de validez 
                    unsigned char valid;
                    fread(&valid, sizeof(unsigned char), 1, memory_file);

                    if (valid == 0x01) {
                        //Leemos el nombre del archivo que ocupa 14 bytes 
                        char fname[15] = {0};
                        fread(fname, sizeof(char),14, memory_file);
                        fname[14] = '\0';  //si

                        //Leemos el tamaño del archivo
                        unsigned int file_size;
                        fread(&file_size, sizeof(unsigned int), 1, memory_file);

                        //Saltamos la direccion virtual
                        fseek(memory_file, 4, SEEK_CUR);
                        printf("Nombre: %s, Tamaño: %u bytes\n", fname, file_size);
                    } else {
                        //Saltamos el resto de la entrada que ocupa 22 bytes
                        fseek(memory_file, 22, SEEK_CUR);
                    }
                }
                break;
            }   else {
                //Saltamos el resto de la entrada del pcb
                fseek(memory_file, 254, SEEK_CUR);
            }
        }  else {
            //Saltamos el resto de la entrada del pcb
                fseek(memory_file, 255, SEEK_CUR);
        }
    } 
    if (!process_found) {
        printf("Proceso con ID %d no se encontró.\n", process_id);
    }
    fclose(memory_file); // Para no perder memoria
}

// void os_frame_bitmap()Imprime el estado actual del Frame Bitmap. Tambi´en debe imprimir el conteo de frames ocupados y libres

void os_frame_bitmap() {
    //Abrimos el archivo de memoria como binario igual que antes 
    FILE *memory_file = fopen(memory_path_global, "rb");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }

    //Calculamos el offset del Frame bitmap, segun enunciado 8kb + 128b + 128 kb
    unsigned int frame_bitmap_offset = 8192 + 128 + 131072;
    //Leemos el frame bitmap
    fseek(memory_file, frame_bitmap_offset, SEEK_SET);
    unsigned char frame_bitmap[8192];
    fread(frame_bitmap, sizeof(unsigned char), 8192, memory_file);

    int total_frames = 65536;
    int frames_used = 0;

    //Contamos los frames ocupados;
    for (int i = 0; i < total_frames; i++) {
        int byte_index = i / 8;
        int bit_index = i % 8;
        unsigned char byte = frame_bitmap[byte_index];

        if (byte & (1 << bit_index)) {
            frames_used++;
        }
    }
    int frames_free = total_frames - frames_used;

    printf("Estado del Frame Bitmap:\n");
    printf("Frames ocupados: %d\n", frames_used);
    printf("Frames libres: %d\n", frames_free);

    fclose(memory_file);
}

void os_tp_bitmap() {
    //Abrimos el archivo de memoria como binario igual que antes 
    FILE *memory_file = fopen(memory_path_global, "rb");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }

    // Calculamos el oofset del bitmap de tablas de pag
    unsigned int tp_bitmap_offset = 8192; // 8Kb

    //Leemos el bitmap de la tabla de pag
    fseek(memory_file, tp_bitmap_offset, SEEK_SET);
    unsigned char tp_bitmap[128];
    fread(tp_bitmap, sizeof(unsigned char), 128, memory_file);

    int total_tables = 1024;
    int tables_used = 0;

    //Contamos tablas ocupadas

    for (int i = 0; i < total_tables; i++) {
        int byte_index = i / 8;
        int bit_index = i & 8;
        unsigned char byte = tp_bitmap[byte_index];

        if (byte & (1 << bit_index)) {
            tables_used++;
        }
    }

    int tables_free = total_tables - tables_used;

    printf("Estado del Bitmap de Tablas de Páginas:\n");
    printf("Tablas ocupadas: %d\n", tables_used);
    printf("Tablas libres: %d\n", tables_free);

    fclose(memory_file);
}

//Funciones de procesos 

void os_start_process(int process_id, char* process_name) {
    //Abrimos el archivo de memoria como binario igual que antes 
    FILE *memory_file = fopen(memory_path_global, "rb+");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }

    printf("Abriendo archivo de memoria: %s\n", memory_path_global);  //Linea de debug porque estaba malo :(

    //Definimos los offsets y los tamaños 
    unsigned int pcb_table_offset = 0;
    unsigned int pcb_entry_size = 256; 
    int process_started = 0;

    //Iteramos sobre las entradas de la tabla PCB
    for (int i = 0; i < 32; i++) {
        unsigned int entry_offset = pcb_table_offset + i * pcb_entry_size;

        fseek(memory_file, entry_offset, SEEK_SET);
        unsigned char state;
        fread(&state, sizeof(unsigned char), 1, memory_file);
        
        if (state == 0x00) {
            //Encontramos la key
            process_started = 1;
            //Escribimos el estado activo
            fseek(memory_file, entry_offset, SEEK_SET);
            state = 0x01;
            fwrite(&state, sizeof(unsigned char), 1, memory_file);
            //Escribimos el id del proceso
            unsigned char pid = (unsigned char)process_id;
            fwrite(&pid, sizeof(unsigned char), 1, memory_file);
            // Escribimos el nombre del proceso 
            char name_buffer[11] = {0};
            strncpy(name_buffer, process_name, 11);
            fwrite(name_buffer, sizeof(char), 11, memory_file);
            // Inicializamos la tabla de archivos
            unsigned char file_table[115] = {0};
            fwrite(file_table, sizeof(unsigned char), 115, memory_file);
            // Inicializamos la tabla de pags de orden 1
            unsigned short page_table[64] = {0};
            fwrite(page_table, sizeof(unsigned short), 64, memory_file);

            printf("Proceso iniciado: ID = %d, Nombre = %s\n", process_id, name_buffer);

            break;
        }
    }
    if (!process_started) {
        printf("Error: No hay espacio para un nuevo proceso. \n");
    }
    fclose(memory_file);
}

//Por ultimo la funcion os_finish_process(int process_id)

void os_finish_process(int process_id) {
    //Abrimos el archivo igual que las otras 300 veces 
    FILE *memory_file = fopen(memory_path_global, "rb+");
    if (!memory_file) {
        printf("Error: no se pudo abrir el archivo %s \n", memory_path_global);
        return;
    }
    //definimos las mismas variables de antes ya que las funciones son muy similares (cambiando el process)
    unsigned int pcb_table_offset = 0;
    unsigned int pcb_entry_size = 256; 
    int process_found = 0;
    //Iteramos sobre las entradas de la tabla para encontrar el proceso
    for (int i = 0; i < 32; i++) {
        unsigned int entry_offset = pcb_table_offset + i * pcb_entry_size;
        fseek(memory_file, entry_offset, SEEK_SET);
        unsigned char state;
        fread(&state, sizeof(unsigned char), 1, memory_file);
        if (state == 0x01){
            unsigned char pid;
            fread(&pid, sizeof(unsigned char), 1, memory_file);
            if (pid == (unsigned char)process_id) {
                process_found = 1;
                //Saltamos el nombre 
                fseek(memory_file, 11, SEEK_CUR);
                //Leemos la tabla de archivos
                int file_table_entries = 5;
                for (int j = 0; j < file_table_entries; j++) {
                    //Leemos el bit de validez 
                    unsigned char valid;
                    fread(&valid, sizeof(unsigned char), 1, memory_file);
                    if (valid == 0x01) {
                        //Saltamos tanto el nombre del archivo como su tamaño
                        fseek(memory_file, 14 + 4, SEEK_CUR);
                        //Leemos la direccion virtual
                        unsigned int virtual_address;
                        fread(&virtual_address, sizeof(unsigned int), 1, memory_file);
                    } else {
                        //Se salta el resto de la entrada si no
                        fseek(memory_file, 22, SEEK_CUR);
                    }
                }
                //Liberamos la tabla de paginas de orden 1 para esto primero las leemos
                unsigned int first_level_page_table_offset = entry_offset + 1 + 1 + 11 + 115;
                fseek(memory_file, first_level_page_table_offset, SEEK_SET);
                unsigned short first_level_page_table[64];
                fread(first_level_page_table, sizeof(unsigned short), 64, memory_file);
                //Abrimos y modificamos el bitmap de la tabla 
                unsigned int tp_bitmap_offset = 8192; //va despues de la tabla de pcb
                fseek(memory_file, tp_bitmap_offset, SEEK_SET);
                unsigned char tp_bitmap[128];
                fread(tp_bitmap, sizeof(unsigned char), 128, memory_file);
                //Abrimos y modificamos el frame bitmap
                unsigned int frame_bitmap_offset = 8192 + 128 + 131072;
                fseek(memory_file, frame_bitmap_offset, SEEK_SET);
                unsigned char frame_bitmap[8192];
                fread(frame_bitmap, sizeof(unsigned char), 8192, memory_file);
                //Recorremos la tabla de paginas de primer orden
                for (int k = 0; k < 64; k++) {
                    unsigned short spt_number = first_level_page_table[k];
                    if (spt_number != 0) {
                        // Liberamos la tabla de orden 2 y marcamos en el Bitmap de tabla de pags como libre
                        int tp_bit_index = spt_number;
                        int tp_byte_index = tp_bit_index / 8;
                        int tp_bit_in_byte = tp_bit_index % 8;
                        tp_bitmap[tp_byte_index] &= ~(1 << tp_bit_in_byte);
                        // Leemos la tabla de orden 2
                        unsigned int spt_offset = 8192 + 128 + spt_number * 128; // 8 KB + 128 B + SPTN * 128 bytes
                        fseek(memory_file, spt_offset, SEEK_SET);
                        unsigned short second_level_page_table[64];
                        fread(second_level_page_table, sizeof(unsigned short), 64, memory_file);
                        // Liberamos los frames
                        for (int l = 0; l < 64; l++) {
                            unsigned short pfn = second_level_page_table[l];
                            if (pfn != 0) {
                                int frame_bit_index = pfn;
                                int frame_byte_index = frame_bit_index / 8;
                                int frame_bit_in_byte = frame_bit_index % 8;
                                frame_bitmap[frame_byte_index] &= ~(1 << frame_bit_in_byte);
                            }
                        }
                    }
                }
                // Escribimos los bitmaps actualizados
                fseek(memory_file, tp_bitmap_offset, SEEK_SET);
                fwrite(tp_bitmap, sizeof(unsigned char), 128, memory_file);
                fseek(memory_file, frame_bitmap_offset, SEEK_SET);
                fwrite(frame_bitmap, sizeof(unsigned char), 8192, memory_file);
                // Marcamos la entrada del proceso en la Tabla de PCBs como inválida
                fseek(memory_file, entry_offset, SEEK_SET);
                state = 0x00;
                fwrite(&state, sizeof(unsigned char), 1, memory_file);
                printf("Proceso terminado y recursos liberados: ID = %d\n", process_id);
                break;
            } else {
                // Saltamos el resto de la entrada del PCB
                fseek(memory_file, 254, SEEK_CUR);
            }
        } else {
            // Saltamos el resto de la entrada del PCB igual que arriba
            fseek(memory_file, 255, SEEK_CUR);
        }
    }

    if (!process_found) {
        printf("Error: Proceso con ID %d no encontrado.\n", process_id);
    }

    fclose(memory_file);  //liberamos para que no muera
}