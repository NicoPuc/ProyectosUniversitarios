#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "codeTree.h"

unsigned long combineHashes(char nodeValue, unsigned long leftHash, unsigned long rightHash)
{
    unsigned long hash = 7699;
    hash = ((hash << 5) + hash) + nodeValue;
    hash = ((hash << 5) + hash) + leftHash;
    hash = ((hash << 5) + hash) + rightHash;
    return hash;
}

void storeSubtreeHash(HashTableEntry *penguinEntry, unsigned long subtreeHash, int position)
{
    unsigned int hashIndex = subtreeHash % SUBTREE_TABLE_SIZE;
    SubtreeEntry *current = penguinEntry->subtreeHashTable[hashIndex];
    while (current != NULL)
    {
        if (current->subtreeHash == subtreeHash)
        {
            for (int i = 0; i < current->positionsCount; i++)
            {
                if (current->positions[i] == position)
                {
                    return;
                }
            }
            if (current->positionsCount == current->positionsCapacity)
            {
                current->positionsCapacity *= 2;
                current->positions = realloc(current->positions, current->positionsCapacity * sizeof(int));
            }
            current->positions[current->positionsCount++] = position;
            return;
        }
        current = current->next;
    }

    SubtreeEntry *newEntry = malloc(sizeof(SubtreeEntry));
    newEntry->subtreeHash = subtreeHash;
    newEntry->positionsCapacity = 4;
    newEntry->positionsCount = 1;
    newEntry->positions = malloc(newEntry->positionsCapacity * sizeof(int));
    newEntry->positions[0] = position;

    newEntry->next = penguinEntry->subtreeHashTable[hashIndex];
    penguinEntry->subtreeHashTable[hashIndex] = newEntry;
}

int getNodeLevel(int index)
{
    return (int)floor(log2(index + 1));
}
int getFirstNodeIndexAtLevel(int level)
{
    return (int)pow(2, level) - 1;
}

int getLastNodeIndexAtLevel(int level, int length)
{
    int lastNodeIndex = (int)pow(2, level + 1) - 2;
    return (lastNodeIndex >= length) ? length - 1 : lastNodeIndex;
}

void generateSubtreeHashes(char *codeTree, int length, HashTableEntry *penguinEntry)
{
    unsigned long fullTreeHash = computeSubtreeHash(codeTree, 0, length);
    storeSubtreeCodeAndHash(penguinEntry, codeTree, fullTreeHash, 0);
    int totalLevels = getNodeLevel(length - 1);
    for (int level = totalLevels; level >= 0; level--)
    {
        int firstNodeIndex = getFirstNodeIndexAtLevel(level);
        int lastNodeIndex = getLastNodeIndexAtLevel(level, length);

        for (int i = firstNodeIndex; i <= lastNodeIndex; i++)
        {
            if (2 * i + 2 < length)
            {
                int subtreeSize = 3;
                char *subtreeCode = (char *)malloc(subtreeSize + 1);
                subtreeCode[0] = codeTree[i];
                subtreeCode[1] = codeTree[2 * i + 1];
                subtreeCode[2] = codeTree[2 * i + 2];
                subtreeCode[3] = '\0';
                unsigned long subtreeHash = computeSubtreeHash(subtreeCode, 0, subtreeSize);
                storeSubtreeCodeAndHash(penguinEntry, subtreeCode, subtreeHash, i);
                free(subtreeCode);
            }
        }
    }
}

char *generateFullSubtreeCode(char *codeTree, int index, int length)
{
    if (index >= length)
    {
        return NULL;
    }
    char *leftSubtreeCode = NULL;
    if (2 * index + 1 < length)
    {
        leftSubtreeCode = generateFullSubtreeCode(codeTree, 2 * index + 1, length);
    }
    char *rightSubtreeCode = NULL;
    if (2 * index + 2 < length)
    {
        rightSubtreeCode = generateFullSubtreeCode(codeTree, 2 * index + 2, length);
    }
    int rootSize = 1;
    int leftSize = leftSubtreeCode ? strlen(leftSubtreeCode) : 0;
    int rightSize = rightSubtreeCode ? strlen(rightSubtreeCode) : 0;
    char *fullSubtreeCode = (char *)malloc(rootSize + leftSize + rightSize + 1);
    fullSubtreeCode[0] = codeTree[index];
    if (leftSubtreeCode)
    {
        strcpy(fullSubtreeCode + 1, leftSubtreeCode);
    }
    else
    {
        fullSubtreeCode[1] = '\0';
    }
    if (rightSubtreeCode)
    {
        strcat(fullSubtreeCode, rightSubtreeCode);
    }
    free(leftSubtreeCode);
    free(rightSubtreeCode);
    return fullSubtreeCode;
}

