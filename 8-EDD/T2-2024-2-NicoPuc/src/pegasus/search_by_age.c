#include "pinguino.h"
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct Pinguino *iniciarPinguino(int id, int ejeX, int ejeY, int edad, int peso)
{
    struct Pinguino *pinguino = (struct Pinguino *)malloc(sizeof(struct Pinguino));
    pinguino->id = id;
    pinguino->ejeX = ejeX;
    pinguino->ejeY = ejeY;
    pinguino->edad = edad;
    pinguino->peso = peso;
    return pinguino;
}

void agregarPinguinoALaLista(ListaPinguinos *lista, struct Pinguino *pinguino)
{
    PinguinoList *nuevo = (PinguinoList *)malloc(sizeof(PinguinoList));
    nuevo->pinguino = pinguino;
    nuevo->next = NULL;

    if (*lista == NULL)
    {
        *lista = nuevo;
    }
    else
    {
        PinguinoList *actual = *lista;
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}

void searchByAge(NodoAvl *raiz, int age, ListaPinguinos *lista)
{
    if (raiz == NULL)
        return;

    searchByAge(raiz->izquierdo, age, lista);

    if (raiz->pinguino->edad == age)
    {
        agregarPinguinoALaLista(lista, raiz->pinguino);
    }
    searchByAge(raiz->derecho, age, lista);
}

void searchByAge_(NodoAvl *raiz, int age, FILE *output_file)
{
    ListaPinguinos lista = NULL;
    searchByAge(raiz, age, &lista);
    ListaPinguinos actual = lista;
    fprintf(output_file, "SEARCH-BY-AGE %d\n", age);
    if (actual != NULL)
    {
        fprintf(output_file, "%d ", actual->pinguino->id);
        actual = actual->next;
        while (actual != NULL)
        {
            fprintf(output_file, "- %d ", actual->pinguino->id);
            actual = actual->next;
        }
    }
    fprintf(output_file, "\n");
    while (lista != NULL)
    {
        ListaPinguinos temp = lista;
        lista = lista->next;
        free(temp);
    }
}
