#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "pixel_data.h"

int main(void) {
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

    write_pixel_array("pixels.bin", pixels, pixel_count);
    printf("Saved %zu pixels to pixels.bin\n", pixel_count);

    free(pixels);
    stbi_image_free(img);
    return 0;
}
