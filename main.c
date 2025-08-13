#include "stdio.h"
#include "stdlib.h"

#define MAX 2

typedef struct No {
    int n;
    int folha;
    int chave[MAX];
    struct No *filho[MAX + 1];
} NoArvB, *ArvoreB;

int BuscaArvoreB(ArvoreB r, int k) {
    int i = 1;
    while (i <= r->n && k > r->chave[i]) {
        i++;
    }
    if (i <= r->n && k == r->chave[i]) {
        return r->chave[i];
    } else {
        return BuscaArvoreB(r->filho[i], k);
    }
}

int main(void) {
    ArvoreB r = malloc(sizeof(NoArvB));
    r->n=1;
    r->chave[0]=30;
    r->filho[0]=malloc(sizeof(NoArvB));
    r->filho[1]=malloc(sizeof(NoArvB));
    ArvoreB filhoA = r->filho[0];
    ArvoreB filhoB = r->filho[1];
    filhoA->n=2;
    filhoA->chave[0]=10;
    filhoA->chave[1]=20;
    filhoB->n=2;
    filhoB->chave[0]=30;
    filhoB->chave[1]=40;
    // printf("%d",r->chave[0]);
    // printf("%d",r->filho[0]->chave[0]);
    // printf("%d",r->chave[0]);
    // printf("%d",r->chave[0]);
 BuscaArvoreB(r,40);
    return 0;
}