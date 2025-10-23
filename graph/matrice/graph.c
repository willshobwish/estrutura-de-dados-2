#include "graph.h"  // Inclui o cabeçalho com a definição da estrutura 'Grafo' e as funções declaradas

#include <stdio.h>   // Inclui funções de entrada/saída, como printf e scanf
#include <stdlib.h>  // Inclui funções de alocação e liberação de memória (malloc, free)

// Função que cria um grafo com 'n' vértices
p_grafo CriarGrafo(int n) {
    int i, j;
    p_grafo g = malloc(sizeof(Grafo));   // Aloca memória para a estrutura principal do grafo
    g->n = n;                            // Define o número de vértices
    g->adj = malloc(n * sizeof(int *));  // Aloca memória para o vetor de ponteiros das listas de adjacência (matriz)

    for (i = 0; i < n; i++) {
        g->adj[i] = malloc(n * sizeof(int));  // Aloca memória para cada linha da matriz de adjacência
    }

    // Inicializa a matriz de adjacência com zeros (sem arestas)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            g->adj[i][j] = 0;  // 0 indica ausência de aresta
        }
    }

    return g;  // Retorna o ponteiro para o grafo criado
}

// Função que libera toda a memória usada pelo grafo
void DestroiGrafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++) {
        free(g->adj[i]);  // Libera cada linha da matriz
    }
    free(g->adj);  // Libera o vetor de ponteiros
    free(g);       // Libera a estrutura principal do grafo
}

// Função que insere uma aresta entre os vértices u e v (grafo não direcionado)
void InsereAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 1;  // Marca a conexão de u para v
    g->adj[v][u] = 1;  // Marca a conexão de v para u (pois o grafo é não direcionado)
}

// Função que remove uma aresta entre os vértices u e v
void RemoveAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 0;  // Remove a conexão de u para v
    g->adj[v][u] = 0;  // Remove a conexão de v para u
}

// Função que verifica se há uma aresta entre u e v
int TemAresta(p_grafo g, int u, int v) {
    return g->adj[u][v];  // Retorna 1 se há aresta, 0 caso contrário
}

// Função que lê um grafo da entrada padrão
p_grafo LeGrafo() {
    int n, m, i, u, v;
    p_grafo g;
    scanf("%d %d", &n, &m);  // Lê número de vértices (n) e número de arestas (m)
    g = CriarGrafo(n);       // Cria o grafo com n vértices

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);  // Lê os pares de vértices conectados por arestas
        InsereAresta(g, u, v);   // Insere cada aresta no grafo
    }
    return g;  // Retorna o grafo criado
}

// Função que imprime todas as arestas do grafo
void ImprimeArestas(p_grafo g) {
    int u, v;
    for (u = 0; u < g->n; u++) {
        for (v = 0; v < g->n; v++) {
            if (g->adj[u][v]) {             // Se existe uma aresta entre u e v
                printf("{%d %d}\n", u, v);  // Imprime a aresta
            }
        }
    }
}

// Função que calcula o grau (número de conexões) de um vértice u
int Grau(p_grafo g, int u) {
    int v, grau = 0;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {  // Conta quantas arestas saem de u
            grau++;
        }
    }
    return grau;  // Retorna o grau total
}

// Função que encontra o vértice mais popular (com maior grau)
int MaisPopular(p_grafo g) {
    int u, max, grauMax, grauAtual;
    max = 0;               // Inicializa o mais popular como o vértice 0
    grauMax = Grau(g, 0);  // Calcula o grau do vértice 0

    for (u = 1; u < g->n; u++) {
        grauAtual = Grau(g, u);     // Calcula o grau do vértice u
        if (grauAtual > grauMax) {  // Se tiver grau maior, atualiza o máximo
            grauMax = grauAtual;
            max = u;
        }
    }
    return max;  // Retorna o vértice com maior grau
}

// Função que imprime "recomendações" de vértices conectados a amigos de 'u'
void ImprimeRecomendacoes(p_grafo g, int u) {
    int v, w;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {  // Se v é amigo de u
            for (w = 0; w < g->n; w++) {
                if (g->adj[v][w] && w != u && !g->adj[u][w])
                    // Se w é amigo de v, mas não de u e não é o próprio u
                    printf("%d\n", w);  // Recomenda w a u
            }
        }
    }
}

// Função que verifica se existe caminho entre os vértices s e t
int ExisteCaminho(p_grafo g, int s, int t) {
    int encontrou, i, *visitado = malloc(g->n * sizeof(int));  // Vetor para marcar vértices visitados
    for (i = 0; i < g->n; i++) {
        visitado[i] = 0;  // Inicializa todos como não visitados
    }
    encontrou = BuscaRec(g, visitado, s, t);  // Faz busca recursiva (DFS)
    free(visitado);                           // Libera a memória
    return encontrou;                         // Retorna 1 se encontrou caminho, 0 se não
}

// Função auxiliar recursiva para busca de caminho (DFS)
int BuscaRec(p_grafo g, int *visitado, int v, int t) {
    int w;
    if (v == t) {  // Se encontrou o vértice destino
        return 1;
    }
    visitado[v] = 1;  // Marca o vértice atual como visitado
    for (w = 0; w < g->n; w++) {
        if (g->adj[v][w] && !visitado[w]) {   // Se existe aresta e w ainda não foi visitado
            if (BuscaRec(g, visitado, w, t))  // Continua a busca a partir de w
                return 1;                     // Se achou o destino, retorna 1
        }
    }
    return 0;  // Se não encontrou, retorna 0
}
