#include <assert.h>
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

void teste_CriarGrafo() {
    printf("\n=== Teste: CriarGrafo ===\n");
    p_grafo g = CriarGrafo(5);
    assert(g != NULL);
    assert(g->n == 5);
    printf("✓ Grafo criado com 5 vértices\n");

    // Verifica se todas as posições estão inicializadas com 0
    int i, j, todas_zero = 1;
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            if (g->adj[i][j] != 0) {
                todas_zero = 0;
            }
        }
    }
    assert(todas_zero == 1);
    printf("✓ Matriz de adjacência inicializada corretamente\n");

    DestroiGrafo(g);
}

void teste_InsereAresta() {
    printf("\n=== Teste: InsereAresta ===\n");
    p_grafo g = CriarGrafo(4);

    // Testa inserção de aresta simples
    InsereAresta(g, 0, 1);
    assert(g->adj[0][1] == 1);
    assert(g->adj[1][0] == 1);
    printf("✓ Aresta (0,1) inserida corretamente\n");

    // Testa múltiplas arestas
    InsereAresta(g, 1, 2);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 0, 3);
    assert(g->adj[1][2] == 1 && g->adj[2][1] == 1);
    assert(g->adj[2][3] == 1 && g->adj[3][2] == 1);
    assert(g->adj[0][3] == 1 && g->adj[3][0] == 1);
    printf("✓ Múltiplas arestas inseridas corretamente\n");

    // Testa laço (aresta do vértice para ele mesmo)
    InsereAresta(g, 2, 2);
    assert(g->adj[2][2] == 1);
    printf("✓ Laço (2,2) inserido corretamente\n");

    DestroiGrafo(g);
}

void teste_RemoveAresta() {
    printf("\n=== Teste: RemoveAresta ===\n");
    p_grafo g = CriarGrafo(4);

    // Insere e remove aresta
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    RemoveAresta(g, 0, 1);
    assert(g->adj[0][1] == 0);
    assert(g->adj[1][0] == 0);
    assert(g->adj[1][2] == 1);  // Verifica que outras arestas não foram afetadas
    printf("✓ Aresta (0,1) removida corretamente\n");

    // Remove laço
    InsereAresta(g, 3, 3);
    RemoveAresta(g, 3, 3);
    assert(g->adj[3][3] == 0);
    printf("✓ Laço (3,3) removido corretamente\n");

    DestroiGrafo(g);
}

void teste_TemAresta() {
    printf("\n=== Teste: TemAresta ===\n");
    p_grafo g = CriarGrafo(4);

    assert(TemAresta(g, 0, 1) == 0);
    printf("✓ Verifica ausência de aresta corretamente\n");

    InsereAresta(g, 0, 1);
    assert(TemAresta(g, 0, 1) == 1);
    assert(TemAresta(g, 1, 0) == 1);
    printf("✓ Verifica presença de aresta corretamente\n");

    InsereAresta(g, 2, 2);
    assert(TemAresta(g, 2, 2) == 1);
    printf("✓ Verifica presença de laço corretamente\n");

    DestroiGrafo(g);
}

void teste_ImprimeArestas() {
    printf("\n=== Teste: ImprimeArestas ===\n");
    p_grafo g = CriarGrafo(3);

    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 0, 2);

    printf("Arestas do grafo:\n");
    ImprimeArestas(g);
    printf("✓ Função executada (verificar saída acima)\n");

    DestroiGrafo(g);
}

void teste_Grau() {
    printf("\n=== Teste: Grau ===\n");
    p_grafo g = CriarGrafo(5);

    // Vértice sem arestas
    assert(Grau(g, 0) == 0);
    printf("✓ Grau de vértice isolado = 0\n");

    // Vértice com uma aresta
    InsereAresta(g, 0, 1);
    assert(Grau(g, 0) == 1);
    assert(Grau(g, 1) == 1);
    printf("✓ Grau correto após inserir uma aresta\n");

    // Vértice com múltiplas arestas
    InsereAresta(g, 0, 2);
    InsereAresta(g, 0, 3);
    InsereAresta(g, 0, 4);
    assert(Grau(g, 0) == 4);
    printf("✓ Grau correto com múltiplas arestas: %d\n", Grau(g, 0));

    // Vértice com laço
    InsereAresta(g, 2, 2);
    int grau2 = Grau(g, 2);
    printf("✓ Grau do vértice 2 com laço: %d\n", grau2);

    DestroiGrafo(g);
}

