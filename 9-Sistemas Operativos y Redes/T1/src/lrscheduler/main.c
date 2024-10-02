#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"

#define MAX_PROCESSES 100

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("Uso: %s <input_file> <output_file> <quantum>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_name = (char *)argv[1];
    char *output_file_name = (char *)argv[2];
    int q = atoi(argv[3]);

    InputFile *input_file = read_file(file_name);

    if (input_file == NULL)
    {
        printf("Error al leer el archivo: %s\n", file_name);
        return EXIT_FAILURE;
    }

    int num_processes = input_file->len;
    Process *processes[MAX_PROCESSES];

    // Inicializar procesos
    for (int i = 0; i < num_processes; ++i)
    {
        char *name = input_file->lines[i][0];
        int pid = atoi(input_file->lines[i][1]);
        int arrival_time = atoi(input_file->lines[i][2]);
        int burst_time = atoi(input_file->lines[i][3]);
        int n_bursts = atoi(input_file->lines[i][4]);
        int io_wait_time = atoi(input_file->lines[i][5]);
        int deadline = atoi(input_file->lines[i][6]);

        processes[i] = create_process(name, pid, arrival_time, burst_time, n_bursts, io_wait_time, deadline);
        processes[i]->state = READY; // Inicializar en READY
    }

    // Crear colas de alta y baja prioridad
    Queue *high_queue = create_queue();
    Queue *low_queue = create_queue();

    int current_time = 0;
    int total_processes_finished = 0;
    int total_processes = num_processes;

    Process *running_process = NULL;
    int running_quantum = 0;

    while (total_processes_finished < total_processes)
    {
        // Paso 1: Actualizar procesos que han terminado su tiempo de espera de I/O
        for (int i = 0; i < num_processes; ++i)
        {
            Process *p = processes[i];
            if (p->state == WAITING)
            {
                p->io_remaining_time--;
                if (p->io_remaining_time <= 0)
                {
                    p->state = READY;       // Cambiar a READY
                    enqueue(high_queue, p); // Encolar en la cola alta
                }
            }
        }

        // Paso 2: Actualizar proceso en RUNNING
        if (running_process != NULL)
        {
            running_process->remaining_burst_time--;
            running_quantum--;
            running_process->executed_time++;

            // Incrementar past_deadline si ejecutó pasado el deadline
            if (current_time > running_process->deadline)
            {
                running_process->past_deadline++; // Acumula tiempo ejecutado después del deadline
            }

            // Verificar si el proceso ha terminado su ejecución
            if (running_process->remaining_burst_time <= 0)
            {
                running_process->remaining_bursts--;
                if (running_process->remaining_bursts > 0)
                {
                    // El proceso pasa a esperar I/O
                    running_process->state = WAITING;
                    running_process->io_remaining_time = running_process->io_wait_time;
                    running_process->last_cpu_time = current_time; // Registrar última vez en CPU
                    running_process->interruptions++;
                }
                else
                {
                    // Proceso finaliza
                    running_process->state = FINISHED;
                    running_process->turnaround_time = current_time - running_process->arrival_time; // Calcular turnaround time
                    total_processes_finished++;
                }
                running_process = NULL; // Reiniciar running_process
            }
            else if (running_quantum <= 0)
            {
                // Si se acaba el quantum, mover a la cola Low
                running_process->state = READY;
                enqueue(low_queue, running_process);
                running_process->interruptions++;              // Incrementar interrupciones solo aquí
                running_process->last_cpu_time = current_time; // Registrar la última vez en CPU
                running_process = NULL;                        // Reiniciar running_process
            }
        }

        // Paso 3: Ingresar procesos a las colas según el tiempo actual
        for (int i = 0; i < num_processes; ++i)
        {
            Process *p = processes[i];
            if (p->arrival_time == current_time && p->state == READY)
            {
                enqueue(high_queue, p); // Encolar en la cola alta solo si está en READY
            }
        }

        // Paso 4: Revisar procesos en la cola Low para subir a High
        for (int i = 0; i < low_queue->size; ++i)
        {
            Process *p = low_queue->processes[i];
            if (2 * p->deadline < current_time - p->last_cpu_time)
            {
                p->state = READY;
                enqueue(high_queue, p);
                // Eliminar de la cola Low
                for (int j = i; j < low_queue->size - 1; ++j)
                {
                    low_queue->processes[j] = low_queue->processes[j + 1];
                }
                low_queue->size--;
                i--; // Ajustar el índice después de eliminar
            }
        }

        // Paso 5: Seleccionar el siguiente proceso a ejecutar solo si no hay uno en ejecución
        if (running_process == NULL)
        {
            Process *selected_process = NULL;

            // Seleccionar de la cola High si hay procesos disponibles
            if (!is_empty(high_queue))
            {
                selected_process = dequeue(high_queue);
                running_quantum = 2 * q; // Quantum para alta prioridad
            }
            // Seleccionar de la cola Low si no hay procesos en la cola High
            else if (!is_empty(low_queue))
            {
                selected_process = dequeue(low_queue);
                running_quantum = q; // Quantum para baja prioridad
            }

            // Si hay un proceso seleccionado
            if (selected_process != NULL)
            {
                running_process = selected_process;
                running_process->state = RUNNING;
                running_process->remaining_burst_time = running_process->burst_time;

                // Calcular response_time solo si es la primera vez que entra a RUNNING
                if (running_process->response_time == -1)
                {
                    running_process->response_time = current_time - running_process->arrival_time;
                }
                running_process->last_cpu_time = current_time; // Guardar el tiempo de entrada a la CPU
            }
        }

        // Incrementar waiting time solo si el proceso está en READY
        for (int i = 0; i < num_processes; ++i)
        {
            Process *p = processes[i];
            if (p->state == READY || p->state == WAITING)
            {
                p->waiting_time++; // Acumular tiempo de espera solo en READY
            }
        }

        current_time++;
    }

    // Escribir archivo de salida
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL)
    {
        perror("Error al abrir el archivo de salida");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_processes; ++i)
    {
        Process *p = processes[i];
        printf("%s,%d,%d,%d,%d,%d,%d\n",
               p->name,
               p->pid,
               p->interruptions,
               p->turnaround_time,
               p->response_time,
               p->waiting_time,
               p->past_deadline);
        fprintf(output_file, "%s,%d,%d,%d,%d,%d,%d\n",
                p->name,
                p->pid,
                p->interruptions,
                p->turnaround_time,
                p->response_time,
                p->waiting_time,
                p->past_deadline);
    }
    fclose(output_file);

    // Liberar memoria
    for (int i = 0; i < num_processes; ++i)
    {
        destroy_process(processes[i]);
    }
    destroy_queue(high_queue);
    destroy_queue(low_queue);
    input_file_destroy(input_file);

    printf("Archivo de salida '%s' creado correctamente.\n", output_file_name);

    return 1;
}
