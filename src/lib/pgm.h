#pragma once

typedef struct {
    int width, height, maxValue;
    int *values;
} pgm_t;

pgm_t *pgm_read(const char *file_name);
void pgm_write(pgm_t *image, const char *file_name);
void pgm_free(pgm_t *image);