void teste_MaisPopular() {
    printf("\n=== Teste: MaisPopular ===\n");
    p_grafo g = CriarGrafo(5);

    // Todos os vértices com grau 0 - deve retornar 0
    assert(MaisPopular(g) == 0);
    printf("✓ Vértice mais popular quando todos têm grau 0: %d\n", MaisPopular(g));

    // Vértice 2 com maior grau
    InsereAresta(g, 2, 0);
    InsereAresta(g, 2, 1);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 2, 4);
    assert(MaisPopular(g) == 2);
    printf("✓ Vértice mais popular identificado: %d (grau %d)\n", MaisPopular(g), Grau(g, 2));

    // Vértice 4 se torna mais popular
    InsereAresta(g, 4, 0);
    InsereAresta(g, 4, 1);
    InsereAresta(g, 4, 3);
    InsereAresta(g, 1, 3);
    int popular = MaisPopular(g);
    printf("✓ Novo vértice mais popular: %d (grau %d)\n", popular, Grau(g, popular));

    DestroiGrafo(g);
}

void teste_ImprimeRecomendacoes() {
    printf("\n=== Teste: ImprimeRecomendacoes ===\n");
    p_grafo g = CriarGrafo(6);

    // Cria um grafo social: 0 conectado a 1 e 2
    // 1 conectado a 3 e 4
    // 2 conectado a 5
    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 1, 4);
    InsereAresta(g, 2, 5);

    printf("Recomendações para vértice 0 (amigos: 1, 2):\n");
    printf("Esperado: 3, 4 (amigos de 1) e 5 (amigo de 2)\n");
    ImprimeRecomendacoes(g, 0);
    printf("✓ Função executada (verificar saída acima)\n");

    printf("\nRecomendações para vértice 1 (amigos: 0, 3, 4):\n");
    printf("Esperado: 2 (amigo de 0) e 5 (se existir conexão)\n");
    ImprimeRecomendacoes(g, 1);
    printf("✓ Função executada (verificar saída acima)\n");

    DestroiGrafo(g);
}

void teste_ExisteCaminho() {
    printf("\n=== Teste: ExisteCaminho ===\n");
    p_grafo g = CriarGrafo(6);

    // Grafo desconexo: componente 1 = {0,1,2}, componente 2 = {3,4}, vértice isolado = {5}
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 3, 4);

    // Testa caminhos dentro do mesmo componente
    assert(ExisteCaminho(g, 0, 2) == 1);
    printf("✓ Caminho existe entre 0 e 2: SIM\n");

    assert(ExisteCaminho(g, 3, 4) == 1);
    printf("✓ Caminho existe entre 3 e 4: SIM\n");

    // Testa caminhos entre componentes diferentes
    assert(ExisteCaminho(g, 0, 3) == 0);
    printf("✓ Caminho existe entre 0 e 3: NÃO\n");

    assert(ExisteCaminho(g, 0, 5) == 0);
    printf("✓ Caminho existe entre 0 e 5 (isolado): NÃO\n");

    // Testa caminho de um vértice para ele mesmo
    assert(ExisteCaminho(g, 0, 0) == 1);
    printf("✓ Caminho existe de 0 para 0: SIM\n");

    // Conecta os componentes e testa novamente
    InsereAresta(g, 2, 3);
    assert(ExisteCaminho(g, 0, 4) == 1);
    printf("✓ Após conectar componentes, caminho 0 → 4: SIM\n");

    DestroiGrafo(g);
}

void teste_LeGrafo() {
    printf("\n=== Teste: LeGrafo ===\n");
    printf("Função LeGrafo requer entrada manual via stdin.\n");
    printf("Para testar, execute o programa e forneça:\n");
    printf("  Primeira linha: <num_vertices> <num_arestas>\n");
    printf("  Linhas seguintes: <vertice_u> <vertice_v>\n");
    printf("✓ Teste manual necessário\n");
}

void teste_DestroiGrafo() {
    printf("\n=== Teste: DestroiGrafo ===\n");
    p_grafo g = CriarGrafo(10);
    InsereAresta(g, 0, 1);
    InsereAresta(g, 2, 3);
    DestroiGrafo(g);
    printf("Grafo destruido sem erros (verificar com valgrind para vazamentos)\n");
}

