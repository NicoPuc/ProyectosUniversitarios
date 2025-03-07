#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Osrms_File.h"

osrmsFile *os_open(int process_id, char *file_name, char mode)
{
    FILE *mem_file = fopen(file_name, "rb+");
    if (!mem_file)
    {
        perror("Error al abrir el archivo de memoria");
        return NULL;
    }

    // Validar el process_id
    if (process_id < 0 || process_id >= 32)
    {
        printf("ID de proceso inválido\n");
        fclose(mem_file);
        return NULL;
    }

    // Calcular la posición de la entrada del PCB
    unsigned int pcb_entry_pos = PCB_TABLE_START + process_id * PCB_ENTRY_SIZE;

    // Leer el estado del proceso
    uint8_t estado;
    fseek(mem_file, pcb_entry_pos, SEEK_SET);
    fread(&estado, sizeof(uint8_t), 1, mem_file);
    if (estado != 0x01)
    {
        printf("El proceso no está en ejecución\n");
        fclose(mem_file);
        return NULL;
    }

    // Leer la Tabla de Archivos del proceso
    unsigned int file_table_pos = pcb_entry_pos + 2 + 11; // Saltar estado (1 byte), id (1 byte), nombre (11 bytes)
    fseek(mem_file, file_table_pos, SEEK_SET);
    uint8_t file_table[FILE_TABLE_SIZE];
    fread(file_table, sizeof(uint8_t), FILE_TABLE_SIZE, mem_file);

    osrmsFile *file_desc = NULL;

    if (mode == 'r')
    {
        // Buscar el archivo en la Tabla de Archivos
        int found = 0;
        for (int i = 0; i < MAX_FILES; i++)
        {
            uint8_t validez = file_table[i * FILE_ENTRY_SIZE];
            char nombre_archivo[15] = {0};
            memcpy(nombre_archivo, &file_table[i * FILE_ENTRY_SIZE + 1], 14);

            if (validez == 0x01 && strcmp(nombre_archivo, file_name) == 0)
            {
                // Archivo encontrado
                found = 1;
                file_desc = (osrmsFile *)malloc(sizeof(osrmsFile));
                file_desc->process_id = process_id;
                strcpy(file_desc->file_name, file_name);
                // Leer tamaño y dirección virtual
                unsigned int tamaño_archivo;
                memcpy(&tamaño_archivo, &file_table[i * FILE_ENTRY_SIZE + 15], 4);
                file_desc->file_size = tamaño_archivo;

                unsigned int direccion_virtual;
                memcpy(&direccion_virtual, &file_table[i * FILE_ENTRY_SIZE + 19], 4);
                file_desc->virtual_address = direccion_virtual;

                file_desc->mode = mode;
                break;
            }
        }
        if (!found)
        {
            printf("Archivo no encontrado\n");
            fclose(mem_file);
            return NULL;
        }
    }
    else if (mode == 'w')
    {
        // Verificar que el archivo no exista
        int exists = 0;
        unsigned int last_virtual_address = 0; // Mantiene la última dirección virtual utilizada
        for (int i = 0; i < MAX_FILES; i++)
        {
            uint8_t validez = file_table[i * FILE_ENTRY_SIZE];
            if (validez == 0x01)
            {
                // Si hay archivos válidos, actualizamos la última dirección virtual utilizada
                unsigned int direccion_virtual;
                memcpy(&direccion_virtual, &file_table[i * FILE_ENTRY_SIZE + 19], 4);
                if (direccion_virtual > last_virtual_address)
                {
                    last_virtual_address = direccion_virtual;
                }

                char nombre_archivo[15] = {0};
                memcpy(nombre_archivo, &file_table[i * FILE_ENTRY_SIZE + 1], 14);
                if (strcmp(nombre_archivo, file_name) == 0)
                {
                    // Archivo ya existe
                    exists = 1;
                    break;
                }
            }
        }

        if (exists)
        {
            printf("El archivo ya existe\n");
            fclose(mem_file);
            return NULL;
        }

        // Asignar la nueva dirección virtual
        unsigned int direccion_virtual = last_virtual_address + PAGE_SIZE;
        if (direccion_virtual >= VIRTUAL_MEMORY_SIZE)
        {
            printf("No hay espacio en la memoria virtual del proceso\n");
            fclose(mem_file);
            return NULL;
        }

        // Crear una nueva entrada en la Tabla de Archivos
        int free_entry = -1;
        for (int i = 0; i < MAX_FILES; i++)
        {
            uint8_t validez = file_table[i * FILE_ENTRY_SIZE];
            if (validez == 0x00)
            {
                free_entry = i;
                break;
            }
        }
        if (free_entry == -1)
        {
            printf("No hay espacio en la Tabla de Archivos\n");
            fclose(mem_file);
            return NULL;
        }

        // Inicializar la entrada
        unsigned int entry_pos = file_table_pos + free_entry * FILE_ENTRY_SIZE;
        fseek(mem_file, entry_pos, SEEK_SET);

        uint8_t validez = 0x01;
        fwrite(&validez, sizeof(uint8_t), 1, mem_file);

        char nombre_archivo[14] = {0};
        strncpy(nombre_archivo, file_name, 14);
        fwrite(nombre_archivo, sizeof(char), 14, mem_file);

        unsigned int tamaño_archivo = 0;
        fwrite(&tamaño_archivo, sizeof(unsigned int), 1, mem_file);

        // Escribir la dirección virtual asignada
        fwrite(&direccion_virtual, sizeof(unsigned int), 1, mem_file);

        // Crear el descriptor de archivo
        file_desc = (osrmsFile *)malloc(sizeof(osrmsFile));
        file_desc->process_id = process_id;
        strcpy(file_desc->file_name, file_name);
        file_desc->file_size = 0;
        file_desc->virtual_address = direccion_virtual;
        file_desc->mode = mode;
    }
    else
    {
        printf("Modo inválido\n");
        fclose(mem_file);
        return NULL;
    }

    fclose(mem_file);
    return file_desc;
}

