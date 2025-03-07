// crear un avl, importante que este siempre balanceado, por lo que cuando se balancea cuando entra o sale un pinguino
// nodo hijo izq menor o igual y nodo hijo derecha mayor por edad

// para funcion dos crear un arbol inductivamente hacia arriba considerando max sub izq
//  de esta forma quedan todas las hojas ordenadas y tomamos desde el min-range hasta el max-range
#ifndef AVL_H
#define AVL_H
#include <stdio.h>

struct Pinguino;
struct NodoAvl
{
    struct Pinguino *pinguino;
    int fe;
    struct NodoAvl *izquierdo;
    struct NodoAvl *derecho;
};
typedef struct NodoAvl NodoAvl;

NodoAvl *inicializarAvl();
NodoAvl *nuevoNodoAvl(struct Pinguino *pinguino);

void insertarAvl(NodoAvl **raiz, struct Pinguino *pinguino, int *swap);
void actualizarIzquierda(NodoAvl **raiz, int *swap);
void actualizarDerecha(NodoAvl **raiz, int *swap);

void rotacionII(NodoAvl **raiz);
void rotacionID(NodoAvl **raiz);
void rotacionDD(NodoAvl **raiz);
void rotacionDI(NodoAvl **raiz);
void rotacionII2(NodoAvl **raiz);
void rotacionDD2(NodoAvl **raiz);

void borrar(NodoAvl **raiz, struct Pinguino *pinguino, int *swap);
void eliminar(NodoAvl **raiz, int *swap);
void menor(NodoAvl *raiz, struct Pinguino **pinguino);
void actualizarBD(NodoAvl **raiz, int *swap);
void actualizarBI(NodoAvl **raiz, int *swap);
void liberarAvl(NodoAvl **raiz);
void liberarNodo(NodoAvl *nodo);
#endif