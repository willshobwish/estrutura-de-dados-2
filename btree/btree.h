#ifndef BTREE_H
#define BTREE_H

#define MAX 2

typedef struct No {
    int n;
    int folha;
    int chave[MAX];
    struct No *filho[MAX + 1];
} NoArvB, *ArvoreB;

int BuscaArvoreB(ArvoreB r, int k);
void InsereArvoreB(ArvoreB r, int k);
void RemoveArvoreB(ArvoreB r, int k);

#endif 