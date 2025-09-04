#include "btree.h"
#include "stdio.h"
#include "stdlib.h"


int main(void) {
    ArvoreB r = AllocateNode();
    r->folha = 1;
    r->n = 0;
    for(int i=0;i<100;i++){
        r=InsereArvoreB(r,i);
    }
    // for(int i=0;i<100;i++){
        // BuscaArvoreB(r,i);
    // }
    PrintBTree(r,0);
    return 0;
}