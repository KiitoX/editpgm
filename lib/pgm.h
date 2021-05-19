//
// Created by emma on 19/05/2021.
//

#ifndef EDITPGM_PGM_H
#define EDITPGM_PGM_H

#include <stddef.h>
#include <stdint.h>
#include <malloc.h>
#include <assert.h>

typedef struct {
    size_t width, height, maxval;
    uint16_t *values;
} pgm_t;

pgm_t *pgm_load_file(const char *file_name);

void pgm_write_file(pgm_t *image);

#endif //EDITPGM_PGM_H
