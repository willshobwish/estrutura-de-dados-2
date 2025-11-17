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

int main(void) {
    printf("\n=== TESTE 1: Grau ===\n");
    p_grafo g1 = CriarGrafo(5);
    InsereAresta(g1, 0, 1);
    InsereAresta(g1, 0, 2);
    InsereAresta(g1, 0, 3);
    InsereAresta(g1, 1, 2);

    printf("Grafo 1 - Arestas:\n");
    ImprimeArestas(g1);
    printf("\nGraus dos vertices:\n");
    for (int i = 0; i < g1->n; i++) {
        printf("Vertice %d: grau %d\n", i, Grau(g1, i));
    }

    printf("\n=== TESTE 2: MaisPopular ===\n");
    int popular = MaisPopular(g1);
    printf("Vértice mais popular: %d (grau %d)\n", popular, Grau(g1, popular));

    DestroiGrafo(g1);

    printf("\n=== TESTE 3: ImprimeRecomendacoes ===\n");
    p_grafo g2 = CriarGrafo(6);
    // Cria uma rede social: 0-1-2-3, 1-4, 2-5
    InsereAresta(g2, 0, 1);
    InsereAresta(g2, 1, 2);
    InsereAresta(g2, 2, 3);
    InsereAresta(g2, 1, 4);
    InsereAresta(g2, 2, 5);

    printf("Grafo 2 - Arestas:\n");
    ImprimeArestas(g2);
    printf("\nRecomendações para o vértice 0 (amigos de amigos):\n");
    ImprimeRecomendacoes(g2, 0);

    printf("\nRecomendações para o vértice 1:\n");
    ImprimeRecomendacoes(g2, 1);

    DestroiGrafo(g2);

    printf("\n=== TESTE 4: EncontraComponentes ===\n");
    p_grafo g3 = CriarGrafo(7);
    // Cria três componentes: {0,1,2}, {3,4}, {5,6}
    InsereAresta(g3, 0, 1);
    InsereAresta(g3, 1, 2);
    InsereAresta(g3, 3, 4);
    InsereAresta(g3, 5, 6);

    printf("Grafo 3 - Arestas:\n");
    ImprimeArestas(g3);

    int* componentes = EncontraComponentes(g3);
    printf("\nComponentes conexas:\n");
    for (int i = 0; i < g3->n; i++) {
        printf("Vértice %d: componente %d\n", i, componentes[i]);
    }

    free(componentes);
    DestroiGrafo(g3);

    printf("\n=== TESTE 5: Grafo Completo ===\n");
    p_grafo g4 = CriarGrafo(4);
    // Cria um grafo completo K4
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            InsereAresta(g4, i, j);
        }
    }

    printf("Grafo 4 (K4) - Todos os graus devem ser 3:\n");
    for (int i = 0; i < g4->n; i++) {
        printf("Vértice %d: grau %d\n", i, Grau(g4, i));
    }

    int* comp4 = EncontraComponentes(g4);
    printf("\nTodos devem estar no mesmo componente:\n");
    for (int i = 0; i < g4->n; i++) {
        printf("Vértice %d: componente %d\n", i, comp4[i]);
    }

    free(comp4);
    DestroiGrafo(g4);

    printf("\n=== TESTE 6: encontraCaminhos ===\n");
    p_grafo g5 = CriarGrafo(8);
    // Cria um grafo com estrutura de árvore e componentes separadas
    // Componente 1: 0-1-2, 1-3
    InsereAresta(g5, 0, 1);
    InsereAresta(g5, 1, 2);
    InsereAresta(g5, 1, 3);

    // Componente 2: 4-5-6
    InsereAresta(g5, 4, 5);
    InsereAresta(g5, 5, 6);

    // Vértice isolado: 7

    printf("Grafo 5 - Arestas:\n");
    ImprimeArestas(g5);

    printf("\nBusca em profundidade a partir do vértice 0:\n");
    int* pai0 = encontraCaminhos(g5, 0);
    printf("\nÁrvore de caminhos (vetor pai) a partir de 0:\n");
    for (int i = 0; i < g5->n; i++) {
        if (pai0[i] == -1) {
            printf("Vértice %d: não alcançável (pai = -1)\n", i);
        } else if (pai0[i] == i) {
            printf("Vértice %d: raiz da busca (pai = %d)\n", i, pai0[i]);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai0[i]);
            imprimeCaminho(pai0, i);
            printf("\n");
        }
    }

    printf("\n\nBusca em profundidade a partir do vértice 4:\n");
    int* pai4 = encontraCaminhos(g5, 4);
    printf("\nÁrvore de caminhos (vetor pai) a partir de 4:\n");
    for (int i = 0; i < g5->n; i++) {
        if (pai4[i] == -1) {
            printf("Vértice %d: não alcançável (pai = -1)\n", i);
        } else if (pai4[i] == i) {
            printf("Vértice %d: raiz da busca (pai = %d)\n", i, pai4[i]);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai4[i]);
            imprimeCaminho(pai4, i);
            printf("\n");
        }
    }

    printf("\n\nBusca em profundidade a partir do vértice 7 (isolado):\n");
    int* pai7 = encontraCaminhos(g5, 7);
    printf("\nÁrvore de caminhos (vetor pai) a partir de 7:\n");
    for (int i = 0; i < g5->n; i++) {
        if (pai7[i] == -1) {
            printf("Vértice %d: não alcançável (pai = -1)\n", i);
        } else if (pai7[i] == i) {
            printf("Vértice %d: raiz da busca (pai = %d)\n", i, pai7[i]);
        } else {
            printf("Vértice %d: pai = %d\n", i, pai7[i]);
        }
    }

    free(pai0);
    free(pai4);
    free(pai7);
    DestroiGrafo(g5);

    printf("\n=== TESTE 7: encontraCaminhos em Grafo Cíclico ===\n");
    p_grafo g6 = CriarGrafo(5);
    // Cria um ciclo: 0-1-2-3-4-0
    InsereAresta(g6, 0, 1);
    InsereAresta(g6, 1, 2);
    InsereAresta(g6, 2, 3);
    InsereAresta(g6, 3, 4);
    InsereAresta(g6, 4, 0);
    // Adiciona uma aresta transversal
    InsereAresta(g6, 1, 4);

    printf("Grafo 6 (cíclico) - Arestas:\n");
    ImprimeArestas(g6);

    printf("\nBusca em profundidade a partir do vértice 0:\n");
    int* pai_ciclo = encontraCaminhos(g6, 0);
    printf("\nÁrvore de caminhos no grafo cíclico:\n");
    for (int i = 0; i < g6->n; i++) {
        if (pai_ciclo[i] == i) {
            printf("Vértice %d: raiz (pai = %d)\n", i, pai_ciclo[i]);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai_ciclo[i]);
            imprimeCaminho(pai_ciclo, i);
            printf("\n");
        }
    }

    free(pai_ciclo);
    DestroiGrafo(g6);

    printf("\n=== TESTE 8: Algoritmo de Dijkstra ===\n");
    p_grafo g7 = CriarGrafo(6);
    /* Cria um grafo ponderado
     * Exemplo baseado em um grafo clássico para Dijkstra
     *     1
     *   /   \
     *  4     2
     * 0       3
     *  7     1
     *   \   /
     *     2
     *     |
     *     5
     *     4
     *     |
     *     5
     */

    InsereArestaPonderada(g7, 0, 1, 4);  // 0-1 peso 4
    InsereArestaPonderada(g7, 0, 2, 7);  // 0-2 peso 7
    InsereArestaPonderada(g7, 1, 3, 2);  // 1-3 peso 2
    InsereArestaPonderada(g7, 2, 3, 1);  // 2-3 peso 1
    InsereArestaPonderada(g7, 2, 4, 5);  // 2-4 peso 5
    InsereArestaPonderada(g7, 3, 4, 4);  // 3-4 peso 4

    printf("Grafo 7 (ponderado) - Estrutura:\n");
    printf("Vertices: 0, 1, 2, 3, 4\n");
    printf("Arestas com pesos:\n");
    printf("  0-1 (peso 4)\n");
    printf("  0-2 (peso 7)\n");
    printf("  1-3 (peso 2)\n");
    printf("  2-3 (peso 1)\n");
    printf("  2-4 (peso 5)\n");
    printf("  3-4 (peso 4)\n");

    printf("\nExecutando Dijkstra a partir do vértice 0:\n");
    int* pai_dijkstra = dijkstra(g7, 0);

    printf("\nCaminhos mínimos a partir de 0:\n");
    for (int i = 0; i < g7->n; i++) {
        if (pai_dijkstra[i] == -1) {
            printf("Vértice %d: não alcançável\n", i);
        } else if (pai_dijkstra[i] == i) {
            printf("Vértice %d: origem (distância 0)\n", i);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai_dijkstra[i]);
            imprimeCaminho(pai_dijkstra, i);
            printf("\n");
        }
    }

    free(pai_dijkstra);

    printf("\n=== TESTE 9: Dijkstra com Componentes Desconexas ===\n");
    p_grafo g8 = CriarGrafo(7);
    // Componente 1: 0-1-2 (conectado)
    InsereArestaPonderada(g8, 0, 1, 3);
    InsereArestaPonderada(g8, 1, 2, 5);

    // Componente 2: 3-4-5 (desconectado da componente 1)
    InsereArestaPonderada(g8, 3, 4, 2);
    InsereArestaPonderada(g8, 4, 5, 1);

    // Vértice isolado: 6

    printf("Grafo 8 - Duas componentes separadas:\n");
    printf("Componente 1: 0-1-2\n");
    printf("Componente 2: 3-4-5\n");
    printf("Vértice isolado: 6\n");

    printf("\nDijkstra a partir do vértice 0:\n");
    int* pai_dijkstra2 = dijkstra(g8, 0);
    for (int i = 0; i < g8->n; i++) {
        if (pai_dijkstra2[i] == -1) {
            printf("Vértice %d: não alcançável\n", i);
        } else if (pai_dijkstra2[i] == i) {
            printf("Vértice %d: origem\n", i);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai_dijkstra2[i]);
            imprimeCaminho(pai_dijkstra2, i);
            printf("\n");
        }
    }

    free(pai_dijkstra2);
    DestroiGrafo(g7);
    DestroiGrafo(g8);

    printf("\n=== TESTE 10: Dijkstra - Grafo Completo Ponderado ===\n");
    p_grafo g9 = CriarGrafo(4);
    // Grafo completo K4 com pesos diferentes
    InsereArestaPonderada(g9, 0, 1, 1);
    InsereArestaPonderada(g9, 0, 2, 4);
    InsereArestaPonderada(g9, 0, 3, 10);
    InsereArestaPonderada(g9, 1, 2, 2);
    InsereArestaPonderada(g9, 1, 3, 5);
    InsereArestaPonderada(g9, 2, 3, 3);

    printf("Grafo 9 - K4 ponderado:\n");
    printf("  0-1 (peso 1), 0-2 (peso 4), 0-3 (peso 10)\n");
    printf("  1-2 (peso 2), 1-3 (peso 5)\n");
    printf("  2-3 (peso 3)\n");

    printf("\nDijkstra a partir do vértice 0:\n");
    int* pai_dijkstra3 = dijkstra(g9, 0);

    printf("Árvore de caminhos mínimos:\n");
    for (int i = 0; i < g9->n; i++) {
        if (pai_dijkstra3[i] == i) {
            printf("Vértice %d: origem\n", i);
        } else {
            printf("Vértice %d: pai = %d, caminho: ", i, pai_dijkstra3[i]);
            imprimeCaminho(pai_dijkstra3, i);
            printf("\n");
        }
    }

    printf("\nDistâncias esperadas de 0:\n");
    printf("  0->1: 1 (direto)\n");
    printf("  0->2: 3 (via 1: 0->1->2)\n");
    printf("  0->3: 6 (via 1 e 2: 0->1->2->3)\n");

    free(pai_dijkstra3);
    DestroiGrafo(g9);

    printf("\n=== TESTE 11: Dijkstra com Distâncias ===\n");
    p_grafo g10 = CriarGrafo(5);
    // Cria um grafo para testar caminhos mínimos com distâncias explícitas
    InsereArestaPonderada(g10, 0, 1, 10);
    InsereArestaPonderada(g10, 0, 2, 5);
    InsereArestaPonderada(g10, 1, 3, 1);
    InsereArestaPonderada(g10, 2, 1, 3);
    InsereArestaPonderada(g10, 2, 3, 8);
    InsereArestaPonderada(g10, 2, 4, 2);
    InsereArestaPonderada(g10, 3, 4, 4);

    printf("Grafo 10 - Teste de distâncias:\n");
    printf("  0-1 (peso 10), 0-2 (peso 5)\n");
    printf("  1-3 (peso 1), 2-1 (peso 3)\n");
    printf("  2-3 (peso 8), 2-4 (peso 2)\n");
    printf("  3-4 (peso 4)\n");

    printf("\nDijkstra a partir do vértice 0:\n");
    int* pai_dijkstra4 = dijkstra(g10, 0);

    printf("Caminhos encontrados:\n");
    for (int i = 0; i < g10->n; i++) {
        if (pai_dijkstra4[i] == i) {
            printf("Vértice %d: origem\n", i);
        } else if (pai_dijkstra4[i] != -1) {
            printf("Vértice %d: caminho: ", i);
            imprimeCaminho(pai_dijkstra4, i);
            printf("\n");
        }
    }

    printf("\nDistâncias esperadas (calculadas manualmente):\n");
    printf("  0->0: 0\n");
    printf("  0->1: 8 (via 2: 0->2->1, custo 5+3=8, melhor que direto 10)\n");
    printf("  0->2: 5 (direto)\n");
    printf("  0->3: 9 (via 2 e 1: 0->2->1->3, custo 5+3+1=9)\n");
    printf("  0->4: 7 (via 2: 0->2->4, custo 5+2=7)\n");

    free(pai_dijkstra4);
    DestroiGrafo(g10);

    printf("\n=== Todos os testes concluídos! ===\n");

    return 0;
}