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