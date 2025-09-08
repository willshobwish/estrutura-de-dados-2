#include "patricia_trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void inicializa(No **arvore) {
    *arvore = malloc(sizeof(No));
    (*arvore)->chave = UINT_MAX;
    (*arvore)->esq = (*arvore)->dir = *arvore;
    (*arvore)->bit = -1;
}

unsigned bit(unsigned chave, int k) {
    return chave >> (bits_na_chave - 1 - k) & 1;
}

No *busca(No *arvore, unsigned x) {
    No *t = busca_rec(arvore->esq, x, -1);
    return t->chave == x ? t : NULL;
}

No *busca_rec(No *arvore, unsigned x, int w) {
    if (arvore->bit <= w) {
        return arvore;
    }
    if (bit(x, arvore->bit) == 0) {
        return busca_rec(arvore->esq, x, arvore->bit);
    } else {
        return busca_rec(arvore->dir, x, arvore->bit);
    }
}
void insere(No **arvore, unsigned chave) {
    int i;
    No *t = busca_rec((*arvore)->esq, chave, -1);
    if (chave == t->chave) return;
    for (i = 0; bit(chave, i) == bit(t->chave, i); i++);
    (*arvore)->esq = insere_rec((*arvore)->esq, chave, i, *arvore);
}

No *insere_rec(No *arvore, unsigned chave, int w, No *pai) {
    if ((arvore->bit >= w) || (arvore->bit <= pai->bit)) {
        // cria nó novo
        No *novo = malloc(sizeof(No));
        novo->chave = chave;
        novo->bit = w;
        if (bit(chave, novo->bit) == 1) {
            novo->esq = arvore;
            novo->dir = novo;
        } else {
            novo->esq = novo;
            novo->dir = arvore;
        }
        return novo;
    }

    // recursão (se não entrou no if)
    if (bit(chave, arvore->bit) == 0) {
        arvore->esq = insere_rec(arvore->esq, chave, w, arvore);
    } else {
        arvore->dir = insere_rec(arvore->dir, chave, w, arvore);
    }

    return arvore; // garante retorno em todos os caminhos
}