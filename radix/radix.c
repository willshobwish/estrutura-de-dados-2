#include "radix.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void inicializa(No **arvore) {
    *arvore = malloc(sizeof(No));
    (*arvore)->chave = UINT_MAX;
    (*arvore)->esq = NULL;
    (*arvore)->dir = NULL;
    (*arvore)->bit = -1;
}

unsigned bit(unsigned chave, int k) {
    return chave >> (bits_na_chave - 1 - k) & 1;
}

No *busca_rec(No *arvore, unsigned x, int nivel) {
    if (arvore == NULL) {
        return NULL;
    }
    if (x == arvore->chave) {
        return arvore;
    }
    if (bit(x, nivel) == 0) {
        return busca_rec(arvore->esq, x, nivel + 1);

    } else {
        return busca_rec(arvore->dir, x, nivel + 1);
    }
}

No *busca(No *arvore, unsigned x) {
    return busca_rec(arvore, x, 0);
}

No *insere_rec(No *arvore, unsigned chave, int nivel) {
    No *novo;
    if (arvore == NULL) {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->chave = chave;
        return novo;
    }
    if (chave == arvore->chave) {
        return arvore;
    }
    if (bit(chave, nivel) == 0) {
        arvore->esq = insere_rec(arvore->esq, chave, nivel + 1);
    } else {
        arvore->dir = insere_rec(arvore->dir, chave, nivel + 1);
    }
    return arvore;
}

void insere(No **arvore, unsigned chave) {
    *arvore = insere_rec(*arvore, chave, 0);
}