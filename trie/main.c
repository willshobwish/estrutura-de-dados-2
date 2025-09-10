#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    No *arvore;
    
    // Initialize the tree
    inicializa(&arvore);
    
    // Insert some values
    printf("Inserting values: 10, 5, 15, 12\n\n");
    insere(&arvore, 10);
    insere(&arvore, 5);
    insere(&arvore, 15);
    insere(&arvore, 12);
    
    // Print the trie structure
    imprime_trie(arvore, 0);
    printf("\n");
    
    // Search for values
    unsigned valores_teste[] = {10, 5, 15, 12, 7, 20};
    int num_testes = sizeof(valores_teste) / sizeof(valores_teste[0]);
    
    for (int i = 0; i < num_testes; i++) {
        No *resultado = busca(arvore, valores_teste[i]);
        if (resultado != NULL) {
            printf("Found: %u\n", valores_teste[i]);
        } else {
            printf("Not found: %u\n", valores_teste[i]);
        }
    }
    
    return 0;
}