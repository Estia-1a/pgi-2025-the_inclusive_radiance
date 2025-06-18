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