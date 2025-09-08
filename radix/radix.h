#ifndef RADIX_H
#define RADIX_H
#define bits_na_chave 32

typedef struct No {
    unsigned chave;
    int bit;
    struct No *esq, *dir;
} No;

void inicializa(No **arvore);
No *busca(No *arvore, unsigned x);
void insere(No **arvore, unsigned chave);
#endif