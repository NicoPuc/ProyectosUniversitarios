#include <stdlib.h>
#include <stdio.h>
#include "avl_peso.h"
#include "pinguino.h"

NodoAvlPeso *inicializarAvlPeso()
{
    return NULL;
}

NodoAvlPeso *nuevoNodoAvlPeso(struct Pinguino *pinguino)
{
    NodoAvlPeso *nuevo = (NodoAvlPeso *)malloc(sizeof(NodoAvlPeso));
    if (nuevo == NULL)
    {
        printf("Error al asignar memoria para el nodo AVL de peso.\n");
        exit(1);
    }
    nuevo->pinguino = pinguino;
    nuevo->fe = 0;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

void insertarAvlPeso(NodoAvlPeso **raiz, struct Pinguino *pinguino, int *swap)
{
    if (*raiz == NULL)
    {
        *raiz = nuevoNodoAvlPeso(pinguino);
        *swap = 1;
    }
    else if (pinguino->peso < (*raiz)->pinguino->peso ||
             (pinguino->peso == (*raiz)->pinguino->peso && pinguino->id < (*raiz)->pinguino->id))
    {
        insertarAvlPeso(&((*raiz)->izquierdo), pinguino, swap);
        if (*swap)
            actualizarIzquierdaPeso(raiz, swap);
    }
    else
    {
        insertarAvlPeso(&((*raiz)->derecho), pinguino, swap);
        if (*swap)
            actualizarDerechaPeso(raiz, swap);
    }
}

void actualizarIzquierdaPeso(NodoAvlPeso **raiz, int *swap)
{
    switch ((*raiz)->fe)
    {
    case 1:
        (*raiz)->fe = 0;
        *swap = 0;
        break;
    case 0:
        (*raiz)->fe = -1;
        break;
    case -1:
        if ((*raiz)->izquierdo->fe == -1)
            rotacionIIPeso(raiz);
        else
            rotacionIDPeso(raiz);
        *swap = 0;
        break;
    }
}

void actualizarDerechaPeso(NodoAvlPeso **raiz, int *swap)
{
    switch ((*raiz)->fe)
    {
    case -1:
        (*raiz)->fe = 0;
        *swap = 0;
        break;
    case 0:
        (*raiz)->fe = 1;
        break;
    case 1:
        if ((*raiz)->derecho->fe == 1)
            rotacionDDPeso(raiz);
        else
            rotacionDIPeso(raiz);
        *swap = 0;
        break;
    }
}

// Rotaciones

void rotacionIIPeso(NodoAvlPeso **raiz)
{
    NodoAvlPeso *temp = (*raiz)->izquierdo;
    (*raiz)->izquierdo = temp->derecho;
    temp->derecho = *raiz;
    (*raiz)->fe = 0;
    temp->fe = 0;
    *raiz = temp;
}

void rotacionIDPeso(NodoAvlPeso **raiz)
{
    NodoAvlPeso *temp1 = (*raiz)->izquierdo;
    NodoAvlPeso *temp2 = temp1->derecho;

    temp1->derecho = temp2->izquierdo;
    temp2->izquierdo = temp1;
    (*raiz)->izquierdo = temp2->derecho;
    temp2->derecho = *raiz;

    if (temp2->fe == -1)
        (*raiz)->fe = 1;
    else
        (*raiz)->fe = 0;

    if (temp2->fe == 1)
        temp1->fe = -1;
    else
        temp1->fe = 0;

    temp2->fe = 0;
    *raiz = temp2;
}

void rotacionDDPeso(NodoAvlPeso **raiz)
{
    NodoAvlPeso *temp = (*raiz)->derecho;
    (*raiz)->derecho = temp->izquierdo;
    temp->izquierdo = *raiz;
    (*raiz)->fe = 0;
    temp->fe = 0;
    *raiz = temp;
}

void rotacionDIPeso(NodoAvlPeso **raiz)
{
    NodoAvlPeso *temp1 = (*raiz)->derecho;
    NodoAvlPeso *temp2 = temp1->izquierdo;

    temp1->izquierdo = temp2->derecho;
    temp2->derecho = temp1;
    (*raiz)->derecho = temp2->izquierdo;
    temp2->izquierdo = *raiz;

    if (temp2->fe == 1)
        (*raiz)->fe = -1;
    else
        (*raiz)->fe = 0;

    if (temp2->fe == -1)
        temp1->fe = 1;
    else
        temp1->fe = 0;

    temp2->fe = 0;
    *raiz = temp2;
}

void liberarAvlPeso(NodoAvlPeso **raiz)
{
    // liberamos arbol pq pinguinos se liberan en otra funcion
    if (*raiz == NULL)
        return;

    liberarAvlPeso(&((*raiz)->izquierdo));
    liberarAvlPeso(&((*raiz)->derecho));
    free(*raiz);
    *raiz = NULL;
}

NodoAvlPeso *encontrarMinimoEnRango(NodoAvlPeso *raiz, int minWeight)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->pinguino->peso < minWeight)
        return encontrarMinimoEnRango(raiz->derecho, minWeight);
    else
    {
        NodoAvlPeso *izq = encontrarMinimoEnRango(raiz->izquierdo, minWeight);
        return (izq != NULL) ? izq : raiz;
    }
}

NodoAvlPeso *encontrarMaximoEnRango(NodoAvlPeso *raiz, int maxWeight)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->pinguino->peso > maxWeight)
        return encontrarMaximoEnRango(raiz->izquierdo, maxWeight);
    else
    {
        NodoAvlPeso *der = encontrarMaximoEnRango(raiz->derecho, maxWeight);
        return (der != NULL) ? der : raiz;
    }
}
