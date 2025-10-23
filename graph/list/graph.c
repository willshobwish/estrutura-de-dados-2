#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

p_grafo CriarGrafo(int n) {
    int i;
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    for (i = 0; i < n; i++) {
        g->adjacencia[i] = NULL;
    }
    return g;
}

void LiberaLista(p_no lista) {
    if (lista != NULL) {
        LiberaLista(lista->prox);
        free(lista);
    }
}

void DestroiGrafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++) {
        LiberaLista(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

p_no InsereNaLista(p_no lista, int v) {
    p_no novo = malloc(sizeof(No));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void InsereAresta(p_grafo g, int u, int v) {
    g->adjacencia[v] = InsereNaLista(g->adjacencia[v], u);
    g->adjacencia[u] = InsereNaLista(g->adjacencia[u], v);
}

p_no RemoveDaLista(p_no lista, int v) {
    p_no proximo;
    if (lista == NULL) {
        return NULL;
    } else if (lista->v == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    } else {
        lista->prox = RemoveDaLista(lista->prox, v);
        return lista;
    }
}

void RemoveAresta(p_grafo g, int u, int v) {
    g->adjacencia[u] = RemoveDaLista(g->adjacencia[u], v);
    g->adjacencia[v] = RemoveDaLista(g->adjacencia[v], u);
}

int TemAresta(p_grafo g, int u, int v) {
    p_no t;
    for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
        if (t->v == v) {
            return 1;
        }
    }
    return 0;
}

// p_grafo LeGrafo() {
//     int n, m, i, u, v;
//     p_grafo g;
//     scanf("%d %d", &n, &m);
//     g = CriarGrafo(n);
//     for (i = 0; i < m; i++) {
//         scanf("%d %d", &u, &v);
//         InsereAresta(g, u, v);
//     }
//     return g;
// }

void ImprimeArestas(p_grafo g) {
    int u;
    p_no t;
    for (u = 0; u < g->n; u++) {
        for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
            printf("{%d %d}\n", u, t->v);
        }
    }
}

// int Grau(p_grafo g, int u) {
//     int v, grau = 0;
//     for (v = 0; v < g->n; v++) {
//         if (g->adj[u][v]) {
//             grau++;
//         }
//     }
//     return grau;
// }

// int MaisPopular(p_grafo g) {
//     int u, max, grauMax, grauAtual;
//     max = 0;
//     grauMax = Grau(g, 0);
//     for (u = 1; u < g->n; u++) {
//         grauAtual = Grau(g, u);
//         if (grauAtual > grauMax) {
//             grauMax = grauAtual;
//             max = u;
//         }
//     }
//     return max;
// }

// void ImprimeRecomendacoes(p_grafo g, int u) {
//     int v, w;
//     for (v = 0; v < g->n; v++) {
//         if (g->adj[u][v]) {
//             for (w = 0; w < g->n; w++) {
//                 if (g->adj[v][w] && w != u && !g->adj[u][w])
//                     printf("%d\n", w);
//             }
//         }
//     }
// }

int *EncontraComponentes(p_grafo g){
    int s,c=0,*componentes = malloc(g->n*sizeof(int));
    for(s=0;s<g->n;s++){
        componentes[s]=-1;
    } 
    for(s=0;s<g->n,s++){
        if(componentes[s]==-1){
            VisitaRec(g,componentes,c,s);
            c++;
        }
    }
    return componentes;
}

void VisitaRec(p_grafo g, int *componentes, int comp, int v){
    p_no t;
    componentes[v] = comp;
    for(t=g->adjacencia[v];t!=NULL;t=t->prox){
        if(componentes[t->v]==-1){
            VisitaRec(g,componentes,comp,t->v);
        }
    }
}