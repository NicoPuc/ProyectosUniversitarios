// src/queue/queue.c
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        perror("Failed to allocate memory for queue");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

void destroy_queue(Queue *queue)
{
    free(queue);
}

void enqueue(Queue *queue, Process *process)
{
    if (is_full(queue))
    {
        printf("Queue is full. Cannot enqueue process %s\n", process->name);
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_PROCESSES;
    queue->processes[queue->rear] = process;
    queue->size++;
}

Process *dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        return NULL;
    }
    Process *process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % MAX_PROCESSES;
    queue->size--;
    return process;
}

bool is_empty(Queue *queue)
{
    return queue->size == 0;
}

bool is_full(Queue *queue)
{
    return queue->size == MAX_PROCESSES;
}
