#include "prim.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

MinHeap *create_min_heap(int capacity)
{
    MinHeap *heap = malloc(sizeof(MinHeap));
    if (!heap)
    {
        perror("Error al asignar memoria para el min-heap");
        exit(1);
    }
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void insert_min_heap(MinHeap *heap, int node, int cost)
{
    if (heap->size >= heap->capacity)
    {
        fprintf(stderr, "Error: Heap capacity exceeded\n");
        exit(1);
    }
    heap->nodes[heap->size] = (HeapNode){node, cost};
    int i = heap->size++;
    while (i > 0 && heap->nodes[(i - 1) / 2].cost > heap->nodes[i].cost)
    {
        swap(&heap->nodes[(i - 1) / 2], &heap->nodes[i]);
        i = (i - 1) / 2;
    }
}

HeapNode extract_min(MinHeap *heap)
{
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    int i = 0;
    while (true)
    {
        int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < heap->size && heap->nodes[left].cost < heap->nodes[smallest].cost)
            smallest = left;
        if (right < heap->size && heap->nodes[right].cost < heap->nodes[smallest].cost)
            smallest = right;
        if (smallest == i)
            break;
        swap(&heap->nodes[i], &heap->nodes[smallest]);
        i = smallest;
    }
    return root;
}

void free_min_heap(MinHeap *heap)
{
    free(heap->nodes);
    free(heap);
}

EdgeNode **create_graph(int N)
{
    EdgeNode **graph = calloc(N, sizeof(EdgeNode *));
    if (!graph)
    {
        perror("Error al asignar memoria para el grafo");
        exit(1);
    }
    return graph;
}

void add_edge(EdgeNode **graph, int u, int v, int cost)
{
    EdgeNode *new_node = malloc(sizeof(EdgeNode));
    if (!new_node)
    {
        perror("Error al asignar memoria para la arista");
        exit(1);
    }
    new_node->v = v;
    new_node->cost = cost;
    new_node->next = graph[u];
    graph[u] = new_node;
}

void free_graph(EdgeNode **graph, int N)
{
    if (!graph)
        return;

    for (int i = 0; i < N; i++)
    {
        EdgeNode *current = graph[i];
        while (current)
        {
            EdgeNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

int prim(int N, int L, Edge *edges)
{
    EdgeNode **graph = create_graph(N);

    for (int i = 0; i < L; i++)
    {
        if (edges[i].u < 0 || edges[i].u >= N || edges[i].v < 0 || edges[i].v >= N)
        {
            fprintf(stderr, "Índice inválido en la entrada de aristas u: %d, v: %d, cost: %d\n", edges[i].u, edges[i].v, edges[i].cost);
            continue;
        }
        add_edge(graph, edges[i].u, edges[i].v, edges[i].cost);
        add_edge(graph, edges[i].v, edges[i].u, edges[i].cost);
    }

    MinHeap *heap = create_min_heap(L);
    bool *in_mst = calloc(N, sizeof(bool));
    if (!in_mst)
    {
        perror("Error al asignar memoria para in_mst");
        exit(1);
    }

    int mst_cost = 0, nodes_used = 0;
    insert_min_heap(heap, 0, 0);

    while (heap->size > 0)
    {
        HeapNode min_node = extract_min(heap);
        if (in_mst[min_node.node])
            continue;

        in_mst[min_node.node] = true;
        mst_cost += min_node.cost;
        nodes_used++;

        for (EdgeNode *edge = graph[min_node.node]; edge; edge = edge->next)
        {
            if (!in_mst[edge->v])
            {
                insert_min_heap(heap, edge->v, edge->cost);
            }
        }

        if (nodes_used == N)
        {
            free_min_heap(heap);
            free(in_mst);
            free_graph(graph, N);
            return mst_cost;
        }
    }

    free_min_heap(heap);
    free(in_mst);
    free_graph(graph, N);
    return -1;
}
