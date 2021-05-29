#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/pgm.h"

void parse_args(int argc, char** argv, char **input_file, char **output_file) {
    if (argc < 2) return;

    // Print a simple help
    if (0 == strcmp("-h", argv[1]) || 0 == strcmp("--help", argv[1])) {
        printf("Usage: editpgm [input.pgm [output.pgm]]");
        exit(EXIT_SUCCESS);
    }

    *input_file = argv[1];

    if (argc < 3) return;

    *output_file = argv[2];
}

int main(int argc, char** argv) {
    char *input_file = "", *output_file = "";

    parse_args(argc, argv, &input_file, &output_file);

    pgm_t *image = pgm_read(input_file);

    pgm_write(image, output_file);

    pgm_free(image);
    return 0;
}
