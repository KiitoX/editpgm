// Standard includes
#include <assert.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

// Local includes
#include "lib/pgm.h"

/*
typedef struct {
    int width, height, maxValue;
    int *values;
} pgm_t;
*/

/**
 * @brief Mirrors the specified image vertically.
 * @param image The image to mirror.
 * @author Benedikt
 */
void mirror_vertically(pgm_t *image) {
	int *val = image->values;
	int w = image->width;
	int h = image->height;

#pragma omp parallel for 
	for (int r = 0; r < image->height / 2; r++) {
#pragma omp parallel for
		for (int c = 0; c < image->width; c++) {
			int* v1 = val + r * w + c;
			int* v2 = val + (h - r - 1) * w + c; 
			int temp = *v1;
			*v1 = *v2;
			*v2 = temp;	
		}
	}	
}

