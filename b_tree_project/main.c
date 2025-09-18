/**
 * @file main.c
 * @brief Programa principal para ler uma imagem, embaralhar pixels, armazenar em Árvore B e reconstruir a imagem.
 *
 * O programa carrega uma imagem PNG, transforma em PixelData, embaralha os pixels, insere
 * na Árvore B, e em seguida reconstrói a imagem a partir da Árvore B, salvando como PNG.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "b_tree.h"
#include "pixel_data.h"
#include "random_array_generator.h"

#ifndef STB_IMAGE_H
unsigned char *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
void stbi_image_free(void *retval_from_stbi_load);
int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
#endif

/**
 * @brief Função principal.
 *
 * Carrega a imagem, converte para PixelData, embaralha, insere na Árvore B,
 * reconstrói a imagem e salva em arquivo.
 *
 * @return 0 se sucesso, 1 em caso de falha.
 */
int main(void) {
    srand(time(NULL));

    int width, height, channels;
    unsigned char *img = stbi_load("Labrador Retriever.png", &width, &height, &channels, 3);
    if (!img) {
        printf("Failed to load image\n");
        return 1;
    }

    size_t pixel_count = width * height;
    PixelData *pixels = malloc(sizeof(PixelData) * pixel_count);
    if (!pixels) {
        stbi_image_free(img);
        return 1;
    }

    // Converter a imagem em PixelData
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            PixelData *p = &pixels[y * width + x];
            p->index = y * width + x;
            p->height = height;
            p->width = width;
            p->R = img[idx];
            p->G = img[idx + 1];
            p->B = img[idx + 2];
        }
    }

    shuffle_pixels(pixels, pixel_count);

    // Criar árvore B e inserir pixels
    ArvoreB r = AllocateNode();
    if (!r) {
        printf("Failed to allocate root node\n");
        free(pixels);
        stbi_image_free(img);
        return 1;
    }
    r->folha = 1;
    r->n = 0;
    for (size_t i = 0; i < pixel_count; i++) {
        r = InsereArvoreB(r, pixels[i].index, pixels[i]);
    }

    // Reconstruir imagem a partir da árvore
    PixelData *recreateImage = malloc(sizeof(PixelData) * pixel_count);
    if (!recreateImage) {
        printf("Failed to allocate memory for recreateImage\n");
        free(pixels);
        stbi_image_free(img);
        return 1;
    }
    for (size_t i = 0; i < pixel_count; i++) {
        recreateImage[i] = BuscaArvoreB(r, pixels[i].index);
        if (recreateImage[i].index == (unsigned int)-1) {
            printf("Warning: Failed to find pixel with index %u\n", pixels[i].index);
        }
    }

    unsigned char *imageArr = malloc(width * height * 3);
    if (!imageArr) {
        printf("Failed to allocate memory for imageArr\n");
        free(pixels);
        free(recreateImage);
        stbi_image_free(img);
        return 1;
    }

    for (size_t i = 0; i < pixel_count; i++) {
        int idx = recreateImage[i].index * 3;
        imageArr[idx] = recreateImage[i].R;
        imageArr[idx + 1] = recreateImage[i].G;
        imageArr[idx + 2] = recreateImage[i].B;
    }

    if (!stbi_write_png("reconstructed.png", width, height, 3, imageArr, width * 3)) {
        printf("Failed to save image.\n");
    } else {
        printf("Image saved to 'reconstructed.png'.\n");
    }

    free(pixels);
    free(recreateImage);
    free(imageArr);
    stbi_image_free(img);

    return 0;
}
