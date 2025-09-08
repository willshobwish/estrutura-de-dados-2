#ifndef PATRICIA_TRIE_H
#define PATRICIA_TRIE_H
#define bits_na_chave 32

typedef struct No {
    unsigned chave;
    int bit;
    struct No *esq, *dir;
} No;

void inicializa(No **arvore);
unsigned bit(unsigned chave, int k);
No *busca(No *arvore, unsigned x);
No *busca_rec(No *arvore, unsigned x, int w);
void insere(No **arvore, unsigned chave);
No *insere_rec(No *arvore, unsigned chave, int w, No *pai);

#endif