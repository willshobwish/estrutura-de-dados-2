#include "b_tree.h"

#include "pixel_data.h"
#include "stdio.h"
#include "stdlib.h"

void SaveNodeToFile(NoArvB *node, int is_root) {
    if (node->n == 0) return; // não salva nó vazio

    char filename[64];
    if (is_root) {
        sprintf(filename, "root.dat"); // nó raiz sempre "root.dat"
    } else {
        sprintf(filename, "%d.dat", node->chave[0]); // outros nós pelo valor da primeira chave
    }

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao salvar nó");
        return;
    }

    fwrite(node, sizeof(NoArvB), 1, fp);
    fclose(fp);
}

NoArvB *LoadNodeFromFile(int key) {
    char filename[64];
    sprintf(filename, "%d.dat", key);  // nome do arquivo é a primeira chave

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Erro ao abrir arquivo do nó");
        return NULL;
    }

    NoArvB *node = malloc(sizeof(NoArvB));
    if (!node) {
        fclose(fp);
        return NULL;
    }

    if (fread(node, sizeof(NoArvB), 1, fp) != 1) {
        perror("Erro ao ler nó do arquivo");
        free(node);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return node;
}

NoArvB* AllocateRootNode() {
    NoArvB* z = malloc(sizeof(NoArvB));
    if (!z) return NULL;
    z->n = 0;
    z->folha = 1;
    for (int j = 0; j < MAX + 1; j++)
        z->filho[j] = 0; // filhos ainda não existem
    SaveNodeToFile(z, 1); // salva como raiz
    return z;
}

NoArvB *AllocateNode() {
    NoArvB *z = malloc(sizeof(NoArvB));
    if (!z) return NULL;
    z->n = 0;
    z->folha = 1;
    for (int j = 0; j < MAX + 1; j++) {
        z->filho[j] = 0; // 0 significa “nenhum filho ainda”
    }
    return z;
}

int BuscaArvoreB(ArvoreB r, int k) {
    // printf("%d\n",r->n);
    if (r == NULL) {
        return -1;  // Key not found
    }

    int i = 0;
    while (i < r->n && k > r->chave[i]) {
        i++;
    }

    if (i < r->n && k == r->chave[i]) {
        return r->chave[i];
    } else if (r->folha) {
        return -1;  // Key not found and we're at a leaf
    } else {
        ArvoreB filho = LoadNodeFromFile(r->filho[i]);
        return BuscaArvoreB(filho, k);
    }
}

void SplitChildArvoreB(NoArvB *x, int i, int is_root) {
    int t = (MAX + 1) / 2;
    NoArvB *y = LoadNodeFromFile(x->filho[i]); // carrega filho i
    if (!y) return;

    NoArvB *z = AllocateNode();
    z->folha = y->folha;
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
        z->pixel[j] = y->pixel[j + t];
    }

    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filho[j] = y->filho[j + t];
        }
    }

    y->n = t - 1;

    for (int j = x->n; j >= i + 1; j--) {
        x->filho[j + 1] = x->filho[j];
    }

    SaveNodeToFile(z, 0);
    x->filho[i + 1] = z->chave[0];  // armazena a primeira chave como referência

    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pixel[j + 1] = x->pixel[j];
    }

    x->chave[i] = y->chave[t - 1];
    x->pixel[i] = y->pixel[t - 1];
    x->n++;

    SaveNodeToFile(y, 0);
    SaveNodeToFile(x, is_root);

    free(y);
    free(z);
}


void InsereNaoCheioArvoreB(ArvoreB x, int k, PixelData px, int is_root) {
    int t = (MAX + 1) / 2;
    int i = x->n - 1;

    if (x->folha) {
        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pixel[i + 1] = x->pixel[i];  // shift pixel data too
            i--;
        }
        x->chave[i + 1] = k;
        x->pixel[i + 1] = px;  // insert associated pixel
        x->n++;
        SaveNodeToFile(x, is_root); // salva alterações no disco
    } else {
        while (i >= 0 && k < x->chave[i]) i++;
        ArvoreB xFilho = LoadNodeFromFile(x->filho[i]);
        if (!xFilho) return;

        if (xFilho->n == 2 * t - 1) {
            SplitChildArvoreB(x, i, is_root);
            if (k > x->chave[i]) i++;
            free(xFilho);
            xFilho = LoadNodeFromFile(x->filho[i]); // recarrega o filho atualizado
        }

        InsereNaoCheioArvoreB(xFilho, k, px, 0); // filhos não são raiz
        free(xFilho);
    }
}


ArvoreB InsereArvoreB(ArvoreB r, int k, PixelData px) {
    int t = (MAX + 1) / 2;

    if (r->n == 2 * t - 1) {  // raiz cheia
        NoArvB *s = AllocateNode();
        s->folha = 0;
        s->filho[0] = r->chave[0]; // usamos a primeira chave do antigo nó raiz como índice
        SplitChildArvoreB(s, 0, 1); // 1 indica que é a nova raiz
        InsereNaoCheioArvoreB(s, k, px, 1); // raiz
        return s;
    } else {
        InsereNaoCheioArvoreB(r, k, px, 1); // raiz
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
                ArvoreB filho = LoadNodeFromFile(r->filho[i]);
                PrintBTree(filho, level + 1);
            }
        }
    }
}