void teste_EncontraComponentes() {
    printf("\n=== Teste: EncontraComponentes ===\n");
    p_grafo g = CriarGrafo(7);

    // Cria tres componentes: {0,1,2}, {3,4}, {5,6}
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 5, 6);

    int* componentes = EncontraComponentes(g);
    printf("Componente do vertice 0: %d\n", componentes[0]);
    printf("Componente do vertice 1: %d\n", componentes[1]);
    printf("Componente do vertice 2: %d\n", componentes[2]);
    printf("Componente do vertice 3: %d\n", componentes[3]);
    printf("Componente do vertice 4: %d\n", componentes[4]);
    printf("Componente do vertice 5: %d\n", componentes[5]);
    printf("Componente do vertice 6: %d\n", componentes[6]);

    // Verifica que vertices do mesmo componente tem o mesmo numero
    assert(componentes[0] == componentes[1]);
    assert(componentes[1] == componentes[2]);
    assert(componentes[3] == componentes[4]);
    assert(componentes[5] == componentes[6]);

    // Verifica que componentes diferentes tem numeros diferentes
    assert(componentes[0] != componentes[3]);
    assert(componentes[0] != componentes[5]);
    assert(componentes[3] != componentes[5]);

    printf("Tres componentes conexas identificadas corretamente\n");

    free(componentes);
    DestroiGrafo(g);
}

void teste_encontraCaminhos() {
    printf("\n=== Teste: encontraCaminhos ===\n");
    p_grafo g = CriarGrafo(8);

    // Cria um grafo com estrutura de arvore e componentes separadas
    // Componente 1: 0-1-2, 1-3
    InsereAresta(g, 0, 1);
    InsereAresta(g, 1, 2);
    InsereAresta(g, 1, 3);

    // Componente 2: 4-5-6
    InsereAresta(g, 4, 5);
    InsereAresta(g, 5, 6);

    // Vertice isolado: 7

    printf("\nBusca em profundidade a partir do vertice 0:\n");
    int* pai0 = encontraCaminhos(g, 0);
    printf("Arvore de caminhos (vetor pai) a partir de 0:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai0[i] == -1) {
            printf("Vertice %d: nao alcancavel (pai = -1)\n", i);
        } else if (pai0[i] == i) {
            printf("Vertice %d: raiz da busca (pai = %d)\n", i, pai0[i]);
        } else {
            printf("Vertice %d: pai = %d, caminho: ", i, pai0[i]);
            imprimeCaminho(pai0, i);
            printf("\n");
        }
    }

    printf("\nBusca em profundidade a partir do vertice 4:\n");
    int* pai4 = encontraCaminhos(g, 4);
    printf("Arvore de caminhos (vetor pai) a partir de 4:\n");
    for (int i = 0; i < g->n; i++) {
        if (pai4[i] == -1) {
            printf("Vertice %d: nao alcancavel (pai = -1)\n", i);
        } else if (pai4[i] == i) {
            printf("Vertice %d: raiz da busca (pai = %d)\n", i, pai4[i]);
        } else {
            printf("Vertice %d: pai = %d, caminho: ", i, pai4[i]);
            imprimeCaminho(pai4, i);
            printf("\n");
        }
    }

    // Verifica corretude
    assert(pai0[0] == 0);   // 0 e raiz
    assert(pai0[1] == 0);   // 1 tem pai 0
    assert(pai0[4] == -1);  // 4 nao alcancavel de 0
    assert(pai4[4] == 4);   // 4 e raiz
    assert(pai4[0] == -1);  // 0 nao alcancavel de 4

    printf("Funcao encontraCaminhos funcionando corretamente\n");

    free(pai0);
    free(pai4);
    DestroiGrafo(g);
}

void teste_busca_em_profundidade_iterativa() {
    printf("\n=== Teste: busca_em_profundidade (iterativa com pilha) ===\n");
    p_grafo g = CriarGrafo(6);

    // Cria um grafo ciclico para testar
    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 1, 3);
    InsereAresta(g, 2, 3);
    InsereAresta(g, 3, 4);
    InsereAresta(g, 4, 5);

    printf("Busca iterativa a partir do vertice 0:\n");
    int* pai = busca_em_profundidade(g, 0);

    printf("Arvore de caminhos (versao iterativa):\n");
    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai[i] == i) {
            printf("Vertice %d: raiz\n", i);
        } else {
            printf("Vertice %d: pai = %d, caminho: ", i, pai[i]);
            imprimeCaminho(pai, i);
            printf("\n");
        }
    }

    // Verifica que todos os vertices foram alcancados
    for (int i = 0; i < g->n; i++) {
        assert(pai[i] != -1);
    }
    printf("Todos os vertices alcancados pela busca iterativa\n");

    free(pai);
    DestroiGrafo(g);
}

