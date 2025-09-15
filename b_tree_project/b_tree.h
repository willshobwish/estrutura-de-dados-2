#ifndef BTREE_H
#define BTREE_H

#include "pixel_data.h"
// O maximo tem que ser no minimo 3 porque t>=2, 2t-2 => 2*2-1 = 3
#define MAX 1000


typedef struct No {
    int n;                 
    int folha;             
    int chave[MAX];        
    PixelData pixel[MAX];  
    struct No *filho[MAX + 1];
} NoArvB, *ArvoreB;

PixelData BuscaArvoreB(ArvoreB r, int k);
ArvoreB InsereArvoreB(ArvoreB r, int k, PixelData px);
void RemoveArvoreB(ArvoreB r, int k);
NoArvB *AllocateNode();
void InsereNaoCheioArvoreB(ArvoreB x, int k, PixelData px);
void PrintBTree(ArvoreB r, int level);
#endif