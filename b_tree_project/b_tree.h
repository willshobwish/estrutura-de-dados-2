#ifndef BTREE_H
#define BTREE_H

#include "pixel_data.h"
// O maximo tem que ser no minimo 3 porque t>=2, 2t-2 => 2*2-1 = 3
#define MAX 1000

// typedef struct No {
//     int n;                     // Number of keys in the node
//     int folha;                  // Is leaf (1) or not (0)
//     int chave[MAX];             // Keys
//     PixelData pixel[MAX];       // Data associated with each key
//     struct No *filho[MAX + 1]; // Child pointers
// } NoArvB, *ArvoreB;

typedef struct No {
    int n;                     // Number of keys in the node
    int folha;                  // Is leaf (1) or not (0)
    int chave[MAX];             // Keys
    PixelData pixel[MAX];       // Data associated with each key
    unsigned filho[MAX + 1]; // Child pointers
} NoArvB, *ArvoreB;


int BuscaArvoreB(ArvoreB r, int k);
ArvoreB InsereArvoreB(ArvoreB r, int k, PixelData px);
void RemoveArvoreB(ArvoreB r, int k);
NoArvB *AllocateNode();
// void SplitChildArvoreB(NoArvB *x, int i);
void InsereNaoCheioArvoreB(ArvoreB x, int k, PixelData px, int is_root);
void PrintBTree(ArvoreB r, int level);
#endif 