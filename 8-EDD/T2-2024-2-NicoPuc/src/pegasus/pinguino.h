#ifndef PINGUINO_H
#define PINGUINO_H

#include <stdio.h>
#include "avl.h"
#include "avl_peso.h"

struct Pinguino
{
    int id;
    int ejeX;
    int ejeY;
    int edad;
    int peso;
};
typedef struct Pinguino *pinguino;

typedef struct PinguinoList
{
    struct Pinguino *pinguino;
    struct PinguinoList *next;
} PinguinoList;

typedef PinguinoList *ListaPinguinos;
// search by age
void searchByAge(NodoAvl *raiz, int age, ListaPinguinos *lista);
void searchByAge_(NodoAvl *raiz, int age, FILE *output_file);
void agregarPinguinoALaLista(ListaPinguinos *lista, struct Pinguino *pinguino);
struct Pinguino *iniciarPinguino(int id, int ejeX, int ejeY, int edad, int peso);

// search by weight range
void searchByWeightRange_(NodoAvlPeso *raizPeso, int minWeight, int maxWeight, FILE *output_file);
void searchByWeightRange(NodoAvlPeso *raiz, int minWeight, int maxWeight, ListaPinguinos *lista);
#endif