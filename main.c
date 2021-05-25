#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

/**
 * Intern representation of an image.
 * You do *not* need to modify this.
 **/
typedef struct image {
    int w;
    int h;
    int maxValue;
    int* data;
} *Image;

/**
 * Read a plain PGM (P2) image from stdin and returns it as Image pointer.
 * You do *not* need to modify this.
 */
Image read_image() {
    int i = 0, value, ptr;
    Image img = malloc( sizeof(struct image) );
    img->w = -1;
    img->h = -1;
    img->maxValue = -1;

    // 1. discard the magic number
    while ( (ptr = getc(stdin)) != EOF ) {
        if (ptr == '#') while ( getc(stdin) != '\n' ); // discard comment line
        if (ptr == 'P') { getc(stdin); break; }
    }

    // 2. read the image data
    while ( (ptr = getc(stdin)) != EOF ) {
        if (ptr == '#') while ( getc(stdin) != '\n' ); // discard comment line
        if (scanf("%d", &value) <= 0) continue;
        if (img->w < 0) { img->w = value; continue; }
        if (img->h < 0) {
            img->h = value;
            img->data = malloc( img->w * img->h * sizeof(int) );
            continue;
        }
        if (img->maxValue < 0) { img->maxValue = value; continue; }
        img->data[i++] = value;
    }

    return img;
}

/**
 * Write an intern image to stdout as plain PGM (P2) image.
 * You do *not* need to modify this.
 */
void write_image(Image img) {
    printf("P2 %d %d %d\n", img->w, img->h, img->maxValue);
    for (int i = 0; i < img->w * img->h; i++) {
        printf("%d\n", img->data[i]);
    }
}

/*
 * Replace the image by black and white lines.
 */
void not_a_feature(Image img) {
    int h = img->h;
    int w = img->w;

    // the image data can be traversed by two for-loops
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (y % 2 == 0) {
                img->data[y*h+x] = 0;
            } else {
                img->data[y*h+x] = img->maxValue;
            }
        }
    }

    // alternatively, one may use only one for-loop
    // (this code does the same as the code above)
    for (int i = 0; i < h*w; i++) {
        int x = i / w, y = i % w;
        if (y % 2 == 0) {
            img->data[y*img->h+x] = 0;
        } else {
            img->data[y*img->h+x] = img->maxValue;
        }
    }
}

int main(int argc, char** argv) {

    // read image from stdin
    Image img = read_image();

    /*
     * This function replaces the image by black and white lines.
     * Add program logic and features instead.
     */
    not_a_feature(img);

    // write result to stdout
    write_image(img);

    // clean up
    free(img->data);
    free(img);
    return 0;
}