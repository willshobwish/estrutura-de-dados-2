#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void imprimeCaminho(int* pai, int destino) {
    if (pai[destino] == destino) {
        printf("%d", destino);
        return;
    }
    imprimeCaminho(pai, pai[destino]);
    printf(" -> %d", destino);
}

void grauPopularidade() {
    p_grafo g = CriarGrafo(5);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 0, 3);
    InsereAresta(g, 1, 2);

    printf("Grafo criado:\n");
    ImprimeArestas(g);
    printf("\nGraus dos vertices:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: grau %d\n", i, Grau(g, i));
    }

    int popular = MaisPopular(g);
    printf("\nVertice mais popular: %d com grau %d\n", popular, Grau(g, popular));

    DestroiGrafo(g);
}

void recomendacoes() {
    p_grafo g = CriarGrafo(6);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 1, 4);
    InsereAresta(g, 2, 5);

    printf("\nEstrutura da rede social:\n");
    ImprimeArestas(g);

    printf("\nRecomendacoes para o vertice 0:\n");
    ImprimeRecomendacoes(g, 0);

    printf("\nRecomendacoes para o vertice 1:\n");
    ImprimeRecomendacoes(g, 1);

    DestroiGrafo(g);
}

void componentesConexas() {
    p_grafo g = CriarGrafo(7);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 5, 6);

    printf("\nGrafo com componentes separadas:\n");
    ImprimeArestas(g);

    int* componentes = EncontraComponentes(g);
    printf("\nComponentes conexas identificadas:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d pertence ao componente %d\n", i, componentes[i]);
    }

    free(componentes);
    DestroiGrafo(g);
}

void grafoCompleto() {
    p_grafo g = CriarGrafo(4);
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            InsereAresta(g, i, j);
        }
    }

    printf("\nGrafo completo K4:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: grau %d\n", i, Grau(g, i));
    }

    int* comp = EncontraComponentes(g);
    printf("\nTodos os vertices no mesmo componente:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: componente %d\n", i, comp[i]);
    }

    free(comp);
    DestroiGrafo(g);
}

