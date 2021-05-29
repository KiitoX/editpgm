#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/pgm.h"

enum operation {
    MIRROR_HORIZONTAL,
    MIRROR_VERTICALLY,
    INVERT,
    NO_OP,
};

extern void mirrorHorizontal(pgm_t *picture);
extern void mirror_vertically(pgm_t *image);
extern void pgm_invert(pgm_t *image);

void print_help() {
    // Print a simple help
    printf("Usage: editpgm [input.pgm [output.pgm]] [operation]\n"
           "\n"
           "The standard input/output is used if no file name is specified, respectively."
           "\n"
           "The following image operations are available:\n"
           " -mh --mirror-horizontally  mirror the image horizontally;\n"
           " -mv --mirror-vertically    mirror the image vertically;\n"
           " -i  --invert               invert the image;\n"
           "\n"
           "     --help                 display this help and exit;\n");
}

void parse_args(int argc, char** argv, char **input_file, char **output_file, enum operation *op) {
    // Loop over all given command line arguments
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        if (*arg == '-') {
            // If an argument starts with a dash, treat it as an optional argument
            if (0 == strcmp("-h", argv[1]) || 0 == strcmp(arg, "--help")) {
                print_help();
                exit(EXIT_SUCCESS);
            } else if (0 == strcmp(arg, "-mh") || 0 == strcmp(arg, "--mirror-horizontally")) {
                *op = MIRROR_HORIZONTAL;
            } else if (0 == strcmp(arg, "-mv") || 0 == strcmp(arg, "--mirror-vertically")) {
                *op = MIRROR_VERTICALLY;
            } else if (0 == strcmp(arg, "-i") || 0 == strcmp(arg, "--invert")) {
                *op = INVERT;
            } else {
                printf("Error, unknown optional argument '%s'.\n\n", arg);
                print_help();
                exit(EXIT_FAILURE);
            }
        } else {
            // Otherwise it is a positional argument
            if (**input_file == '\0') {
                *input_file = arg;
            } else if (**output_file == '\0') {
                *output_file = arg;
            } else {
                printf("Error, could not associate positional argument '%s'.\n\n", arg);
                print_help();
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char** argv) {
    char *input_file = "", *output_file = "";
    enum operation image_operation;

    parse_args(argc, argv, &input_file, &output_file, &image_operation);

    pgm_t *image = pgm_read(input_file);

    switch (image_operation) {
        case MIRROR_HORIZONTAL:
            mirrorHorizontal(image);
            break;
	    case MIRROR_VERTICALLY:
	        mirror_vertically(image);
            break;
        case INVERT:
            pgm_invert(image);
            break;
        case NO_OP:
        default:
            printf("Warning: no operation has been specified!\n");
            break;
    }

    pgm_write(image, output_file);

    pgm_free(image);
    return 0;
}
