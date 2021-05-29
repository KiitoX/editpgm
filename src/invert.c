/**
 * Author: Manuel Caldeira, 2021
 */

#include "lib/pgm.h"

void pgm_invert(pgm_t *image) {
    int size = image->width * image->height;
    int max = image->maxValue;
    int *values = image->values;
#pragma omp parallel for default(none) firstprivate(size) shared(max) shared(values)
    for (int i = 0; i < size; ++i) {
        values[i] = max - values[i];
    }
}
