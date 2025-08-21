#include "pixel_data.h"
#include <stdlib.h>

void write_pixel_array(const char* filename, PixelData* pixels, size_t count) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Cannot open file for writing");
        return;
    }

    fwrite(&count, sizeof(size_t), 1, fp);
    fwrite(pixels, sizeof(PixelData), count, fp);
    fclose(fp);
}

PixelData* read_pixel_array(const char* filename, size_t* out_count) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("Cannot open file for reading");
        *out_count = 0;
        return NULL;
    }

    fread(out_count, sizeof(size_t), 1, fp);

    PixelData* pixels = malloc(sizeof(PixelData) * (*out_count));
    if (!pixels) {
        fclose(fp);
        *out_count = 0;
        return NULL;
    }

    fread(pixels, sizeof(PixelData), *out_count, fp);
    fclose(fp);

    return pixels;
}
