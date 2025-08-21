#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct {
    unsigned int index;
    unsigned int height;
    unsigned int width;
    unsigned char R;
    unsigned char G;
    unsigned char B;
} PixelData;

int main(void) {
    int width, height, channels;
    unsigned char *img = stbi_load("ISIC_0024329.jpg", &width, &height, &channels,0);

    if (!img) {
        printf("Failed to load image\n");
        return 1;
    }

    printf("Image size: %dx%d, Channels: %d\n", width, height, channels);
    int i=0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channels;
            // printf("[%d,%d]", y, x);
            printf("%d",i);
            if (channels >= 1) printf(" R:%d", img[idx + 0]);
            if (channels >= 2) printf(" G:%d", img[idx + 1]);
            if (channels >= 3) printf(" B:%d", img[idx + 2]);
            if (channels == 4) printf(" A:%d", img[idx + 3]);
            printf("\n");
            i++;
        }
    }
    stbi_image_free(img);
    return 0;
}