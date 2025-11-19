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

void operacoesBasicas() {
    p_grafo g = CriarGrafo(5);

    printf("Grafo criado com 5 vertices\n");
    printf("Inserindo arestas...\n");

    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 0, 3);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 2, 2);  // laco

    printf("\nArestas do grafo:\n");
    ImprimeArestas(g);

    printf("\nVerificando arestas:\n");
    printf("Existe aresta (0,1)? %s\n", TemAresta(g, 0, 1) ? "Sim" : "Nao");
    printf("Existe aresta (0,4)? %s\n", TemAresta(g, 0, 4) ? "Sim" : "Nao");
    printf("Existe laco (2,2)? %s\n", TemAresta(g, 2, 2) ? "Sim" : "Nao");

    printf("\nGraus dos vertices:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: grau %d\n", i, Grau(g, i));
    }

    printf("\nRemovendo aresta (0,1)...\n");
    RemoveAresta(g, 0, 1);
    printf("Existe aresta (0,1)? %s\n", TemAresta(g, 0, 1) ? "Sim" : "Nao");
    printf("Novo grau do vertice 0: %d\n", Grau(g, 0));

    DestroiGrafo(g);
}

void popularidadeRecomendacoes() {
    p_grafo g = CriarGrafo(6);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 1, 4);
    InsereAresta(g, 2, 5);

    printf("\nEstrutura da rede social:\n");
    ImprimeArestas(g);

    int popular = MaisPopular(g);
    printf("\nVertice mais popular: %d (grau %d)\n", popular, Grau(g, popular));

    printf("\nRecomendacões de amizade para o vertice 0:\n");
    ImprimeRecomendacoes(g, 0);

    printf("\nRecomendacões de amizade para o vertice 1:\n");
    ImprimeRecomendacoes(g, 1);

    DestroiGrafo(g);
}

void caminhos() {
    p_grafo g = CriarGrafo(6);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 3, 4);

    printf("\nGrafo desconexo:\n");
    ImprimeArestas(g);

    printf("\nVerificando existência de caminhos:\n");
    printf("Existe caminho de 0 para 2? %s\n", ExisteCaminho(g, 0, 2) ? "Sim" : "Nao");
    printf("Existe caminho de 3 para 4? %s\n", ExisteCaminho(g, 3, 4) ? "Sim" : "Nao");
    printf("Existe caminho de 0 para 3? %s\n", ExisteCaminho(g, 0, 3) ? "Sim" : "Nao");
    printf("Existe caminho de 0 para 5? %s\n", ExisteCaminho(g, 0, 5) ? "Sim" : "Nao");

    InsereAresta(g, 2, 3);
    printf("Agora existe caminho de 0 para 4? %s\n", ExisteCaminho(g, 0, 4) ? "Sim" : "Nao");

    DestroiGrafo(g);
}

void componentesConexas() {
    p_grafo g = CriarGrafo(7);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 5, 6);

    printf("\nGrafo com múltiplas componentes:\n");
    ImprimeArestas(g);

    int* componentes = EncontraComponentes(g);
    printf("\nComponentes conexas identificadas:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: componente %d\n", i, componentes[i]);
    }

    free(componentes);
    DestroiGrafo(g);
}

void grafoCompleto() {
    p_grafo g = CriarGrafo(4);

    printf("\nCriando grafo completo K4...\n");
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            InsereAresta(g, i, j);
        }
    }

    printf("Graus dos vertices no K4:\n");
    for (int i = 0; i < g->n; i++) {
        printf("Vertice %d: grau %d\n", i, Grau(g, i));
    }

    printf("\nVerificando conectividade completa:\n");
    int conectado = 1;
    for (int i = 0; i < 4 && conectado; i++) {
        for (int j = 0; j < 4 && conectado; j++) {
            if (!ExisteCaminho(g, i, j)) {
                conectado = 0;
            }
        }
    }
    printf("Todos os vertices conectados? %s\n", conectado ? "Sim" : "Nao");

    DestroiGrafo(g);
}

void buscaProfundidade() {
    p_grafo g = CriarGrafo(8);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 4, 5);
    InsereAresta(g, 5, 6);

    printf("\nGrafo com componentes separadas:\n");
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

void buscaIterativa() {
    p_grafo g = CriarGrafo(6);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 4, 5);

    printf("\nGrafo ciclico:\n");
    ImprimeArestas(g);

    printf("\nBusca em profundidade iterativa a partir do vertice 0:\n");
    int* pai = busca_em_profundidade(g, 0);

    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai[i] == i) {
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

void buscaLargura() {
    p_grafo g = CriarGrafo(7);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 0, 3);
    InsereAresta(g, 1, 4);
    InsereAresta(g, 2, 5);
    InsereAresta(g, 3, 6);

    printf("\nGrafo em niveis:\n");
    ImprimeArestas(g);

    printf("\nBusca em largura a partir do vertice 0:\n");
    int* pai_bfs = busca_em_largura(g, 0);

    printf("Caminhos mais curtos (BFS):\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_bfs[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai_bfs[i] == i) {
            printf("Vertice %d: raiz\n", i);
        } else {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai_bfs, i);
            printf("\n");
        }
    }

    printf("\nComparando com busca em profundidade:\n");
    int* pai_dfs = busca_em_profundidade(g, 0);

    printf("Caminhos (DFS):\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_dfs[i] == i) {
            printf("Vertice %d: raiz\n", i);
        } else {
            printf("Vertice %d: ", i);
            imprimeCaminho(pai_dfs, i);
            printf("\n");
        }
    }

    free(pai_bfs);
    free(pai_dfs);
    DestroiGrafo(g);
}

