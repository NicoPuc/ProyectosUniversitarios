
// recomendamos investigar y usar árboles como Range-tree o KD-tree para estas consultas

// Investiga sobre Fractional Cascading e impleméntalo para resolver los eventos de la parte 1.2. Además,
// responde la pregunta extra en el informe (ver sección del informe para más detalles). Ten en cuenta que no
// se otorgarán bonificaciones parciales; para recibir las décimas, la implementación debe ser correcta y estar
// claramente explicada en el informe. Si la implementación está mal documentada, es poco clara o no cumple
// con la complejidad esperada, no se otorgará el bonus. Más adelante se subirá un formulario para avisar de la
// participación en el bonus.

// lista in_circle(x1, y1, r)
// {
//     lista pinguinos = crearLista(); // tamañao indefinido
//     // buscar pinguinos en el ciculo de centro x1, y1 y con radio r
//     return pinguinos;
// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "factorialCascading.h"
#include "pinguino.h"

// Function prototypes
void inCircle(RangeTreeNode *root, int x_center, int y_center, int radius, FILE *output_file)
{
    // Define the bounding rectangle
    int x1 = x_center - radius;
    int x2 = x_center + radius;
    int y1 = y_center - radius;
    int y2 = y_center + radius;

    // Initialize the result array
    int size = 10;
    int count = 0;
    pinguino *candidates = malloc(size * sizeof(pinguino));
    if (candidates == NULL)
    {
        printf("Error allocating memory for candidates array\n");
        exit(1);
    }

    // Use the existing rangeQuery2D to get candidates within the bounding rectangle
    rangeQuery2D(root, x1, x2, y1, y2, &candidates, &count, &size);

    // Initialize the final result array
    int final_size = count > 10 ? count : 10;
    int final_count = 0;
    pinguino *result = malloc(final_size * sizeof(pinguino));
    if (result == NULL)
    {
        printf("Error allocating memory for result array\n");
        exit(1);
    }

    // Filter candidates that are inside the circle
    for (int i = 0; i < count; i++)
    {
        pinguino p = candidates[i];
        int dx = p->ejeX - x_center;
        int dy = p->ejeY - y_center;
        double distance = sqrt(dx * dx + dy * dy);
        if (distance <= radius)
        {
            if (final_count >= final_size)
            {
                final_size *= 2;
                result = realloc(result, final_size * sizeof(pinguino));
                if (result == NULL)
                {
                    printf("Error reallocating memory for result array\n");
                    exit(1);
                }
            }
            result[final_count++] = p;
        }
    }

    // Free the candidates array
    free(candidates);

    // Sort the results by ejeX, then by ejeY
    qsort(result, final_count, sizeof(pinguino), comparePenguins);

    // Output the results
    fprintf(output_file, "IN-CIRCLE %d %d %d\n", x_center, y_center, radius);
    for (int i = 0; i < final_count; i++)
    {
        fprintf(output_file, "%d ", result[i]->id);
        if (i < final_count - 1)
        {
            fprintf(output_file, "- ");
        }
    }
    fprintf(output_file, "\n");

    // Free the result array
    free(result);
}
