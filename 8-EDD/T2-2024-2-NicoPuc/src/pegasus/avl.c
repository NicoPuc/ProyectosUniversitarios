#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "pinguino.h"

NodoAvl *inicializarAvl()
{
    return NULL;
}

NodoAvl *nuevoNodoAvl(struct Pinguino *pinguino)
{
    NodoAvl *nuevo = (NodoAvl *)malloc(sizeof(NodoAvl));
    nuevo->pinguino = pinguino;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    nuevo->fe = 0;
    return nuevo;
}

void insertarAvl(NodoAvl **raiz, struct Pinguino *pinguino, int *swap)
{
    if (*raiz == NULL)
    {
        *raiz = nuevoNodoAvl(pinguino);
        *swap = 1;
    }
    else if (pinguino->edad < (*raiz)->pinguino->edad)
    {
        insertarAvl(&((*raiz)->izquierdo), pinguino, swap);
        if (*swap)
            actualizarIzquierda(raiz, swap);
    }
    else if (pinguino->edad > (*raiz)->pinguino->edad)
    {
        insertarAvl(&((*raiz)->derecho), pinguino, swap);
        if (*swap)
            actualizarDerecha(raiz, swap);
    }
    else // pinguino->edad == (*raiz)->pinguino->edad
    {
        // Compare IDs
        if (pinguino->id <= (*raiz)->pinguino->id)
        {
            insertarAvl(&((*raiz)->izquierdo), pinguino, swap);
            if (*swap)
                actualizarIzquierda(raiz, swap);
        }
        else // pinguino->id > (*raiz)->pinguino->id
        {
            insertarAvl(&((*raiz)->derecho), pinguino, swap);
            if (*swap)
                actualizarDerecha(raiz, swap);
        }
    }
}

void actualizarIzquierda(NodoAvl **raiz, int *swap)
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
            rotacionII(&(*raiz));
        else
            rotacionID(&(*raiz));
        *swap = 0;
        break;
    }
}

void actualizarDerecha(NodoAvl **raiz, int *swap)
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
            rotacionDD(&(*raiz));
        else
            rotacionDI(&(*raiz));
        *swap = 0;
        break;
    }
}

void rotacionII(NodoAvl **raiz)
{
    NodoAvl *temporal = (*raiz)->izquierdo;
    (*raiz)->izquierdo = temporal->derecho;
    temporal->derecho = *raiz;
    temporal->fe = 0;
    (*raiz)->fe = 0;
    *raiz = temporal;
}

void rotacionID(NodoAvl **raiz)
{
    NodoAvl *aux1, *aux2;
    aux1 = (*raiz)->izquierdo;
    aux2 = aux1->derecho;
    aux1->derecho = aux2->izquierdo;
    aux2->izquierdo = aux1;
    (*raiz)->izquierdo = aux2->derecho;
    aux2->derecho = *raiz;
    if (aux2->fe == 1)
        aux1->fe = -1;
    else
        aux1->fe = 0;
    if (aux2->fe == -1)
        (*raiz)->fe = 1;
    else
        (*raiz)->fe = 0;
    aux2->fe = 0;
    *raiz = aux2;
}

void rotacionDD(NodoAvl **raiz)
{
    NodoAvl *aux = (*raiz)->derecho;
    (*raiz)->derecho = aux->izquierdo;
    aux->izquierdo = *raiz;
    aux->fe = 0;
    (*raiz)->fe = 0;
    *raiz = aux;
}

void rotacionDI(NodoAvl **raiz)
{
    if ((*raiz)->derecho == NULL)
    {
        return;
    }

    NodoAvl *aux1 = (*raiz)->derecho;

    if (aux1->izquierdo == NULL)
    {
        return;
    }

    NodoAvl *aux2 = aux1->izquierdo;

    aux1->izquierdo = aux2->derecho;
    aux2->derecho = aux1;
    (*raiz)->derecho = aux2->izquierdo;
    aux2->izquierdo = *raiz;
    if (aux2->fe == 1)
        aux1->fe = -1;
    else
        aux1->fe = 0;
    if (aux2->fe == -1)
        (*raiz)->fe = 1;
    else
        (*raiz)->fe = 0;
    aux2->fe = 0;
    *raiz = aux2;
}

