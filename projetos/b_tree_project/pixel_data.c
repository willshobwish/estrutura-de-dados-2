/**
 * @file pixel_data_utils.c
 * @brief Implementação de utilitários para PixelData e reconstrução de imagem.
 *
 * Este arquivo contém funções para embaralhar pixels, ler/gravar arrays de
 * PixelData em arquivo binário e reconstruir uma imagem PNG a partir desses
 * pixels usando stb_image_write.
 */

#include "pixel_data.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/**
 * @brief Embaralha um array de PixelData usando o algoritmo de Fisher–Yates.
 *
 * @param pixels Ponteiro para o array de PixelData.
 * @param count Número de elementos no array.
 */
void shuffle_pixels(PixelData* pixels, size_t count) {
    for (size_t i = count - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        PixelData tmp = pixels[i];
        pixels[i] = pixels[j];
        pixels[j] = tmp;
    }
}

/**
 * @brief Grava um array de PixelData em arquivo binário.
 *
 * Formato: [size_t count][PixelData x count]
 *
 * @param filename Caminho do arquivo de saída.
 * @param pixels Ponteiro para o array de PixelData.
 * @param count Quantidade de elementos a gravar.
 */
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

/**
 * @brief Lê um array de PixelData de um arquivo binário.
 *
 * @param filename Caminho do arquivo de entrada.
 * @param out_count Ponteiro para armazenar o número de pixels lidos.
 * @return Ponteiro para um array alocado de PixelData; NULL em caso de erro.
 */
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

/**
 * @brief Reconstrói uma imagem PNG a partir de um arquivo de PixelData.
 *
 * @param input_file Arquivo binário contendo o array de PixelData.
 * @param output_file Caminho do PNG a ser gravado.
 * @return 1 em sucesso, 0 em caso de falha.
 */
int reconstruct_image_from_pixels(const char* input_file, const char* output_file) {
    size_t pixel_count;
    PixelData* pixels = read_pixel_array(input_file, &pixel_count);
    if (!pixels || pixel_count == 0) {
        if (!pixels) fprintf(stderr, "Failed to load pixels from '%s'.\n", input_file);
        else fprintf(stderr, "No pixels to reconstruct in '%s'.\n", input_file);
        free(pixels);
        return 0;
    }

    int width = pixels[0].width;
    int height = pixels[0].height;
    unsigned char* img = malloc(width * height * 3);
    if (!img) {
        perror("Failed to allocate image buffer");
        free(pixels);
        return 0;
    }

    for (size_t i = 0; i < pixel_count; i++) {
        int idx = pixels[i].index * 3;
        img[idx]     = pixels[i].R;
        img[idx + 1] = pixels[i].G;
        img[idx + 2] = pixels[i].B;
    }

    int success = stbi_write_png(output_file, width, height, 3, img, width * 3);
    if (!success) fprintf(stderr, "Failed to save image to '%s'.\n", output_file);
    else printf("Image saved to '%s'.\n", output_file);

    free(img);
    free(pixels);
    return success;
}