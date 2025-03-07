#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iglu.h"

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

  int x; // Numero de Pasos
  int k; // Tiempo de Espera
  int w; // profundidad minima de sueno
  int p; // profundidad inicial y maxima de sueno

  int result = fscanf(input_file, "%d %d %d %d ", &x, &k, &w, &p);
  if (result != 4)
  {
    printf("Error reading first line");
    return 1;
  }
  printf("x: %d, k: %d, w: %d, p: %d\n", x, k, w, p);

  /* Instanciamos nuestras estructuras*/
  int *s = malloc(x * sizeof(int));
  for (int i = 0; i < x; i++)
  {
    result = fscanf(input_file, "%d", &s[i]);
    if (result != 1)
    {
      printf("Error reading step weight");
      return 1;
    }
    // printf("Paso: %d\n", s[i]);
  }

  int status = cruzar_iglu(x, k, w, p, s);
  if (status == -1)
  {
    fprintf(output_file, "-1\n");
  }
  else
  {
    fprintf(output_file, "%d\n", status);
  }

  /* Cerramos los archivos */
  fclose(input_file);
  fclose(output_file);

  /* Liberamos memoria */
  free(s);

  return 0;
}
