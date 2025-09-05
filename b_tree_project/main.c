#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "b_tree.h"
#include "random_array_generator.h"
#include "pixel_data.h"

// Add the stb_image declaration since it's not in your headers
#ifndef STB_IMAGE_H
unsigned char *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
void stbi_image_free(void *retval_from_stbi_load);
#endif

int main(void) {
    srand(time(NULL));

    int width, height, channels;
    unsigned char* img = stbi_load("ISIC_0024329.jpg", &width, &height, &channels, 3); // force RGB
    if (!img) {
        printf("Failed to load image\n");
        return 1;
    }

    size_t pixel_count = width * height;
    PixelData* pixels = malloc(sizeof(PixelData) * pixel_count);
    if (!pixels) {
        stbi_image_free(img);
        return 1;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            PixelData* p = &pixels[y * width + x];
            p->index = y * width + x;
            p->height = height;
            p->width = width;
            p->R = img[idx];
            p->G = img[idx + 1];
            p->B = img[idx + 2];
        }
    }

    shuffle_pixels(pixels, pixel_count);

    // for(int i=0;i<10;i++){
    //     printf("%d\n",pixels[i].index);
    // }
    ArvoreB r = AllocateNode();

    if (!r) {
        printf("Failed to allocate root node\n");
        free(pixels);
        stbi_image_free(img);
        return 1;
    }

    r->folha = 1;
    r->n = 0;
    
    // Fixed function call - was missing parameter
    for (int i = 0; i < pixel_count; i++) {
        r = InsereArvoreB(r, pixels[i].index, pixels[i]);
    }
    
    PrintBTree(r, 0);
    // printf("AAA\n");
    
    // Clean up
    free(pixels);
    stbi_image_free(img);
    
    return 0;
}