// Función para leer un archivo
int os_read_file(osrmsFile *file_desc, char *dest)
{
    if (!file_desc || file_desc->mode != 'r')
    {
        printf("Descriptor de archivo inválido o modo incorrecto\n");
        return -1;
    }

    FILE *mem_file = fopen(file_desc, "rb");
    if (!mem_file)
    {
        perror("Error al abrir el archivo de memoria");
        return -1;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file)
    {
        perror("Error al crear el archivo de destino");
        fclose(mem_file);
        return -1;
    }

    unsigned int bytes_leidos = 0;
    unsigned int tamaño_archivo = file_desc->file_size;
    unsigned int direccion_virtual = file_desc->virtual_address;

    while (bytes_leidos < tamaño_archivo)
    {
        // Obtener VPN y offset
        unsigned int vpn = (direccion_virtual >> 15) & 0xFFF; // 12 bits
        unsigned int offset = direccion_virtual & 0x7FFF;     // 15 bits

        unsigned int vpn_primera_orden = vpn >> 6;   // Primeros 6 bits
        unsigned int vpn_segunda_orden = vpn & 0x3F; // Últimos 6 bits

        // Obtener número de Tabla de Páginas de Segundo Orden
        unsigned int pcb_entry_pos = PCB_TABLE_START + file_desc->process_id * PCB_ENTRY_SIZE;
        unsigned int tp_po_pos = pcb_entry_pos + 2 + 11 + FILE_TABLE_SIZE; // Posición de la Tabla de Páginas de Primer Orden
        unsigned int entrada_tp_po_pos = tp_po_pos + vpn_primera_orden * 2;

        fseek(mem_file, entrada_tp_po_pos, SEEK_SET);
        uint16_t spt_number;
        fread(&spt_number, sizeof(uint16_t), 1, mem_file);

        // Obtener PFN
        unsigned int spt_pos = SPT_SPACE_START + spt_number * SPT_ENTRY_SIZE;
        unsigned int entrada_spt_pos = spt_pos + vpn_segunda_orden * 2;

        fseek(mem_file, entrada_spt_pos, SEEK_SET);
        uint16_t pfn;
        fread(&pfn, sizeof(uint16_t), 1, mem_file);

        // Calcular dirección física absoluta
        unsigned int dir_fisica = (8 * 1024) + 128 + (128 * 1024) + (8 * 1024) + pfn * FRAME_SIZE + offset;

        // Leer datos desde la memoria montada
        fseek(mem_file, dir_fisica, SEEK_SET);
        unsigned int bytes_a_leer = FRAME_SIZE - offset;
        if (bytes_a_leer > (tamaño_archivo - bytes_leidos))
        {
            bytes_a_leer = tamaño_archivo - bytes_leidos;
        }
        char *buffer = (char *)malloc(bytes_a_leer);
        fread(buffer, sizeof(char), bytes_a_leer, mem_file);

        // Escribir en el archivo de destino
        fwrite(buffer, sizeof(char), bytes_a_leer, dest_file);

        free(buffer);

        // Actualizar contadores y direcciones
        bytes_leidos += bytes_a_leer;
        direccion_virtual += bytes_a_leer;
    }

    fclose(mem_file);
    fclose(dest_file);

    return bytes_leidos;
}

