#include "../osrms_API/osrms_API.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Uso: %s <memoria.bin>\n", argv[0]);
        return 1;
    }

    // Montar la memoria
    os_mount((char *)argv[1]);
    
    // Mostrar los procesos en ejecución
    os_ls_processes();

    // Verificar si un archivo existe en un proceso
    int process_id = 1;
    char file_name[] = "profeleslievuelvaporfavor.txt";
    int exists = os_exists(process_id, file_name);
    if (exists) {
        printf("El archivo '%s' existe en el proceso %d.\n", file_name, process_id);
    } else {
        printf("El archivo '%s' no existe en el proceso %d.\n", file_name, process_id);
    }

    // Iniciar un nuevo proceso
    printf("\n-- Iniciando un nuevo proceso --\n");
    int new_process_id = 1; // Proceso que vamos a iniciar y luego finalizar
    char new_process_name[] = "ProcesoNuevo";
    os_start_process(new_process_id, new_process_name);

    // Listar archivos de un proceso
    os_ls_files(process_id);

    // Mostrar el estado del Frame Bitmap
    os_frame_bitmap();

    // Mostrar el estado del Bitmap de Tablas de Páginas
    os_tp_bitmap();

    // Terminar el proceso que acabamos de iniciar
    printf("\n-- Finalizando el proceso con ID %d --\n", new_process_id);
    os_finish_process(new_process_id);

    // Mostramos los procesos en ejecución denuevo despues de terminar el proceso iniciado
    printf("\n-- Procesos en ejecución después de finalizar el proceso --\n");
    os_ls_processes();



    return 0;
}
