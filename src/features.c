#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void dimension(const char *source_path)
{
    unsigned char *pixels = NULL;
    int w = 0, h = 0, channels = 0;

    if (read_image_data(source_path, &pixels, &w, &h, &channels) != 0) {
        fputs("error: impossible de charger l’image « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }

    printf("dimension: %d, %d\n", w, h);
    free(pixels);
}

void first_pixel(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    int result = read_image_data(source_path, &data, &width, &height, &channels);
    if (result != 0) {
        printf("Error reading image\n");
        return;
    }
    if (channels < 3) {
        printf("Need at least 3 channels\n");
        free(data);
        return;
    }
    int r = data[0];
    int g = data[1];
    int b = data[2];
    printf("first_pixel: %d, %d, %d\n", r, g, b);
    free(data);
}

void tenth_pixel(char *source_path) {
    unsigned char *data;
    int width, height, channels;
    int result = read_image_data(source_path, &data, &width, &height, &channels);
    if (result != 0) {
        printf("Error reading image\n");
        return;
    }
    if (channels < 3) {
        printf("Need at least 3 channels\n");
        free(data);
        return;
    }
    if (width < 10) {
        printf("Image must be at least 10 pixels wide\n");
        free(data);
        return;
    }
    int pixel_index = 9 * channels;
    int r = data[pixel_index];
    int g = data[pixel_index + 1];
    int b = data[pixel_index + 2];
    printf("tenth_pixel: %d, %d, %d\n", r, g, b);
    free(data);
}

void second_line(const char *source_path)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, c = 0;
    if (read_image_data(source_path, &data, &w, &h, &c) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int offset = w * c;
    int r = data[offset];
    int g = data[offset + 1];
    int b = data[offset + 2];
    printf("second_line: %d, %d, %d\n", r, g, b);
    free(data);
}

void max_pixel(const char *source_path)
{
    unsigned char *data = NULL;
    int w = 0, h = 0, ch = 0;
    if (read_image_data(source_path, &data, &w, &h, &ch) != 0) {
        fputs("error: impossible de charger « ", stderr);
        fputs(source_path, stderr);
        fputs(" »\n", stderr);
        return;
    }
    int max_sum = -1;
    int max_x = 0, max_y = 0, r = 0, g = 0, b = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * ch;
            int rr = data[idx];
            int gg = data[idx + 1];
            int bb = data[idx + 2];
            int sum = rr + gg + bb;
            if (sum > max_sum) {
                max_sum = sum;
                max_x = x; max_y = y;
                r = rr; g = gg; b = bb;
            }
        }
    }
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, r, g, b);
    free(data);
}