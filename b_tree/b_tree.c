#include "b_tree.h"
#include "stdlib.h"
#include "stdio.h"

int BuscaArvoreB(ArvoreB r, int k) {
    // printf("%d\n",r->n);
    if (r == NULL) {
        return -1; // Key not found
    }
    
    int i = 0;
    while (i < r->n && k > r->chave[i]) {
        i++;
    }
    
    if (i < r->n && k == r->chave[i]) {
        return r->chave[i];
    } else if (r->folha) {
        return -1; // Key not found and we're at a leaf
    } else {
        return BuscaArvoreB(r->filho[i], k);
    }
}

NoArvB *AllocateNode() {
    NoArvB *z = malloc(sizeof(NoArvB));
    if (!z) return NULL;
    z->n = 0;
    z->folha = 1;
    for (int j = 0; j < MAX + 1; j++) {
        z->filho[j] = NULL;
    }
    return z;
}

void SplitChildArvoreB(NoArvB *x, int i) {
    // int t = (int)ceil((float)MAX / 2.0);
    int t = (MAX+1)/2;
    NoArvB *z = AllocateNode();
    NoArvB *y = x->filho[i];
    z->folha = y->folha;
    z->n = t - 1;
    
    // Copy the last t-1 keys from y to z
    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
    }
    
    // If y is not a leaf, copy the last t children from y to z
    if (y->folha == 0) {
        for (int j = 0; j < t; j++) {
            z->filho[j] = y->filho[j + t];
        }
    }
    
    y->n = t - 1;
    
    // Shift x's children to make room for z
    for (int j = x->n; j >= i + 1; j--) {
        x->filho[j + 1] = x->filho[j];
    }
    x->filho[i + 1] = z;
    
    // Shift x's keys to make room for the median key
    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
    }
    
    // Move the median key from y to x
    x->chave[i] = y->chave[t - 1];
    x->n = x->n + 1;
}

void InsereNaoCheioArvoreB(ArvoreB x, int k) {
    // int t = (int)ceil((float)MAX / 2.0);
    int t = (MAX+1)/2;
    int i = x->n - 1;
    
    if (x->folha) {
        // Shift keys greater than k to the right
        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            i--;
        }
        // Insert the key
        x->chave[i + 1] = k;
        x->n++;
    } else {
        // Find the child where k should be inserted
        while (i >= 0 && k < x->chave[i]) {
            i--;
        }
        i++; // Now i is the index of the appropriate child
        
        // If the child is full, split it
        if (x->filho[i]->n == 2 * t) {
            SplitChildArvoreB(x, i);
            if (k > x->chave[i]) {
                i++;
            }
        }
        // Recursive call
        InsereNaoCheioArvoreB(x->filho[i], k);
    }
}

ArvoreB InsereArvoreB(ArvoreB r, int k) {
    // int t = (int)ceil((float)MAX / 2.0);
    int t = (MAX+1)/2;
    if (r->n == 2 * t - 1) {
        NoArvB *s = AllocateNode();
        s->folha = 0;
        s->n = 0;
        s->filho[0] = r;
        SplitChildArvoreB(s, 0);
        InsereNaoCheioArvoreB(s, k);
        return s;
    } else {
        InsereNaoCheioArvoreB(r, k);
        return r;
    }
}

// Debug function to print the tree structure
void PrintBTree(ArvoreB r, int level) {
    if (r != NULL) {
        printf("Level %d: [", level);
        for (int i = 0; i < r->n; i++) {
            printf("%d", r->chave[i]);
            if (i < r->n - 1) printf(", ");
        }
        printf("] (folha: %s)\n", r->folha ? "yes" : "no");
        
        if (!r->folha) {
            for (int i = 0; i <= r->n; i++) {
                PrintBTree(r->filho[i], level + 1);
            }
        }
    }
}