// Función para escribir un archivo
int os_write_file(osrmsFile *file_desc, char *src)
{
    if (!file_desc || file_desc->mode != 'w')
    {
        printf("Descriptor de archivo inválido o modo incorrecto\n");
        return -1;
    }

    FILE *mem_file = fopen(file_desc, "rb+");
    if (!mem_file)
    {
        perror("Error al abrir el archivo de memoria");
        return -1;
    }

    FILE *src_file = fopen(src, "rb");
    if (!src_file)
    {
        perror("Error al abrir el archivo fuente");
        fclose(mem_file);
        return -1;
    }

    // Obtener tamaño del archivo fuente
    fseek(src_file, 0, SEEK_END);
    unsigned int tamaño_archivo = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);

    // Verificar espacio disponible en memoria virtual y frames
    // Esto es simplificado para el ejemplo; se debería implementar una verificación real
    unsigned int bytes_escritos = 0;
    unsigned int direccion_virtual = file_desc->virtual_address;

    while (bytes_escritos < tamaño_archivo)
    {
        // Obtener VPN y offset
        unsigned int vpn = (direccion_virtual >> 15) & 0xFFF; // 12 bits
        unsigned int offset = direccion_virtual & 0x7FFF;     // 15 bits

        unsigned int vpn_primera_orden = vpn >> 6;   // Primeros 6 bits
        unsigned int vpn_segunda_orden = vpn & 0x3F; // Últimos 6 bits

        // Asignar Tabla de Páginas de Segundo Orden si es necesario
        // Actualizar Bitmap de Tablas de Páginas
        // Para simplificar, asumiremos que ya están asignadas

        // Obtener PFN
        uint16_t pfn = 0;
        // Se debería asignar un frame libre y actualizar el Frame Bitmap
        // Para simplificar, asignamos un PFN consecutivo
        pfn = vpn; // Esto es solo para el ejemplo

        // Escribir PFN en la Tabla de Páginas de Segundo Orden
        unsigned int spt_number = vpn_primera_orden; // Para simplificar
        unsigned int spt_pos = SPT_SPACE_START + spt_number * SPT_ENTRY_SIZE;
        unsigned int entrada_spt_pos = spt_pos + vpn_segunda_orden * 2;

        fseek(mem_file, entrada_spt_pos, SEEK_SET);
        fwrite(&pfn, sizeof(uint16_t), 1, mem_file);

        // Calcular dirección física absoluta
        unsigned int dir_fisica = (8 * 1024) + 128 + (128 * 1024) + (8 * 1024) + pfn * FRAME_SIZE + offset;

        // Leer datos desde el archivo fuente
        fseek(src_file, bytes_escritos, SEEK_SET);
        unsigned int bytes_a_escribir = FRAME_SIZE - offset;
        if (bytes_a_escribir > (tamaño_archivo - bytes_escritos))
        {
            bytes_a_escribir = tamaño_archivo - bytes_escritos;
        }
        char *buffer = (char *)malloc(bytes_a_escribir);
        fread(buffer, sizeof(char), bytes_a_escribir, src_file);

        // Escribir en la memoria montada
        fseek(mem_file, dir_fisica, SEEK_SET);
        fwrite(buffer, sizeof(char), bytes_a_escribir, mem_file);

        free(buffer);

        // Actualizar contadores y direcciones
        bytes_escritos += bytes_a_escribir;
        direccion_virtual += bytes_a_escribir;

        // Verificar si hay frames disponibles
        if (pfn >= TOTAL_FRAMES)
        {
            printf("No quedan frames disponibles\n");
            break;
        }
    }

    // Actualizar tamaño del archivo en la Tabla de Archivos
    unsigned int pcb_entry_pos = PCB_TABLE_START + file_desc->process_id * PCB_ENTRY_SIZE;
    unsigned int file_table_pos = pcb_entry_pos + 2 + 11;
    unsigned int entry_pos = file_table_pos;
    // Buscar la entrada correspondiente al archivo
    for (int i = 0; i < MAX_FILES; i++)
    {
        fseek(mem_file, entry_pos, SEEK_SET);
        uint8_t validez;
        fread(&validez, sizeof(uint8_t), 1, mem_file);
        if (validez == 0x01)
        {
            char nombre_archivo[15] = {0};
            fread(nombre_archivo, sizeof(char), 14, mem_file);
            if (strcmp(nombre_archivo, file_desc->file_name) == 0)
            {
                // Actualizar tamaño del archivo
                fseek(mem_file, entry_pos + 15, SEEK_SET);
                fwrite(&tamaño_archivo, sizeof(unsigned int), 1, mem_file);
                break;
            }
        }
        entry_pos += FILE_ENTRY_SIZE;
    }

    fclose(mem_file);
    fclose(src_file);

    return bytes_escritos;
}

void os_close(osrmsFile *file_desc)
{
    if (file_desc)
    {
        free(file_desc);
    }
    else
    {
        printf("Error en cerrar archivo ya que no existe");
    }
}