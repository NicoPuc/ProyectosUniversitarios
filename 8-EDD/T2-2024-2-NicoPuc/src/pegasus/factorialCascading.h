// para el rango la idea es usar kd tree particionar nuestro espacio
//  parra circular hacer particiones de a 4
#ifndef FACTORIAL_CASCADING_H
#define FACTORIAL_CASCADING_H
#include <stdio.h>

struct Pinguino;
typedef struct Pinguino *pinguino;

typedef struct AssocTreeNode
{
    int y;
    struct AssocTreeNode *left;
    struct AssocTreeNode *right;
    struct AssocTreeNode *left_ptr;
    struct AssocTreeNode *right_ptr;
    pinguino point;
    int isLeaf;
} AssocTreeNode;

typedef struct RangeTreeNode
{
    int x;
    struct RangeTreeNode *left;
    struct RangeTreeNode *right;
    AssocTreeNode *assoc_tree;
    pinguino point;
    int isLeaf;
} RangeTreeNode;

// factorialcascading
int compareX(const void *a, const void *b);
int compareY(const void *a, const void *b);
RangeTreeNode *buildRangeTree(pinguino *points, int n);
AssocTreeNode *buildAssocTree(pinguino *points, int n);
void freeRangeTree(RangeTreeNode *node);
void freeAssocTree(AssocTreeNode *node);

// inrectangle
void inRectangle(RangeTreeNode *root, int x1, int y1, int x2, int y2, int N, FILE *output_file);
void rangeQuery2D(RangeTreeNode *node, int x1, int x2, int y1, int y2, pinguino **result, int *count, int *size);
void rangeQueryY(AssocTreeNode *node, int y1, int y2, pinguino **result, int *count, int *size);
void reportSubtreeY(AssocTreeNode *node, pinguino **result, int *count, int *size);
int comparePenguins(const void *a, const void *b);
RangeTreeNode *findVSplit(RangeTreeNode *node, int x1, int x2);

// incircle
void inCircle(RangeTreeNode *root, int x_center, int y_center, int radius, FILE *output_file);

#endif