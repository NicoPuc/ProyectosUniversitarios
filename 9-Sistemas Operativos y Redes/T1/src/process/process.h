// src/process/process.h
#pragma once

#include <stdbool.h>

typedef enum
{
    READY,
    WAITING,
    RUNNING,
    FINISHED
} State;

typedef struct process
{
    char name[50];
    int pid;
    int arrival_time;
    int burst_time;
    int n_bursts;
    int io_wait_time;
    int deadline;

    State state;

    int remaining_bursts;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int interruptions;
    int past_deadline;
    int start_execution_time;
    int last_cpu_time;
    int executed_time;
    int remaining_burst_time;
    int io_remaining_time;
    int in_high_queue;
} Process;

// Funciones para manejar procesos
Process *create_process(char *name, int pid, int arrival_time, int burst_time, int n_bursts, int io_wait_time, int deadline);
void destroy_process(Process *process);
void initialize_process(Process *p, char *name, int pid, int arrival_time, int burst_time, int n_bursts, int io_wait_time, int deadline);
