#ifndef TRIE_H
#define TRIE_H
#define bits_na_chave 32

typedef struct No {
    unsigned chave;      // Only meaningful in leaf nodes
    int bit;            // Bit position being tested (for internal nodes)
    int is_leaf;        // Flag to indicate if this is a leaf node
    struct No *esq, *dir;
} No;

void inicializa(No **arvore);
No *busca(No *arvore, unsigned x);
void insere(No **arvore, unsigned chave);
void imprime_trie(No *arvore, int nivel);
int eh_folha(No *no);

#endif