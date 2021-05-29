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
	for (int r = 0; r < image->width / 2; r++) {
		for (int c = 0; c < image->height; c++) {
			int* v1 = values + r * width + c;
			int* v2 = values + r * width + height - c;
			int temp = *v1;
			*v1 = *v2;
			*v2 = temp;	
		}
	}	
}