void buscaProfundidade() {
    p_grafo g = CriarGrafo(8);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 4, 5);
    InsereAresta(g, 5, 6);

    printf("\nGrafo com multiplas componentes:\n");
    ImprimeArestas(g);

    printf("\nBusca a partir do vertice 0:\n");
    int* pai0 = encontraCaminhos(g, 0);
    for (int i = 0; i < g->n; i++) {
        if (pai0[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai0[i] == i) {
            printf("Vertice %d: raiz da busca\n", i);
        } else {
            printf("Vertice %d: caminho ", i);
            imprimeCaminho(pai0, i);
            printf("\n");
        }
    }

    printf("\nBusca a partir do vertice 4:\n");
    int* pai4 = encontraCaminhos(g, 4);
    for (int i = 0; i < g->n; i++) {
        if (pai4[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai4[i] == i) {
            printf("Vertice %d: raiz da busca\n", i);
        } else {
            printf("Vertice %d: caminho ", i);
            imprimeCaminho(pai4, i);
            printf("\n");
        }
    }

    free(pai0);
    free(pai4);
    DestroiGrafo(g);
}

void buscaGrafoCiclico() {
    p_grafo g = CriarGrafo(5);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 4, 0);
    InsereAresta(g, 1, 4);

    printf("\nGrafo ciclico:\n");
    ImprimeArestas(g);

    printf("\nBusca a partir do vertice 0:\n");
    int* pai = encontraCaminhos(g, 0);
    for (int i = 0; i < g->n; i++) {
        if (pai[i] == i) {
            printf("Vertice %d: raiz\n", i);
        } else {
            printf("Vertice %d: caminho ", i);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void dijkstraBasico() {
    p_grafo g = CriarGrafo(5);
    InsereArestaPonderada(g, 0, 1, 4);
    InsereArestaPonderada(g, 0, 2, 7);
    InsereArestaPonderada(g, 1, 3, 2);
    InsereArestaPonderada(g, 2, 3, 1);
    InsereArestaPonderada(g, 2, 4, 5);
    InsereArestaPonderada(g, 3, 4, 4);

    printf("\nGrafo ponderado:\n");
    printf("Arestas: 0-1(4), 0-2(7), 1-3(2), 2-3(1), 2-4(5), 3-4(4)\n");

    printf("\nCaminhos minimos a partir do vertice 0:\n");
    int* pai = dijkstra(g, 0);

    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai[i] == i) {
            printf("Vertice %d: origem\n", i);
        } else {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void dijkstraComponentesDesconexas() {
    p_grafo g = CriarGrafo(7);
    InsereArestaPonderada(g, 0, 1, 3);
    InsereArestaPonderada(g, 1, 2, 5);
    InsereArestaPonderada(g, 3, 4, 2);
    InsereArestaPonderada(g, 4, 5, 1);

    printf("\nGrafo com componentes desconexas:\n");
    printf("Componente A: 0-1-2\n");
    printf("Componente B: 3-4-5\n");
    printf("Vertice isolado: 6\n");

    printf("\nDijkstra a partir do vertice 0:\n");
    int* pai = dijkstra(g, 0);
    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai[i] == i) {
            printf("Vertice %d: origem\n", i);
        } else {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void dijkstraGrafoCompleto() {
    p_grafo g = CriarGrafo(4);
    InsereArestaPonderada(g, 0, 1, 1);
    InsereArestaPonderada(g, 0, 2, 4);
    InsereArestaPonderada(g, 0, 3, 10);
    InsereArestaPonderada(g, 1, 2, 2);
    InsereArestaPonderada(g, 1, 3, 5);
    InsereArestaPonderada(g, 2, 3, 3);

    printf("\nGrafo completo ponderado K4:\n");
    printf("Arestas: 0-1(1), 0-2(4), 0-3(10), 1-2(2), 1-3(5), 2-3(3)\n");

    printf("\nCaminhos minimos a partir do vertice 0:\n");
    int* pai = dijkstra(g, 0);

    for (int i = 0; i < g->n; i++) {
        if (pai[i] == i) {
            printf("Vertice %d: origem\n", i);
        } else {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void dijkstraDistancias() {
    p_grafo g = CriarGrafo(5);
    InsereArestaPonderada(g, 0, 1, 10);
    InsereArestaPonderada(g, 0, 2, 5);
    InsereArestaPonderada(g, 1, 3, 1);
    InsereArestaPonderada(g, 2, 1, 3);
    InsereArestaPonderada(g, 2, 3, 8);
    InsereArestaPonderada(g, 2, 4, 2);
    InsereArestaPonderada(g, 3, 4, 4);

    printf("\nGrafo para analise de distancias:\n");
    printf("Arestas: 0-1(10), 0-2(5), 1-3(1), 2-1(3), 2-3(8), 2-4(2), 3-4(4)\n");

    printf("\nCaminhos encontrados a partir do vertice 0:\n");
    int* pai = dijkstra(g, 0);

    for (int i = 0; i < g->n; i++) {
        if (pai[i] == i) {
            printf("Vertice %d: origem\n", i);
        } else if (pai[i] != -1) {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void primBasico() {
    p_grafo g = CriarGrafo(5);

    InsereArestaPonderada(g, 0, 1, 2);
    InsereArestaPonderada(g, 0, 3, 6);
    InsereArestaPonderada(g, 1, 2, 3);
    InsereArestaPonderada(g, 1, 3, 8);
    InsereArestaPonderada(g, 1, 4, 5);
    InsereArestaPonderada(g, 2, 4, 7);
    InsereArestaPonderada(g, 3, 4, 9);

    printf("\nGrafo ponderado:\n");
    printf("Arestas: 0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)\n");

    printf("\nArvore Geradora Minima (Prim) a partir do vertice 0:\n");
    int* pai = prim(g, 0);

    printf("\nArestas da MST:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai[i] != -1 && pai[i] != i) {
            printf("Aresta: %d - %d\n", pai[i], i);
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void primComparacao() {
    p_grafo g = CriarGrafo(4);

    InsereArestaPonderada(g, 0, 1, 1);
    InsereArestaPonderada(g, 0, 2, 4);
    InsereArestaPonderada(g, 0, 3, 3);
    InsereArestaPonderada(g, 1, 2, 2);
    InsereArestaPonderada(g, 2, 3, 5);

    printf("\nGrafo: 0-1(1), 0-2(4), 0-3(3), 1-2(2), 2-3(5)\n");

    printf("\nComparacao: Prim vs Dijkstra\n");

    printf("\nPrim (Arvore Geradora Minima):\n");
    int* pai_prim = prim(g, 0);
    printf("Arestas selecionadas:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_prim[i] != -1 && pai_prim[i] != i) {
            printf("  %d - %d\n", pai_prim[i], i);
        }
    }

    printf("\nDijkstra (Caminhos Minimos):\n");
    int* pai_dijkstra = dijkstra(g, 0);
    printf("Caminhos da origem:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_dijkstra[i] != -1 && pai_dijkstra[i] != i) {
            printf("  Para %d: ", i);
            imprimeCaminho(pai_dijkstra, i);
            printf("\n");
        }
    }

    free(pai_prim);
    free(pai_dijkstra);
    DestroiGrafo(g);
}

int main(void) {
    printf("Analise de Grau e Popularidade\n");
    grauPopularidade();

    printf("\n\nSistema de Recomendacoes\n");
    recomendacoes();

    printf("\n\nComponentes Conexas\n");
    componentesConexas();

    printf("\n\nGrafo Completo\n");
    grafoCompleto();

    printf("\n\nBusca em Profundidade\n");
    buscaProfundidade();

    printf("\n\nBusca em Grafo Ciclico\n");
    buscaGrafoCiclico();

    printf("\n\nAlgoritmo de Dijkstra Basico\n");
    dijkstraBasico();

    printf("\n\nDijkstra com Componentes Desconexas\n");
    dijkstraComponentesDesconexas();

    printf("\n\nDijkstra em Grafo Completo\n");
    dijkstraGrafoCompleto();

    printf("\n\nDijkstra - Analise de Distancias\n");
    dijkstraDistancias();

    printf("\n\nAlgoritmo de Prim (MST)\n");
    primBasico();

    printf("\n\nPrim vs Dijkstra\n");
    primComparacao();

    printf("\n\nPrograma finalizado.\n");
    return 0;
}