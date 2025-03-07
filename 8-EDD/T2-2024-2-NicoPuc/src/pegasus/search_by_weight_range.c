#include <stdlib.h>
#include <stdio.h>
#include "avl_peso.h"
#include "pinguino.h"
void searchByWeightRange(NodoAvlPeso *raiz, int minWeight, int maxWeight, ListaPinguinos *lista)
{
    if (raiz == NULL)
        return;
    if (raiz->pinguino->peso >= minWeight)
        searchByWeightRange(raiz->izquierdo, minWeight, maxWeight, lista);

    if (raiz->pinguino->peso >= minWeight && raiz->pinguino->peso <= maxWeight)
    {
        agregarPinguinoALaLista(lista, raiz->pinguino);
    }
    if (raiz->pinguino->peso <= maxWeight)
        searchByWeightRange(raiz->derecho, minWeight, maxWeight, lista);
}

void searchByWeightRange_(NodoAvlPeso *raizPeso, int minWeight, int maxWeight, FILE *output_file)
{
    ListaPinguinos lista = NULL;
    searchByWeightRange(raizPeso, minWeight, maxWeight, &lista);
    fprintf(output_file, "SEARCH-BY-WEIGHT-RANGE %d %d\n", minWeight, maxWeight);
    PinguinoList *actual = lista;
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
        PinguinoList *temp = lista;
        lista = lista->next;
        free(temp);
    }
}