void borrar(NodoAvl **raiz, struct Pinguino *pinguino, int *swap)
{
    if (!(*raiz))
        *swap = 0;
    else if ((*raiz)->pinguino->id == pinguino->id)
        eliminar(&(*raiz), swap);
    else if (pinguino->edad < (*raiz)->pinguino->edad)
    {
        borrar(&((*raiz)->izquierdo), pinguino, swap);
        if (*swap)
            actualizarBI(&(*raiz), swap);
    }
    else if (pinguino->edad > (*raiz)->pinguino->edad)
    {
        borrar(&((*raiz)->derecho), pinguino, swap);
        if (*swap)
            actualizarBD(&(*raiz), swap);
    }
}

void eliminar(NodoAvl **raiz, int *swap)
{
    NodoAvl *auxiliar;
    struct Pinguino *pinguinoE;
    if ((*raiz)->izquierdo == NULL)
    {
        auxiliar = *raiz;
        *raiz = (*raiz)->derecho;
        free(auxiliar);
        *swap = 1;
    }
    else if ((*raiz)->derecho == NULL)
    {
        auxiliar = *raiz;
        *raiz = (*raiz)->izquierdo;
        free(auxiliar);
        *swap = 1;
    }
    else
    {
        menor((*raiz)->derecho, &pinguinoE);
        (*raiz)->pinguino = pinguinoE;
        borrar(&((*raiz)->derecho), pinguinoE, swap);
        if (swap)
            actualizarBD(&auxiliar, swap);
    }
}

void menor(NodoAvl *raiz, struct Pinguino **pinguino)
{
    if (raiz->izquierdo->pinguino == NULL)
        *pinguino = raiz->pinguino;
    else
        menor(raiz->izquierdo, pinguino);
}

void actualizarBI(NodoAvl **raiz, int *swap)
{
    NodoAvl *temp;
    switch ((*raiz)->fe)
    {
    case -1:
        (*raiz)->fe = 0;
        break;
    case 0:
        (*raiz)->fe = 1;
        *swap = 0;
        break;
    case 1:
        temp = (*raiz)->derecho;
        switch (temp->fe)
        {
        case 1:
            rotacionDD(&(*raiz));
            break;
        case -1:
            rotacionDI(&(*raiz));
            break;
        case 0:
            rotacionDD2(&(*raiz));
            break;
        }
        *swap = 0;
        break;
    }
}

void actualizarBD(NodoAvl **raiz, int *swap)
{
    NodoAvl *temp;
    switch ((*raiz)->fe)
    {
    case 1:
        (*raiz)->fe = 0;
        break;
    case 0:
        (*raiz)->fe = 1;
        *swap = 0;
        break;
    case -1:
        temp = (*raiz)->izquierdo;
        switch (temp->fe)
        {
        case -1:
            rotacionII(&(*raiz));
            break;
        case 1:
            rotacionID(&(*raiz));
            break;
        case 0:
            rotacionII2(&(*raiz));
            break;
        }
        *swap = 0;
        break;
    }
}

void rotacionDD2(NodoAvl **raiz)
{
    NodoAvl *temp;
    temp = (*raiz)->derecho;
    (*raiz)->derecho = temp->izquierdo;
    temp->izquierdo = *raiz;
    temp->fe = -1;
    (*raiz)->fe = 1;
    *raiz = temp;
}

void rotacionII2(NodoAvl **raiz)
{
    {
        NodoAvl *temp;
        temp = (*raiz)->izquierdo;
        (*raiz)->izquierdo = temp->derecho;
        temp->derecho = *raiz;
        temp->fe = 1;
        (*raiz)->fe = -1;
        *raiz = temp;
    }
}

void liberarNodo(NodoAvl *nodo)
{
    if (nodo == NULL)
        return;
    liberarNodo(nodo->izquierdo);
    liberarNodo(nodo->derecho);
    if (nodo->pinguino != NULL)
    {
        free(nodo->pinguino);
    }
    free(nodo);
}

void liberarAvl(NodoAvl **raiz)
{
    if (*raiz == NULL)
        return;
    liberarNodo(*raiz);
    *raiz = NULL;
}