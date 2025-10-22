#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

p_grafo CriarGrafo(int n) {
    int i, j;
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;
    g->adj = malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        g->adj[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            g->adj[i][j] = 0;
        }
    }
    return g;
}

void DestroiGrafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

void InsereAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}
void RemoveAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}
int TemAresta(p_grafo g, int u, int v) {
    return g->adj[u][v];
}

p_grafo LeGrafo() {
    int n, m, i, u, v;
    p_grafo g;
    scanf("%d %d", &n, &m);
    g = CriarGrafo(n);
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        InsereAresta(g, u, v);
    }
    return g;
}

void ImprimeArestas(p_grafo g) {
    int u, v;
    for (u = 0; u < g->n; u++) {
        for (v = 0; v < g->n; v++) {
            if (g->adj[u][v]) {
                printf("{%d %d}\n", u, v);
            }
        }
    }
}

int Grau(p_grafo g, int u) {
    int v, grau = 0;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {
            grau++;
        }
    }
    return grau;
}

int MaisPopular(p_grafo g) {
    int u, max, grauMax, grauAtual;
    max = 0;
    grauMax = Grau(g, 0);
    for (u = 1; u < g->n; u++) {
        grauAtual = Grau(g, u);
        if (grauAtual > grauMax) {
            grauMax = grauAtual;
            max = u;
        }
    }
    return max;
}

void ImprimeRecomendacoes(p_grafo g, int u) {
    int v, w;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {
            for (w = 0; w < g->n; w++) {
                if (g->adj[v][w] && w != u && !g->adj[u][w])
                    printf("%d\n", w);
            }
        }
    }
}