#include "pixel_data.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t pixel_count;
    PixelData* pixels = read_pixel_array("pixels.bin", &pixel_count);

    if (!pixels) {
        printf("Failed to load pixels from file.\n");
        return 1;
    }

    printf("Loaded %zu pixels from file.\n", pixel_count);

    // Example: print first 10 pixels
    for (size_t i = 0; i < pixel_count && i < 10; i++) {
        printf("Pixel %zu Index %d: R=%u G=%u B=%u\n", i, pixels[i].index, pixels[i].R, pixels[i].G, pixels[i].B);
    }

    free(pixels);
    return 0;
}