void teste_busca_em_largura() {
    printf("\n=== Teste: busca_em_largura (BFS) ===\n");
    p_grafo g = CriarGrafo(7);

    // Cria um grafo para demonstrar a diferenca entre DFS e BFS
    // Estrutura: 0 conectado a 1,2,3; 1 conectado a 4; 2 conectado a 5; 3 conectado a 6
    InsereAresta(g, 0, 1);
    InsereAresta(g, 0, 2);
    InsereAresta(g, 0, 3);
    InsereAresta(g, 1, 4);
    InsereAresta(g, 2, 5);
    InsereAresta(g, 3, 6);

    printf("BFS a partir do vertice 0 (explora nivel por nivel):\n");
    int* pai_bfs = busca_em_largura(g, 0);

    printf("Arvore de caminhos (BFS - caminhos mais curtos):\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_bfs[i] == -1) {
            printf("Vertice %d: nao alcancavel\n", i);
        } else if (pai_bfs[i] == i) {
            printf("Vertice %d: raiz (nivel 0)\n", i);
        } else {
            printf("Vertice %d: pai = %d, caminho: ", i, pai_bfs[i]);
            imprimeCaminho(pai_bfs, i);
            printf("\n");
        }
    }

    // Compara com DFS para mostrar a diferenca
    printf("\nDFS a partir do vertice 0 (para comparacao):\n");
    int* pai_dfs = busca_em_profundidade(g, 0);

    printf("Arvore de caminhos (DFS):\n");
    for (int i = 0; i < g->n; i++) {
        if (pai_dfs[i] == i) {
            printf("Vertice %d: raiz\n", i);
        } else {
            printf("Vertice %d: pai = %d, caminho: ", i, pai_dfs[i]);
            imprimeCaminho(pai_dfs, i);
            printf("\n");
        }
    }

    // Verifica que todos foram alcancados
    for (int i = 0; i < g->n; i++) {
        assert(pai_bfs[i] != -1);
        assert(pai_dfs[i] != -1);
    }

    printf("\nBFS garante caminhos mais curtos em grafos nao ponderados\n");

    free(pai_bfs);
    free(pai_dfs);
    DestroiGrafo(g);
}

void teste_GrafoCompleto() {
    printf("\n=== Teste: Grafo Completo K4 ===\n");
    p_grafo g = CriarGrafo(4);

    // Cria um grafo completo K4
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            InsereAresta(g, i, j);
        }
    }

    // Verifica que todos os vértices têm grau 3
    for (i = 0; i < 4; i++) {
        assert(Grau(g, i) == 3);
    }
    printf("✓ Grafo completo K4 criado corretamente\n");
    printf("✓ Todos os vértices têm grau 3\n");

    // Verifica que existe caminho entre todos os pares
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            assert(ExisteCaminho(g, i, j) == 1);
        }
    }
    printf("✓ Existe caminho entre todos os pares de vértices\n");

    DestroiGrafo(g);
}

int main(void) {
    printf("╔═══════════════════════════════════════════╗\n");
    printf("║  TESTES DO GRAFO (MATRIZ DE ADJACÊNCIA)  ║\n");
    printf("╚═══════════════════════════════════════════╝\n");

    teste_CriarGrafo();
    teste_InsereAresta();
    teste_RemoveAresta();
    teste_TemAresta();
    teste_ImprimeArestas();
    teste_Grau();
    teste_MaisPopular();
    teste_ImprimeRecomendacoes();
    teste_ExisteCaminho();
    teste_LeGrafo();
    teste_DestroiGrafo();
    teste_EncontraComponentes();
    teste_encontraCaminhos();
    teste_busca_em_profundidade_iterativa();
    teste_busca_em_largura();
    teste_GrafoCompleto();

    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║      TODOS OS TESTES FORAM EXECUTADOS     ║\n");
    printf("╚═══════════════════════════════════════════╝\n");

    return 0;
}