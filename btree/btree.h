#ifndef BTREE_H
#define BTREE_H

#define MAX 3

typedef struct No {
    int n;
    int folha;
    int chave[MAX];
    struct No *filho[MAX + 1];
} NoArvB, *ArvoreB;

int BuscaArvoreB(ArvoreB r, int k);
ArvoreB InsereArvoreB(ArvoreB r, int k);
void RemoveArvoreB(ArvoreB r, int k);
NoArvB *AllocateNode();
void SplitChildArvoreB(NoArvB *x, int i);
void InsereNaoCheioArvoreB(ArvoreB x, int k);
void PrintBTree(ArvoreB r, int level);
#endif 