unsigned long computeSubtreeHash(char *subtreeCode, int index, int length)
{
    if (index >= length)
    {
        return 0;
    }
    char nodeValue = subtreeCode[index];
    unsigned long leftHash = 0, rightHash = 0;
    if (2 * index + 1 < length)
    {
        leftHash = computeSubtreeHash(subtreeCode, 2 * index + 1, length);
    }
    if (2 * index + 2 < length)
    {
        rightHash = computeSubtreeHash(subtreeCode, 2 * index + 2, length);
    }
    unsigned long subtreeHash = combineHashes(nodeValue, leftHash, rightHash);
    return subtreeHash;
}

void insertarEnHashTable(int penguinId, char *codeTree)
{
    unsigned int hashIndex = hash(penguinId);
    HashTableEntry *newEntry = (HashTableEntry *)malloc(sizeof(HashTableEntry));
    newEntry->penguinId = penguinId;
    newEntry->codeTree = strdup(codeTree);
    memset(newEntry->subtreeHashTable, 0, sizeof(newEntry->subtreeHashTable));
    newEntry->next = hashTable[hashIndex];
    hashTable[hashIndex] = newEntry;

    int length = strlen(codeTree);
    newEntry->hashValues = (unsigned long *)malloc(length * sizeof(unsigned long));
    generateSubtreeHashes(codeTree, length, newEntry);
}

int compareInts(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void validate(int penguinId, char *subtreeCode, int length, FILE *output_file)
{
    unsigned int hashIndex = hash(penguinId) % TABLE_SIZE;
    HashTableEntry *penguinEntry = hashTable[hashIndex];

    while (penguinEntry != NULL)
    {
        if (penguinEntry->penguinId == penguinId)
        {
            break;
        }
        penguinEntry = penguinEntry->next;
    }

    unsigned long subtreeHash = computeSubtreeHash(subtreeCode, 0, length);
    unsigned int subtreeHashIndex = subtreeHash % SUBTREE_TABLE_SIZE;
    SubtreeEntry *current = penguinEntry->subtreeHashTable[subtreeHashIndex];

    while (current != NULL)
    {
        if (current->subtreeHash == subtreeHash && strcmp(current->subtreeCode, subtreeCode) == 0)
        {
            qsort(current->positions, current->positionsCount, sizeof(int), compareInts);
            fprintf(output_file, "GRANTED ACCESS AGENT %d\n", penguinId);
            fprintf(output_file, "\tPERMISSIONS:");
            for (int i = 0; i < current->positionsCount; i++)
            {
                fprintf(output_file, " %d", current->positions[i] + 1);
            }
            fprintf(output_file, "\n");
            return;
        }
        current = current->next;
    }
    fprintf(output_file, "ACCESS DENIED AGENT %d\n", penguinId);
}

void liberarHashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashTableEntry *current = hashTable[i];
        while (current != NULL)
        {
            HashTableEntry *temp = current;
            current = current->next;
            free(temp->codeTree);
            free(temp->hashValues);
            for (int j = 0; j < SUBTREE_TABLE_SIZE; j++)
            {
                SubtreeEntry *subCurrent = temp->subtreeHashTable[j];
                while (subCurrent != NULL)
                {
                    SubtreeEntry *subTemp = subCurrent;
                    subCurrent = subCurrent->next;
                    free(subTemp->positions);
                    free(subTemp);
                }
            }
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

void storeSubtreeCodeAndHash(HashTableEntry *penguinEntry, char *subtreeCode, unsigned long subtreeHash, int position)
{
    unsigned int hashIndex = subtreeHash % SUBTREE_TABLE_SIZE;
    SubtreeEntry *current = penguinEntry->subtreeHashTable[hashIndex];
    while (current != NULL)
    {
        if (current->subtreeHash == subtreeHash)
        {
            for (int i = 0; i < current->positionsCount; i++)
            {
                if (current->positions[i] == position)
                {
                    return;
                }
            }
            if (current->positionsCount == current->positionsCapacity)
            {
                current->positionsCapacity *= 2;
                current->positions = realloc(current->positions, current->positionsCapacity * sizeof(int));
            }
            current->positions[current->positionsCount++] = position;
            return;
        }
        current = current->next;
    }

    SubtreeEntry *newEntry = malloc(sizeof(SubtreeEntry));
    newEntry->subtreeCode = strdup(subtreeCode);
    newEntry->subtreeHash = subtreeHash;
    newEntry->positionsCapacity = 4;
    newEntry->positionsCount = 1;
    newEntry->positions = malloc(newEntry->positionsCapacity * sizeof(int));
    newEntry->positions[0] = position;

    newEntry->next = penguinEntry->subtreeHashTable[hashIndex];
    penguinEntry->subtreeHashTable[hashIndex] = newEntry;
}
