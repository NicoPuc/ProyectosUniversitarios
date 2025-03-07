#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 252323
#define SUBTREE_TABLE_SIZE 252323

typedef struct SubtreeEntry
{
    char *subtreeCode;         // Código del subárbol no hasheado
    unsigned long subtreeHash; // Hash del subárbol
    int *positions;            // Arreglo dinámico de posiciones
    int positionsCount;        // Número de posiciones almacenadas
    int positionsCapacity;     // Capacidad actual del arreglo
    struct SubtreeEntry *next; // Puntero al siguiente en caso de colisiones
} SubtreeEntry;

typedef struct HashTableEntry
{
    int penguinId;
    char *codeTree;
    SubtreeEntry *subtreeHashTable[SUBTREE_TABLE_SIZE];
    unsigned long *hashValues;
    struct HashTableEntry *next;
} HashTableEntry;

typedef struct HashTableEntry HashTableEntry;

extern HashTableEntry *hashTable[TABLE_SIZE];

unsigned int hash(int penguinId);
void insertarEnHashTable(int penguinId, char *codeTree);
char *listaAString(int code_tree[], int tamanio);
void buscarEnHashTable(int penguinId, FILE *output_file);

unsigned long combineHashes(char nodeValue, unsigned long leftHash, unsigned long rightHash);
void storeSubtreeHash(HashTableEntry *penguinEntry, unsigned long subtreeHash, int position);
void generateSubtreeHashes(char *codeTree, int length, HashTableEntry *penguinEntry);
char *generateFullSubtreeCode(char *codeTree, int index, int length);
unsigned long computeSubtreeHash(char *subtreeCode, int index, int length);
void insertarEnHashTable(int penguinId, char *codeTree);
void validate(int penguinId, char *subtreeCode, int length, FILE *output_file);
void liberarHashTable();
void storeSubtreeCodeAndHash(HashTableEntry *penguinEntry, char *subtreeCode, unsigned long subtreeHash, int position);
