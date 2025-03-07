#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeTree.h"

unsigned int hash(int penguinId)
{
    return penguinId % TABLE_SIZE;
}

char *listaAString(int code_tree[], int tamanio)
{
    char *resultado = (char *)malloc((tamanio * 2) * sizeof(char));
    int pos = 0;

    for (int i = 0; i < tamanio; i++)
    {
        pos += sprintf(&resultado[pos], "%d", code_tree[i]);
    }
    resultado[pos] = '\0';
    return resultado;
}

void buscarEnHashTable(int penguinId, FILE *output_file)
{
    unsigned int hashIndex = hash(penguinId);
    HashTableEntry *current = hashTable[hashIndex];
    while (current != NULL)
    {
        if (current->penguinId == penguinId)
        {
            fprintf(output_file, "Penguin %d: %s\n", penguinId, current->codeTree);
            return;
        }
        current = current->next;
    }
}