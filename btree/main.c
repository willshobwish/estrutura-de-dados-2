#include "stdio.h"
#include "stdlib.h"
#include "btree.h"


int main(void) {
    ArvoreB r = malloc(sizeof(NoArvB));
    r->n = 1;
    r->chave[0] = 30;
    r->filho[0] = malloc(sizeof(NoArvB));
    r->filho[1] = malloc(sizeof(NoArvB));
    ArvoreB filhoA = r->filho[0];
    ArvoreB filhoB = r->filho[1];
    filhoA->n = 2;
    filhoA->chave[0] = 10;
    filhoA->chave[1] = 20;
    filhoB->n = 2;
    filhoB->chave[0] = 30;
    filhoB->chave[1] = 40;
    printf("%d", BuscaArvoreB(r, 40));
    return 0;
}