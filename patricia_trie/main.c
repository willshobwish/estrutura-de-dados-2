#include <stdio.h>
#include <stdlib.h>
#include "patricia_trie.h"

int main(void) {
    No *arvore;
    inicializa(&arvore);      // inicializa raiz
    // insere(&arvore, 10);      // insere valor
    // No *resultado = busca(arvore, 10); // busca valor
    // if (resultado != NULL) {
    //     printf("%u\n", resultado->chave); // imprime
    // } else {
    //     printf("Nao encontrado\n");
    // }
    // return 0;
    int value = 10000;
    for(int i=0;i<value;i++){
        insere(&arvore, i);
    }
    for(int i=0;i<value;i++){
        No *resultado = busca(arvore, i);
        printf("\n\nChave:%u\nBit: %d\nEsquerdo: %d\nDireito: %d",resultado->chave,resultado->bit,resultado->dir->chave,resultado->esq->chave);
    }
}
