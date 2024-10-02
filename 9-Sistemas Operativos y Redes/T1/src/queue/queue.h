// src/queue/queue.h
#pragma once

#include "../process/process.h" // Ruta relativa correcta
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct queue
{
    Process *processes[MAX_PROCESSES];
    int front;
    int rear;
    int size;
} Queue;

// Prototipos de funciones
Queue *create_queue();
void destroy_queue(Queue *queue);
void enqueue(Queue *queue, Process *process);
Process *dequeue(Queue *queue);
bool is_empty(Queue *queue);
bool is_full(Queue *queue);
