#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prim.h"

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

  int N; // Numero de maestros
  int L; // Numero de sesiones de entrenamiento

  int result = fscanf(input_file, "%d", &N);
  if (result != 1)
  {
    printf("Error leyendo maestros\n");
    return 1;
  }
  result = fscanf(input_file, "%d", &L);
  if (result != 1)
  {
    printf("Error reading connections");
    return 1;
  }
  // printf("L: %d\n", L);
  /* Instanciamos nuestras estructuras*/
  Edge *edges = malloc(L * sizeof(Edge));

  for (int i = 0; i < L; i++)
  {
    int u, v, cost;
    result = fscanf(input_file, "%d %d %d", &u, &v, &cost);
    if (result != 3)
    {
      printf("Error reading connection line");
      free(edges);
      return 1;
    }
    // printf("Connection: %d, %d, %d\n", u, v, cost);
    edges[i] = (Edge){u - 1, v - 1, cost};
  }

  int mst_cost = prim(N, L, edges);
  fprintf(output_file, "%d\n", mst_cost);

  fclose(input_file);
  fclose(output_file);

  free(edges);
  return 0;
}
