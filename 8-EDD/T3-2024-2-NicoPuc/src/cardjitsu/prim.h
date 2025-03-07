#ifndef PRIM_H
#define PRIM_H

typedef struct
{
    int u, v, cost;
} Edge;

typedef struct EdgeNode
{
    int v;
    int cost;
    struct EdgeNode *next;
} EdgeNode;

typedef struct
{
    int node;
    int cost;
} HeapNode;

typedef struct
{
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

int prim(int N, int L, Edge *edges);

#endif
