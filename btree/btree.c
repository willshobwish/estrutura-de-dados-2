#include "btree.h"

int BuscaArvoreB(ArvoreB r, int k) {
    int i = 0;
    while (i <= r->n && k > r->chave[i]) {
        i++;
    }
    if (i <= r->n && k == r->chave[i]) {
        return r->chave[i];
    } else {
        return BuscaArvoreB(r->filho[i], k);
    }
}
