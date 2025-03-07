#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "pinguino.h"
#include "avl_peso.h"
#include "factorialCascading.h"
/* Retorna true si ambos strings son iguales */

static bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

static bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }
  return true;
}

int main(int argc, char **argv)
{
  check_arguments(argc, argv);

  FILE *input_file = fopen(argv[1], "r");
  FILE *output_file = fopen(argv[2], "w");

  int N; // Cantidad de pingüinos
  int E; // Cantidad de consultas

  int result = fscanf(input_file, "%d", &N);
  if (result != 1)
  {
    printf("Error reading number of penguins");
    return 1;
  }
  // if (N > 45000)
  // {
  //   fclose(input_file);
  //   fclose(output_file);
  //   return 0;
  // }
  int id;
  int x;
  int y;
  int age;
  int weight;
  NodoAvl *raizEdad = inicializarAvl();
  NodoAvlPeso *raizPeso = inicializarAvlPeso();
  int swapEdad = 0;
  int swapPeso = 0;
  pinguino *penguins = malloc(N * sizeof(pinguino));
  for (int i = 0; i < N; i++)
  {
    /* Recibir datos de los pingüinos */
    result = fscanf(input_file, "%d %d %d %d %d", &id, &x, &y, &age, &weight);
    if (result != 5)
      return 1;
    // printf("ID: %d, X: %d, Y: %d, AGE: %d, WEIGHT: %d\n", id, x, y, age, weight);
    struct Pinguino *pinguino = iniciarPinguino(id, x, y, age, weight);
    penguins[i] = pinguino;
    insertarAvl(&raizEdad, pinguino, &swapEdad);
    insertarAvlPeso(&raizPeso, pinguino, &swapPeso);
  }

  qsort(penguins, N, sizeof(pinguino), compareX);
  RangeTreeNode *range_tree = buildRangeTree(penguins, N);

  result = fscanf(input_file, "%d", &E);
  if (result != 1)
  {
    printf("Error reading number of events");
    return 1;
  }
  char command[32];
  /* consultas */
  for (int i = 0; i < E; i++)
  {
    if (fscanf(input_file, "%s", command) != 1)
    {
      printf("Error al leer el comando en la consulta %d\n", i + 1);
      continue;
    }
    if (string_equals(command, "SEARCH-BY-AGE"))
    {
      int age;
      result = fscanf(input_file, "%d", &age);
      if (result != 1)
      {
        return 1;
      }
      searchByAge_(raizEdad, age, output_file);
    }
    else if (string_equals(command, "SEARCH-BY-WEIGHT-RANGE"))
    {
      int minWeight, maxWeight;
      result = fscanf(input_file, "%d %d", &minWeight, &maxWeight);
      if (result != 2)
      {
        return 1;
      }
      searchByWeightRange_(raizPeso, minWeight, maxWeight, output_file);
    }
    else if (string_equals(command, "IN-RECTANGLE"))
    {
      int x1, y1, x2, y2;
      result = fscanf(input_file, "%d %d %d %d", &x1, &y1, &x2, &y2);
      if (result != 4)
      {
        return 1;
      }
      inRectangle(range_tree, x1, y1, x2, y2, N, output_file);
    }
    else if (string_equals(command, "IN-CIRCLE"))
    {
      int x_center, y_center, radius;
      result = fscanf(input_file, "%d %d %d", &x_center, &y_center, &radius);
      if (result != 3)
      {
        return 1;
      }
      inCircle(range_tree, x_center, y_center, radius, output_file);
    }
    /* Recibir consultas */
  }

  /* Cerramos los archivos */
  fclose(input_file);
  fclose(output_file);

  /* Liberamos memoria */
  liberarAvl(&raizEdad);
  liberarAvlPeso(&raizPeso);
  freeRangeTree(range_tree);
  free(penguins);

  return 0;
}
