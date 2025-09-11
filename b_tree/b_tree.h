#ifndef BTREE_H
#define BTREE_H
// O maximo tem que ser no minimo 3 porque t>=2, 2t-2 => 2*2-1 = 3
#define MAX 3

typedef struct No {
    int n;
    int folha;
    int chave[MAX];
    struct No *filho[MAX + 1];
} NoArvB, *ArvoreB;
ArvoreB RemoveArvoreB(ArvoreB root, int k);
int BuscaArvoreB(ArvoreB r, int k);
ArvoreB InsereArvoreB(ArvoreB r, int k);
NoArvB *AllocateNode();
void SplitChildArvoreB(NoArvB *x, int i);
void InsereNaoCheioArvoreB(ArvoreB x, int k);
void PrintBTree(ArvoreB r, int level);
#endif 