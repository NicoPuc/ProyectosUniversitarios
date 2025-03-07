
// recomendamos investigar y usar árboles como Range-tree o KD-tree para estas consultas

// Investiga sobre Fractional Cascading e impleméntalo para resolver los eventos de la parte 1.2. Además,
// responde la pregunta extra en el informe (ver sección del informe para más detalles). Ten en cuenta que no
// se otorgarán bonificaciones parciales; para recibir las décimas, la implementación debe ser correcta y estar
// claramente explicada en el informe. Si la implementación está mal documentada, es poco clara o no cumple
// con la complejidad esperada, no se otorgará el bonus. Más adelante se subirá un formulario para avisar de la
// participación en el bonus.

// lista in_rectangle(x1, y1, x2, y2) // retornar lista con ids de los pinguinos
// {
//     lista pinguinos = crearLista(); // tamaño indefinido
//     // buscar los pinguinos dentro del rectagulo
//     return pinguinos;
// }
#include <stdio.h>
#include <stdlib.h>
#include "pinguino.h"
#include "factorialCascading.h"

int compareX(const void *a, const void *b)
{
    pinguino p1 = *(pinguino *)a;
    pinguino p2 = *(pinguino *)b;
    return p1->ejeX - p2->ejeX;
}

int compareY(const void *a, const void *b)
{
    pinguino p1 = *(pinguino *)a;
    pinguino p2 = *(pinguino *)b;
    return p1->ejeY - p2->ejeY;
}

RangeTreeNode *buildRangeTree(pinguino *points, int n)
{
    if (n == 0)
        return NULL;

    RangeTreeNode *node = malloc(sizeof(RangeTreeNode));
    if (node == NULL)
    {
        printf("Error allocating memory for RangeTreeNode\n");
        exit(1);
    }

    if (n == 1)
    {
        node->x = points[0]->ejeX;
        node->left = NULL;
        node->right = NULL;
        node->point = points[0];
        node->isLeaf = 1;
        node->assoc_tree = buildAssocTree(points, n);
    }
    else
    {
        int mid = n / 2;
        node->x = points[mid]->ejeX;
        node->isLeaf = 0;
        node->point = NULL;
        node->left = buildRangeTree(points, mid);
        node->right = buildRangeTree(points + mid, n - mid);
        node->assoc_tree = buildAssocTree(points, n);
    }
    return node;
}

AssocTreeNode *buildAssocTree(pinguino *points, int n)
{
    if (n == 0)
        return NULL;
    qsort(points, n, sizeof(pinguino), compareY);
    AssocTreeNode *node = malloc(sizeof(AssocTreeNode));

    if (n == 1)
    {
        node->y = points[0]->ejeY;
        node->left = NULL;
        node->right = NULL;
        node->point = points[0];
        node->isLeaf = 1;
        node->left_ptr = NULL;
        node->right_ptr = NULL;
    }
    else
    {
        int mid = n / 2;
        node->y = points[mid]->ejeY;
        node->isLeaf = 0;
        node->point = NULL;
        node->left = buildAssocTree(points, mid);
        node->right = buildAssocTree(points + mid, n - mid);
        node->left_ptr = node->left;
        node->right_ptr = node->right;
    }
    return node;
}

void freeRangeTree(RangeTreeNode *node)
{
    if (node == NULL)
        return;
    freeRangeTree(node->left);
    freeRangeTree(node->right);
    freeAssocTree(node->assoc_tree);
    free(node);
}

void freeAssocTree(AssocTreeNode *node)
{
    if (node == NULL)
        return;
    freeAssocTree(node->left);
    freeAssocTree(node->right);
    free(node);
}