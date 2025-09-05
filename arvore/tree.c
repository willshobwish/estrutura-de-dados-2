#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

#define MAX 3

typedef struct No{
    int n;                    // número atual de chaves no nó
    int folha;               // flag: 1 se é folha, 0 se é nó interno
    int chave[MAX];          // array para armazenar as chaves
    struct No *filho[MAX+1]; // ponteiros para os filhos
}NoArvB, *ArvoreB;

// Função para criar um novo nó
NoArvB* criarNo(int folha) {
    NoArvB* novoNo = (NoArvB*)malloc(sizeof(NoArvB));
    novoNo->n = 0;
    novoNo->folha = folha;
    
    // Inicializa chaves como 0 e filhos como NULL
    for(int i = 0; i < MAX; i++) {
        novoNo->chave[i] = 0;
    }
    for(int i = 0; i < MAX+1; i++) {
        novoNo->filho[i] = NULL;
    }
    
    return novoNo;
}

// Função para buscar uma chave na árvore B
int buscar(NoArvB* raiz, int chave) {
    if(raiz == NULL) {
        return 0; // Árvore vazia
    }
    
    int i = 0;
    
    // Encontra a primeira chave maior ou igual à chave procurada
    while(i < raiz->n && chave > raiz->chave[i]) {
        i++;
    }
    
    // Se encontrou a chave
    if(i < raiz->n && chave == raiz->chave[i]) {
        return 1; // Chave encontrada
    }
    
    // Se é folha e não encontrou, a chave não existe
    if(raiz->folha) {
        return 0;
    }
    
    // Busca no filho apropriado
    return buscar(raiz->filho[i], chave);
}

// Função para imprimir a árvore (em ordem)
void imprimirArvore(NoArvB* raiz, int nivel) {
    if(raiz != NULL) {
        int i;
        
        // Imprime espaçamento baseado no nível
        for(int j = 0; j < nivel; j++) {
            printf("  ");
        }
        
        // Imprime as chaves do nó atual
        printf("Nó (folha=%d): ", raiz->folha);
        for(i = 0; i < raiz->n; i++) {
            printf("%d ", raiz->chave[i]);
        }
        printf("\n");
        
        // Recursivamente imprime os filhos
        if(!raiz->folha) {
            for(i = 0; i <= raiz->n; i++) {
                if(raiz->filho[i] != NULL) {
                    imprimirArvore(raiz->filho[i], nivel + 1);
                }
            }
        }
    }
}

// Função para criar uma árvore B estática de exemplo
ArvoreB criarArvoreEstatica() {
    // Criando os nós folha
    NoArvB* folha1 = criarNo(1); // folha
    folha1->n = 2;
    folha1->chave[0] = 1;
    folha1->chave[1] = 5;
    
    NoArvB* folha2 = criarNo(1); // folha
    folha2->n = 2;
    folha2->chave[0] = 15;
    folha2->chave[1] = 20;
    
    NoArvB* folha3 = criarNo(1); // folha
    folha3->n = 2;
    folha3->chave[0] = 35;
    folha3->chave[1] = 40;
    
    NoArvB* folha4 = criarNo(1); // folha
    folha4->n = 1;
    folha4->chave[0] = 50;
    
    // Criando nós internos
    NoArvB* interno1 = criarNo(0); // não é folha
    interno1->n = 1;
    interno1->chave[0] = 10;
    interno1->filho[0] = folha1;
    interno1->filho[1] = folha2;
    
    NoArvB* interno2 = criarNo(0); // não é folha
    interno2->n = 1;
    interno2->chave[0] = 45;
    interno2->filho[0] = folha3;
    interno2->filho[1] = folha4;
    
    // Criando a raiz
    NoArvB* raiz = criarNo(0); // não é folha
    raiz->n = 1;
    raiz->chave[0] = 30;
    raiz->filho[0] = interno1;
    raiz->filho[1] = interno2;
    
    return raiz;
}

// Função para liberar memória da árvore
void liberarArvore(NoArvB* raiz) {
    if(raiz != NULL) {
        if(!raiz->folha) {
            for(int i = 0; i <= raiz->n; i++) {
                liberarArvore(raiz->filho[i]);
            }
        }
        free(raiz);
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    printf("=== ÁRVORE B - DEMONSTRAÇÃO ===\n\n");
    
    // Criar árvore estática
    ArvoreB arvore = criarArvoreEstatica();
    
    printf("Estrutura da Árvore B criada:\n");
    printf("------------------------------\n");
    imprimirArvore(arvore, 0);
    
    printf("\n=== TESTES DE BUSCA ===\n");
    
    // Array de chaves para testar
    int chavesTeste[] = {1, 5, 10, 15, 25, 30, 35, 50, 99};
    int numTestes = sizeof(chavesTeste) / sizeof(chavesTeste[0]);
    
    for(int i = 0; i < numTestes; i++) {
        int chave = chavesTeste[i];
        int encontrado = buscar(arvore, chave);
        
        printf("Buscar chave %2d: %s\n", 
               chave, 
               encontrado ? "ENCONTRADA" : "NÃO ENCONTRADA");
    }
    
    printf("\n=== EXPLICAÇÃO DA ESTRUTURA ===\n");
    printf("Esta árvore B de ordem 3 tem a seguinte organização:\n");
    printf("- Raiz: [30]\n");
    printf("- Nível 1: [10] e [45]\n");
    printf("- Folhas: [1,5], [15,20], [35,40], [50]\n");
    printf("\nCada nó interno direciona a busca:\n");
    printf("- Valores < 30 vão para o filho esquerdo\n");
    printf("- Valores >= 30 vão para o filho direito\n");
    printf("- E assim por diante nos níveis inferiores\n");
    
    // Liberar memória
    liberarArvore(arvore);
    
    return 0;
}