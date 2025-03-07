
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

void inRectangle(RangeTreeNode *root, int x1, int y1, int x2, int y2, int N, FILE *output_file)
{
    int count = 0;
    pinguino *result = malloc(N * sizeof(pinguino));
    rangeQuery2D(root, x1, x2, y1, y2, &result, &count, &N);
    qsort(result, count, sizeof(pinguino), comparePenguins);
    fprintf(output_file, "IN-RECTANGLE %d %d %d %d\n", x1, y1, x2, y2);
    for (int i = 0; i < count; i++)
    {
        fprintf(output_file, "%d ", result[i]->id);
        if (i < count - 1)
        {
            fprintf(output_file, "- ");
        }
    }
    fprintf(output_file, "\n");
    free(result);
}

int comparePenguins(const void *a, const void *b)
{
    pinguino p1 = *(pinguino *)a;
    pinguino p2 = *(pinguino *)b;
    if (p1->ejeX != p2->ejeX)
    {
        return p1->ejeX - p2->ejeX;
    }
    else
    {
        return p1->ejeY - p2->ejeY;
    }
}

void rangeQuery2D(RangeTreeNode *node, int x1, int x2, int y1, int y2, pinguino **result, int *count, int *size)
{
    if (node == NULL)
    {
        return;
    }
    RangeTreeNode *vsplit = findVSplit(node, x1, x2);

    if (vsplit == NULL)
    {
        return;
    }

    if (vsplit->isLeaf)
    {
        int x = vsplit->point->ejeX;
        int y = vsplit->point->ejeY;
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
        {
            if (*count >= *size)
            {
                *size *= 2;
                *result = realloc(*result, (*size) * sizeof(pinguino));
            }
            (*result)[(*count)++] = vsplit->point;
        }
        return;
    }
    RangeTreeNode *v = vsplit->left;
    while (v != NULL && !v->isLeaf)
    {
        if (x1 <= v->x)
        {
            if (v->right != NULL)
            {
                rangeQueryY(v->right->assoc_tree, y1, y2, result, count, size);
            }
            v = v->left;
        }
        else
        {
            v = v->right;
        }
    }
    if (v != NULL && v->isLeaf)
    {
        int x = v->point->ejeX;
        int y = v->point->ejeY;
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
        {
            if (*count >= *size)
            {
                *size *= 2;
                *result = realloc(*result, (*size) * sizeof(pinguino));
            }
            (*result)[(*count)++] = v->point;
        }
    }
    v = vsplit->right;
    while (v != NULL && !v->isLeaf)
    {
        if (v->x <= x2)
        {
            if (v->left != NULL)
            {
                rangeQueryY(v->left->assoc_tree, y1, y2, result, count, size);
            }
            v = v->right;
        }
        else
        {
            v = v->left;
        }
    }
    if (v != NULL && v->isLeaf)
    {
        int x = v->point->ejeX;
        int y = v->point->ejeY;
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
        {
            if (*count >= *size)
            {
                *size *= 2;
                *result = realloc(*result, (*size) * sizeof(pinguino));
            }
            (*result)[(*count)++] = v->point;
        }
    }
}

RangeTreeNode *findVSplit(RangeTreeNode *node, int x1, int x2)
{
    RangeTreeNode *v = node;
    while (v != NULL && !v->isLeaf && (x2 < v->x || x1 > v->x))
    {
        if (x2 < v->x)
        {
            v = v->left;
        }
        else
        {
            v = v->right;
        }
    }
    return v;
}

void rangeQueryY(AssocTreeNode *node, int y1, int y2, pinguino **result, int *count, int *size)
{
    if (node == NULL)
    {
        return;
    }
    if (node->isLeaf)
    {
        int y = node->point->ejeY;
        if (y1 <= y && y <= y2)
        {
            if (*count >= *size)
            {
                *size *= 2;
                *result = realloc(*result, (*size) * sizeof(pinguino));
            }
            (*result)[(*count)++] = node->point;
        }
        return;
    }
    if (y2 < node->y)
    {
        rangeQueryY(node->left, y1, y2, result, count, size);
    }
    else if (y1 > node->y)
    {
        rangeQueryY(node->right, y1, y2, result, count, size);
    }
    else
    {
        rangeQueryY(node->left, y1, y2, result, count, size);
        rangeQueryY(node->right, y1, y2, result, count, size);
    }
}

void reportSubtreeY(AssocTreeNode *node, pinguino **result, int *count, int *size)
{
    if (node == NULL)
    {
        return;
    }
    if (node->isLeaf)
    {
        if (*count >= *size)
        {
            *size *= 2;
            *result = realloc(*result, (*size) * sizeof(pinguino));
        }
        (*result)[(*count)++] = node->point;
        return;
    }
    reportSubtreeY(node->left, result, count, size);
    reportSubtreeY(node->right, result, count, size);
}