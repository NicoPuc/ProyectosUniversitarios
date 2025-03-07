#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeTree.h"

HashTableEntry *hashTable[TABLE_SIZE] = {NULL};
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

  if (input_file == NULL || output_file == NULL)
  {
    printf("Error al abrir archivos\n");
    return 1;
  }

  int ID;
  int CODE_TREE_LARGE;
  int K;           // Cantidad de consultas
  char buffer[64]; // Buffer para leer "END"
  int result;

  // Leemos hasta encontrar "END"
  while (true)
  {
    result = fscanf(input_file, "%s", buffer);

    // Verificamos si leímos la palabra "END"
    if (string_equals(buffer, "END"))
    {
      // printf("END detected\n");
      break;
    }
    else
    {
      // Si no es "END", convertimos la entrada a entero
      ID = atoi(buffer); // Convertimos buffer a entero para ID
      result = fscanf(input_file, "%d", &CODE_TREE_LARGE);
      if (result != 1)
      {
        printf("Error reading CODE_TREE\n");
        return 1;
      }
      int code_tree[CODE_TREE_LARGE];
      for (int i = 0; i < CODE_TREE_LARGE; i++)
      {
        result = fscanf(input_file, "%d", &code_tree[i]);
        if (result != 1)
        {
          printf("Error reading code tree element\n");
          return 1;
        }
      }
      char *codestring = listaAString(code_tree, CODE_TREE_LARGE);
      insertarEnHashTable(ID, codestring);
      free(codestring);
    }
  }

  // Leemos el número de consultas
  result = fscanf(input_file, "%d", &K);
  if (result != 1)
  {
    printf("Error reading number of events\n");
    return 1;
  }

  // Procesamos los eventos
  char command[32];
  for (int i = 0; i < K; i++)
  {
    result = fscanf(input_file, "%s", command);
    if (result != 1)
    {
      printf("Error reading event\n");
      return 1;
    }
    if (string_equals(command, "FIND"))
    {
      int id_;
      result = fscanf(input_file, "%d", &id_);
      if (result != 1)
      {
        return 1;
      }
      buscarEnHashTable(id_, output_file);
    }
    else if (string_equals(command, "VALIDATE"))
    {
      int id_, largo;
      result = fscanf(input_file, "%d %d", &id_, &largo);
      if (result != 2)
      {
        return 1;
      }
      int lista[largo];
      for (int i = 0; i < largo; i++)
      {
        result = fscanf(input_file, "%d", &lista[i]);
        if (result != 1)
        {
          return 1;
        }
      }
      char *lista_ = listaAString(lista, largo);
      validate(id_, lista_, largo, output_file);
      free(lista_);
      // printAllHashes(id_);
    }
  }

  /* Cerramos los archivos */
  fclose(input_file);
  fclose(output_file);
  liberarHashTable();
  return 0;
}
