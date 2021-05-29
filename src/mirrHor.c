//
// Created by buschkind on 29.05.21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>

#include "lib/pgm.h"

void mirrorHorizontal(pgm_t *picture){

#pragma omp parallel for
    for(int i = 0; i < picture->height; i++){
#pragma omp parallel for
        for(int n = 0; n < picture->width /2; n++){
            int temp = picture->values[picture->width * i + n];
            picture->values[picture->width * i + n] = picture->values[(picture->width * i) + (picture->width - n)];
            picture->values[(picture->width * i) + (picture->width - n)] = temp;
        }
    }



}