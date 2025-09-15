#include "b_tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

PixelData BuscaArvoreB(ArvoreB r, int k) {
    PixelData pixel;
    pixel.index = -1;
    if (r == NULL) {
        return pixel;  
    }

    int i = 0;
    while (i < r->n && k > r->chave[i]) {
        i++;
    }

    if (i < r->n && k == r->chave[i]) {
        return r->pixel[i];
    } else if (r->folha) {
        return pixel;  
    } else {
        return BuscaArvoreB(r->filho[i], k);
    }
}

NoArvB *AllocateNode() {
    NoArvB *z = malloc(sizeof(NoArvB));
    if (!z) return NULL;
    z->n = 0;
    z->folha = 1;
    for (int j = 0; j < MAX + 1; j++) {
        z->filho[j] = NULL;
    }
    return z;
}

void SplitChildArvoreB(NoArvB *x, int i) {
    int t = (MAX + 1) / 2;
    NoArvB *z = AllocateNode();
    NoArvB *y = x->filho[i];
    z->folha = y->folha;
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
        z->pixel[j] = y->pixel[j + t];  
    }
    if (y->folha == 0) {
        for (int j = 0; j < t; j++) {
            z->filho[j] = y->filho[j + t];
        }
    }

    y->n = t - 1;

    
    for (int j = x->n; j >= i + 1; j--) {
        x->filho[j + 1] = x->filho[j];
    }
    x->filho[i + 1] = z;


    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pixel[j + 1] = x->pixel[j];  
    }


    x->chave[i] = y->chave[t - 1];
    x->pixel[i] = y->pixel[t - 1]; 
    x->n = x->n + 1;
}

void InsereNaoCheioArvoreB(ArvoreB x, int k, PixelData px) {

    int t = (MAX + 1) / 2;
    int i = x->n - 1;

    if (x->folha) {

        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pixel[i + 1] = x->pixel[i];
            i--;
        }
    
        x->chave[i + 1] = k;
        x->pixel[i + 1] = px;
        x->n++;
    } else {

        while (i >= 0 && k < x->chave[i]) {
            i--;
        }
        i++;  


        if (x->filho[i]->n == 2 * t - 1) {  
            SplitChildArvoreB(x, i);
            if (k > x->chave[i]) {
                i++;
            }
        }

        InsereNaoCheioArvoreB(x->filho[i], k, px);
    }
}

ArvoreB InsereArvoreB(ArvoreB r, int k, PixelData px) {
   
    int t = (MAX + 1) / 2;
    if (r->n == 2 * t - 1) {
        NoArvB *s = AllocateNode();
        s->folha = 0;
        s->n = 0;
        s->filho[0] = r;
        SplitChildArvoreB(s, 0);          
        InsereNaoCheioArvoreB(s, k, px);  
        return s;
    } else {
        InsereNaoCheioArvoreB(r, k, px);
        return r;
    }
}

void PrintBTree(ArvoreB r, int level) {
    if (r != NULL) {
        printf("Level %d: [", level);
        for (int i = 0; i < r->n; i++) {
            printf("%d", r->chave[i]);
            if (i < r->n - 1) printf(", ");
        }
        printf("] (folha: %s)\n", r->folha ? "yes" : "no");

        if (!r->folha) {
            for (int i = 0; i <= r->n; i++) {
                PrintBTree(r->filho[i], level + 1);
            }
        }
    }
}