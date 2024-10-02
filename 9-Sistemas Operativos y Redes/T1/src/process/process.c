// src/process/process.c
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Process *create_process(char *name, int pid, int arrival_time, int burst_time, int n_bursts, int io_wait_time, int deadline)
{
    Process *p = (Process *)malloc(sizeof(Process));
    if (p == NULL)
    {
        perror("Failed to allocate memory for process");
        exit(EXIT_FAILURE);
    }
    initialize_process(p, name, pid, arrival_time, burst_time, n_bursts, io_wait_time, deadline);

    return p;
}

void destroy_process(Process *process)
{
    free(process);
}

void initialize_process(Process *p, char *name, int pid, int arrival_time, int burst_time, int n_bursts, int io_wait_time, int deadline)
{
    strcpy(p->name, name);
    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->n_bursts = n_bursts;
    p->io_wait_time = io_wait_time;
    p->deadline = deadline;
    p->state = READY;

    // Inicializar variables para estadísticas
    p->remaining_bursts = n_bursts;
    p->waiting_time = 0;
    p->turnaround_time = 0;
    p->response_time = -1; // No establecido aún
    p->interruptions = 0;
    p->past_deadline = 0;
    p->start_execution_time = -1;
    p->last_cpu_time = 0;
    p->executed_time = 0;
    p->remaining_burst_time = burst_time;
    p->io_remaining_time = 0;
    p->in_high_queue = 1; // Inicia en la cola alta
}
