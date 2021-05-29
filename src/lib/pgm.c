#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm.h"

pgm_t *pgm_read(const char *file_name) {
    FILE *pgm_file;
    if (0 == strcmp("", file_name)) {
        // An empty filename (default) denotes input from stdin
        pgm_file = stdin;
    } else {
        // Get a read-only file handle
        pgm_file = fopen(file_name, "r");
    }
    assert(pgm_file != NULL);

    // Allocate memory for the image
    pgm_t *image = malloc(sizeof *image);
    assert(image != NULL);

    // Initialise the image properties
    image->width = -1;
    image->height = -1;
    image->maxValue = -1;

    // First, find and discard the magic number
    int nextChar;
    while ((nextChar = getc(pgm_file)) != EOF) {
        if (nextChar == '#') {
            // Discard comment lines
            while (getc(pgm_file) != '\n');
        }
        if (nextChar == 'P') {
            getc(pgm_file);
            break;
        }
    }

    // Then read the image data
    int value, i = 0;
    while ((nextChar = getc(pgm_file)) != EOF) {
        // Discard comment lines
        if (nextChar == '#') {
            while (getc(pgm_file) != '\n');
        }
        // Skip anything that is not a valid positive integer
        if (fscanf(pgm_file, "%d", &value) <= 0) {
            continue;
        }

        if (image->width < 0) {
            image->width = value;
        } else if (image->height < 0) {
            image->height = value;
            // Allocate memory for the image values
            image->values = calloc(image->width * image->height, sizeof(*image->values));
        } else if (image->maxValue < 0) {
            image->maxValue = value;
        } else {
            image->values[i++] = value;
        }
    }

    return image;
}

void pgm_write(pgm_t *image, const char *file_name) {
    FILE *pgm_file;
    if (0 == strcmp("", file_name)) {
        // An empty filename (default) denotes output to stdout
        pgm_file = stdout;
    } else {
        // Get a write-only file handle, truncate file if it exists, create a new file if it doesn't
        pgm_file = fopen(file_name, "w");
    }
    assert(pgm_file != NULL);

    fprintf(pgm_file, "P2 %d %d %d", image->width, image->height, image->maxValue);

    for (int i = 0; i < image->width * image->height; ++i) {
        if (i % image->width == 0) {
            fprintf(pgm_file, "\n");
        }
        fprintf(pgm_file, "%d ", image->values[i]);
    }
}

void pgm_free(pgm_t *image) {
    free(image->values);
    free(image);
}
