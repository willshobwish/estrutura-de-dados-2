#include "radix.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    No *arvore;  // Declare as pointer to No, not No itself
    
    // Initialize the tree properly
    inicializa(&arvore);
    
    // Insert a value
    insere(&arvore, 10);
    
    // Search for the value
    No *resultado = busca(arvore, 10);
    
    if (resultado != NULL) {
        printf("Found: %u\n", resultado->chave);
    } else {
        printf("Not found\n");
    }
    
    return 0;
}