void primBasico() {
    p_grafo g = CriarGrafo(5);

    // Para matriz, precisamos inserir os pesos diretamente
    g->adj[0][1] = g->adj[1][0] = 2;
    g->adj[0][3] = g->adj[3][0] = 6;
    g->adj[1][2] = g->adj[2][1] = 3;
    g->adj[1][3] = g->adj[3][1] = 8;
    g->adj[1][4] = g->adj[4][1] = 5;
    g->adj[2][4] = g->adj[4][2] = 7;
    g->adj[3][4] = g->adj[4][3] = 9;

    printf("\nGrafo ponderado:\n");
    printf("Arestas: 0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)\n");

    printf("\nArvore Geradora Minima (Prim) a partir do vertice 0:\n");
    int* pai = prim(g, 0);

    printf("\nArestas da MST:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai[i] != -1 && pai[i] != i) {
            printf("Aresta: %d - %d (peso: %d)\n", pai[i], i, g->adj[pai[i]][i]);
        }
    }

    free(pai);
    DestroiGrafo(g);
}

void primGrafoCompleto() {
    p_grafo g = CriarGrafo(4);

    // Grafo completo com pesos variados
    g->adj[0][1] = g->adj[1][0] = 1;
    g->adj[0][2] = g->adj[2][0] = 4;
    g->adj[0][3] = g->adj[3][0] = 3;
    g->adj[1][2] = g->adj[2][1] = 2;
    g->adj[1][3] = g->adj[3][1] = 5;
    g->adj[2][3] = g->adj[3][2] = 6;

    printf("\nGrafo completo K4 ponderado:\n");
    printf("Arestas: 0-1(1), 0-2(4), 0-3(3), 1-2(2), 1-3(5), 2-3(6)\n");

    printf("\nArvore Geradora Minima (Prim):\n");
    int* pai = prim(g, 0);

    printf("\nArestas selecionadas:\n");
    int custo_total = 0;
    for (int i = 0; i < g->n; i++) {
        if (pai[i] != -1 && pai[i] != i) {
            int peso = g->adj[pai[i]][i];
            printf("  %d - %d (peso: %d)\n", pai[i], i, peso);
            custo_total += peso;
        }
    }
    printf("\nCusto total da MST: %d\n", custo_total);

    free(pai);
    DestroiGrafo(g);
}

void primDesconexo() {
    p_grafo g = CriarGrafo(6);

    // Componente 1: vertices 0, 1, 2
    g->adj[0][1] = g->adj[1][0] = 3;
    g->adj[1][2] = g->adj[2][1] = 2;
    g->adj[0][2] = g->adj[2][0] = 5;

    // Componente 2: vertices 3, 4, 5
    g->adj[3][4] = g->adj[4][3] = 1;
    g->adj[4][5] = g->adj[5][4] = 4;

    printf("\nGrafo desconexo:\n");
    printf("Componente 1: 0-1(3), 1-2(2), 0-2(5)\n");
    printf("Componente 2: 3-4(1), 4-5(4)\n");

    printf("\nPrim a partir do vertice 0 (só alcanca componente 1):\n");
    int* pai = prim(g, 0);

    printf("\nArestas da MST:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai[i] != i) {
            printf("  %d - %d (peso: %d)\n", pai[i], i, g->adj[pai[i]][i]);
        }
    }

    free(pai);
    DestroiGrafo(g);
}

int main(void) {
    printf("Operacões Basicas de Grafos\n");
    operacoesBasicas();

    printf("\n\nPopularidade e Recomendacões\n");
    popularidadeRecomendacoes();

    printf("\n\nAnalise de Caminhos\n");
    caminhos();

    printf("\n\nComponentes Conexas\n");
    componentesConexas();

    printf("\n\nGrafo Completo\n");
    grafoCompleto();

    printf("\n\nBusca em Profundidade (Recursiva)\n");
    buscaProfundidade();

    printf("\n\nBusca em Profundidade (Iterativa)\n");
    buscaIterativa();

    printf("\n\nBusca em Largura\n");
    buscaLargura();

    printf("\n\nAlgoritmo de Prim (MST)\n");
    primBasico();

    printf("\n\nPrim em Grafo Completo\n");
    primGrafoCompleto();

    printf("\n\nPrim em Grafo Desconexo\n");
    primDesconexo();

    printf("\n\nPrograma finalizado.\n");
    return 0;
}