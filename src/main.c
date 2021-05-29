#include "lib/pgm.h"

int main(int argc, char** argv) {
    pgm_t *image = pgm_read("-");

    pgm_write(image, "./out.pgm");

    pgm_free(image);
    return 0;
}