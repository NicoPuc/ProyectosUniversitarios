#ifndef AVL_PESO_H
#define AVL_PESO_H

struct Pinguino;

typedef struct NodoAvl NodoAvlPeso;

NodoAvlPeso *inicializarAvlPeso();
NodoAvlPeso *nuevoNodoAvlPeso(struct Pinguino *pinguino);

void insertarAvlPeso(NodoAvlPeso **raiz, struct Pinguino *pinguino, int *swap);
void actualizarIzquierdaPeso(NodoAvlPeso **raiz, int *swap);
void actualizarDerechaPeso(NodoAvlPeso **raiz, int *swap);

void rotacionIIPeso(NodoAvlPeso **raiz);
void rotacionIDPeso(NodoAvlPeso **raiz);
void rotacionDDPeso(NodoAvlPeso **raiz);
void rotacionDIPeso(NodoAvlPeso **raiz);
void liberarAvlPeso(NodoAvlPeso **raiz);

#endif
