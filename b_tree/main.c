#include "b_tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "random_array_generator.h"


int main(void) {
    ArvoreB r = AllocateNode();
    r->folha = 1;
    r->n = 0;
    int *array = RandomArrayGenerator(200,0,10000);
    for (int i = 0; i < 100; i++) {
        r = InsereArvoreB(r, array[i]);
    }
    PrintBTree(r, 0);
    return 0;
}