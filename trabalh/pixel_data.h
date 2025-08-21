#ifndef PIXEL_DATA_H
#define PIXEL_DATA_H

#include <stdio.h>

typedef struct {
    unsigned int index;
    unsigned int height;
    unsigned int width;
    unsigned char R;
    unsigned char G;
    unsigned char B;
} PixelData;

// Functions to write/read PixelData arrays
void write_pixel_array(const char* filename, PixelData* pixels, size_t count);
PixelData* read_pixel_array(const char* filename, size_t* out_count);

#endif
