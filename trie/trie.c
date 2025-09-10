#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void inicializa(No **arvore) {
    *arvore = NULL;  // Start with empty tree
}

unsigned bit(unsigned chave, int k) {
    return (chave >> (bits_na_chave - 1 - k)) & 1;
}

int eh_folha(No *no) {
    return no != NULL && no->is_leaf;
}

No *criar_no_interno(int bit_pos) {
    No *novo = malloc(sizeof(No));
    novo->chave = 0;        // Not meaningful for internal nodes
    novo->bit = bit_pos;
    novo->is_leaf = 0;      // This is an internal node
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *criar_folha(unsigned chave) {
    No *novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->bit = -1;         // Not meaningful for leaf nodes
    novo->is_leaf = 1;      // This is a leaf node
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Find the first bit position where two keys differ
int primeiro_bit_diferente(unsigned chave1, unsigned chave2) {
    unsigned xor_result = chave1 ^ chave2;
    if (xor_result == 0) return -1; // Keys are identical
    
    int bit_pos = 0;
    while (bit_pos < bits_na_chave) {
        if (bit(xor_result, bit_pos) == 1) {
            return bit_pos;
        }
        bit_pos++;
    }
    return -1;
}

No *busca_rec(No *arvore, unsigned x, int nivel) {
    if (arvore == NULL) {
        return NULL;
    }
    
    // If we reached a leaf, check if it matches
    if (eh_folha(arvore)) {
        return (arvore->chave == x) ? arvore : NULL;
    }
    
    // Internal node: follow the appropriate branch based on the bit
    if (bit(x, arvore->bit) == 0) {
        return busca_rec(arvore->esq, x, nivel + 1);
    } else {
        return busca_rec(arvore->dir, x, nivel + 1);
    }
}

No *busca(No *arvore, unsigned x) {
    return busca_rec(arvore, x, 0);
}

No *insere_rec(No *arvore, unsigned chave, int nivel) {
    // If tree is empty, create a leaf
    if (arvore == NULL) {
        return criar_folha(chave);
    }
    
    // If we reached a leaf
    if (eh_folha(arvore)) {
        // If the key already exists, return the existing node
        if (arvore->chave == chave) {
            return arvore;
        }
        
        // Keys are different, we need to create an internal node
        int bit_diff = primeiro_bit_diferente(arvore->chave, chave);
        
        if (bit_diff == -1) {
            // This shouldn't happen as we already checked for equality
            return arvore;
        }
        
        // Create a new internal node at the differing bit position
        No *novo_interno = criar_no_interno(bit_diff);
        No *nova_folha = criar_folha(chave);
        
        // Determine which child goes where based on the differing bit
        if (bit(arvore->chave, bit_diff) == 0) {
            novo_interno->esq = arvore;
            novo_interno->dir = nova_folha;
        } else {
            novo_interno->esq = nova_folha;
            novo_interno->dir = arvore;
        }
        
        return novo_interno;
    }
    
    // Internal node: continue recursion
    if (bit(chave, arvore->bit) == 0) {
        arvore->esq = insere_rec(arvore->esq, chave, nivel + 1);
    } else {
        arvore->dir = insere_rec(arvore->dir, chave, nivel + 1);
    }
    
    return arvore;
}

void insere(No **arvore, unsigned chave) {
    *arvore = insere_rec(*arvore, chave, 0);
}

// Helper function to print the trie structure
void imprime_trie_rec(No *arvore, int profundidade) {
    if (arvore == NULL) {
        return;
    }
    
    // Print indentation
    for (int i = 0; i < profundidade; i++) {
        printf("  ");
    }
    
    if (eh_folha(arvore)) {
        printf("LEAF: %u\n", arvore->chave);
    } else {
        printf("INTERNAL (bit %d)\n", arvore->bit);
        if (arvore->esq != NULL) {
            for (int i = 0; i < profundidade + 1; i++) printf("  ");
            printf("0->\n");
            imprime_trie_rec(arvore->esq, profundidade + 2);
        }
        if (arvore->dir != NULL) {
            for (int i = 0; i < profundidade + 1; i++) printf("  ");
            printf("1->\n");
            imprime_trie_rec(arvore->dir, profundidade + 2);
        }
    }
}

void imprime_trie(No *arvore, int nivel) {
    printf("Trie structure:\n");
    imprime_trie_rec(arvore, 0);
}