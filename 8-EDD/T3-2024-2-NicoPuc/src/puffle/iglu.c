#include "iglu.h"
#include <math.h>
#include <stdio.h>

#include "iglu.h"
#include <math.h>
#include <stdio.h>

int cruzar_iglu(int x, int k, int w, int p, int *steps)
{
    int tiempo_total = 0;
    int profundidad_actual = p;
    for (int i = 0; i < x; i++)
    {
        if (profundidad_actual - steps[i] < w)
        {
            int tiempo_faltante = w - (profundidad_actual - steps[i]);
            tiempo_total += tiempo_faltante * k;
            profundidad_actual += tiempo_faltante;
            if (profundidad_actual > p)
            {
                return -1;
            }
            profundidad_actual -= steps[i];
        }
        else if (profundidad_actual - steps[i] >= w)
        {
            profundidad_actual -= steps[i];
            if (profundidad_actual > p)
            {
                return -1;
            }
        }
        // printf("paso actual: %d: %d, con profundidad actual del pinguino %d y timepo total acomulado %d\n", i, steps[i], profundidad_actual, tiempo_total);
    }

    return tiempo_total;
}
