#include "pixel_data.h"
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"   

int main(void) {
    size_t pixel_count;
    PixelData* pixels = read_pixel_array("pixels.bin", &pixel_count);

    if (!pixels) {
        printf("Failed to load pixels from file.\n");
        return 1;
    }

    if (pixel_count == 0) {
        printf("No pixels to reconstruct.\n");
        free(pixels);
        return 1;
    }

    int width = pixels[0].width;
    int height = pixels[0].height;

    unsigned char* img = malloc(width * height * 3);
    if (!img) {
        perror("Failed to allocate image buffer");
        free(pixels);
        return 1;
    }

    for (size_t i = 0; i < pixel_count; i++) {
        int idx = pixels[i].index * 3;
        img[idx]     = pixels[i].R;
        img[idx + 1] = pixels[i].G;
        img[idx + 2] = pixels[i].B;
    }

    if (!stbi_write_png("reconstructed.png", width, height, 3, img, width * 3)) {
        printf("Failed to save image.\n");
    } else {
        printf("Image saved to 'reconstructed.png'.\n");
    }

    free(img);
    free(pixels);
    return 0;
}
