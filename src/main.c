#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/pgm.h"

enum operation {
    NO_OP,
    MIRROR_VERTICALLY
};

void print_help() {
    // Print a simple help
    printf("Usage: editpgm [input.pgm [output.pgm]] [operation]\n"
           "\n"
           "The standard input/output is used if no file name is specified, respectively."
           "\n"
           "The following image operations are available:\n"
           "  --no-op\t\tdoes nothing to the image;\n"
           "\n"
           "  --help\t\tdisplays this help and exits;\n");
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
            } else if (0 == strcmp(arg, "--no-op")) {
                *op = NO_OP;
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
        case NO_OP:
            break;
	case MIRROR_VERTICALLY:
	    mirror_vertically(image);
	    break;
    }

    pgm_write(image, output_file);

    pgm_free(image);
    return 0;
}
