#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrice/graph.h"
#include "requisitos_comum.h"

/*
 * Função construir_grafo_requisitos_matriz
 * Constrói um grafo direcionado de pré-requisitos usando matriz de adjacência
 * Aresta de A para B significa: A é pré-requisito de B
 */
p_grafo construir_grafo_requisitos_matriz(const char* arquivo, MapaDisciplinas* mapa) {
    p_grafo g = CriarGrafo(mapa->total);

    FILE* fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return g;
    }

    char linha[MAX_LINHA];
    // Pula cabeçalho
    fgets(linha, sizeof(linha), fp);

    int total_prereqs = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        char disciplina[MAX_NOME];
        char prereq[MAX_NOME];

        // Remove newline
        linha[strcspn(linha, "\n")] = 0;

        // Parsing da linha CSV
        char* token = strtok(linha, ",");
        if (!token) continue;

        token = strtok(NULL, ",");  // semestre
        if (!token) continue;

        token = strtok(NULL, ",");  // disciplina
        if (!token) continue;
        strncpy(disciplina, token, MAX_NOME - 1);
        disciplina[MAX_NOME - 1] = '\0';

        token = strtok(NULL, ",");  // pré-requisito
        if (!token || strlen(token) == 0) continue;

        strncpy(prereq, token, MAX_NOME - 1);
        prereq[MAX_NOME - 1] = '\0';

        // Extrai código da disciplina atual
        char codigo_disc[MAX_CODIGO];
        extrair_codigo(disciplina, codigo_disc);
        int idx_disc = buscar_indice_disciplina(mapa, codigo_disc);

        if (idx_disc == -1) continue;

        // Procura por "CIC" no pré-requisito para extrair o código
        char* pos = strstr(prereq, "CIC");
        if (pos) {
            char codigo_prereq[MAX_CODIGO];
            extrair_codigo(pos, codigo_prereq);
            int idx_prereq = buscar_indice_disciplina(mapa, codigo_prereq);

            if (idx_prereq != -1) {
                // Insere aresta: pré-requisito -> disciplina
                InsereAresta(g, idx_prereq, idx_disc);
                total_prereqs++;
            }
        }
    }

    fclose(fp);
    printf("\n=== Grafo de Pré-Requisitos (Matriz) Construído ===\n");
    printf("Vértices: %d disciplinas\n", mapa->total);
    printf("Arestas: %d relações de pré-requisito\n", total_prereqs);

    return g;
}

/*
 * Função imprimir_prerequisitos
 * Imprime os pré-requisitos de cada disciplina
 */
void imprimir_prerequisitos(p_grafo g, MapaDisciplinas* mapa) {
    printf("\n=== Pré-Requisitos por Disciplina ===\n");
    for (int i = 0; i < mapa->total; i++) {
        int tem_prereq = 0;
        printf("\n%s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
        printf("  Pré-requisitos: ");

        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i)) {
                if (tem_prereq) printf(", ");
                printf("%s", mapa->disciplinas[j].codigo);
                tem_prereq = 1;
            }
        }

        if (!tem_prereq) {
            printf("(nenhum)");
        }
        printf("\n");
    }
}

/*
 * Função imprimir_dependentes
 * Imprime as disciplinas que dependem de cada uma
 */
void imprimir_dependentes(p_grafo g, MapaDisciplinas* mapa) {
    printf("\n=== Disciplinas Dependentes ===\n");
    for (int i = 0; i < mapa->total; i++) {
        int tem_dep = 0;
        printf("\n%s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
        printf("  É pré-requisito de: ");

        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, i, j)) {
                if (tem_dep) printf(", ");
                printf("%s", mapa->disciplinas[j].codigo);
                tem_dep = 1;
            }
        }

        if (!tem_dep) {
            printf("(nenhuma)");
        }
        printf("\n");
    }
}

/*
 * Função verificar_ordem_possivel
 * Verifica se uma sequência de disciplinas respeita os pré-requisitos
 */
int verificar_ordem_possivel(p_grafo g, MapaDisciplinas* mapa, int* ordem, int tamanho) {
    int* concluidas = calloc(mapa->total, sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        int disc = ordem[i];

        // Verifica se todos os pré-requisitos foram concluídos
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, disc) && !concluidas[j]) {
                printf("ERRO: %s requer %s que ainda não foi cursada!\n",
                       mapa->disciplinas[disc].codigo,
                       mapa->disciplinas[j].codigo);
                free(concluidas);
                return 0;
            }
        }

        concluidas[disc] = 1;
    }

    free(concluidas);
    return 1;
}

/*
 * Função disciplinas_podem_cursar
 * Lista disciplinas que podem ser cursadas dado um conjunto de disciplinas já concluídas
 */
void disciplinas_podem_cursar(p_grafo g, MapaDisciplinas* mapa, int* concluidas) {
    printf("\n=== Disciplinas Disponíveis para Cursar ===\n");
    int count = 0;

    for (int i = 0; i < mapa->total; i++) {
        if (concluidas[i]) continue;  // Já concluída

        int pode_cursar = 1;
        // Verifica se todos os pré-requisitos foram concluídos
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i) && !concluidas[j]) {
                pode_cursar = 0;
                break;
            }
        }

        if (pode_cursar) {
            printf("  [%d] %s - %s (Ano %d, Sem %d)\n",
                   i,
                   mapa->disciplinas[i].codigo,
                   mapa->disciplinas[i].nome,
                   mapa->disciplinas[i].ano,
                   mapa->disciplinas[i].semestre);
            count++;
        }
    }

    if (count == 0) {
        printf("  (nenhuma disponível)\n");
    } else {
        printf("\nTotal: %d disciplinas disponíveis\n", count);
    }
}

int main(void) {
    // Carrega todas as disciplinas do CSV
    MapaDisciplinas* mapa = carregar_disciplinas("Disciplinas.csv");
    if (!mapa) {
        return 1;
    }

    // Imprime disciplinas carregadas
    imprimir_mapa_disciplinas(mapa);

    // Constrói grafo de pré-requisitos usando matriz
    p_grafo g = construir_grafo_requisitos_matriz("Disciplinas.csv", mapa);

    // Imprime pré-requisitos
    imprimir_prerequisitos(g, mapa);

    // Imprime dependentes
    imprimir_dependentes(g, mapa);

    // Testa ordem das disciplinas do 1º ano, 1º semestre
    printf("\n\n=== TESTE 1: Disciplinas do 1º Ano, 1º Semestre ===\n");
    printf("Estas disciplinas não têm pré-requisitos, podem ser cursadas em qualquer ordem.\n");
    int ordem1[] = {0, 1, 2, 3, 4, 5};  // Primeiras 6 disciplinas
    printf("Ordem testada: ");
    for (int i = 0; i < 6; i++) {
        printf("%s ", mapa->disciplinas[ordem1[i]].codigo);
    }
    printf("\n");
    if (verificar_ordem_possivel(g, mapa, ordem1, 6)) {
        printf("✓ Ordem válida!\n");
    }

    // Simula estudante que concluiu 1º ano
    printf("\n\n=== TESTE 2: Após Concluir 1º Ano ===\n");
    int* concluidas = calloc(mapa->total, sizeof(int));
    // Marca disciplinas do 1º ano como concluídas
    for (int i = 0; i < mapa->total; i++) {
        if (mapa->disciplinas[i].ano == 1) {
            concluidas[i] = 1;
        }
    }
    disciplinas_podem_cursar(g, mapa, concluidas);

    // Encontra componentes conexas (disciplinas relacionadas)
    printf("\n\n=== TESTE 3: Componentes Conexas ===\n");
    int* componentes = EncontraComponentes(g);
    printf("Análise de componentes conexas do grafo (desconsiderando direção):\n");
    int max_comp = 0;
    for (int i = 0; i < mapa->total; i++) {
        if (componentes[i] > max_comp) max_comp = componentes[i];
    }
    printf("Total de componentes: %d\n", max_comp + 1);

    // Busca em largura a partir de uma disciplina base
    printf("\n\n=== TESTE 4: Busca em Largura ===\n");
    int idx_atp1 = buscar_indice_disciplina(mapa, "CIC002MAT3");  // Algoritmos I
    if (idx_atp1 != -1) {
        printf("Disciplinas alcançáveis a partir de %s:\n", mapa->disciplinas[idx_atp1].nome);
        int* pai_bfs = busca_em_largura(g, idx_atp1);

        for (int i = 0; i < mapa->total; i++) {
            if (pai_bfs[i] != -1 && i != idx_atp1) {
                printf("  %s (distância: ", mapa->disciplinas[i].codigo);
                // Calcula distância
                int dist = 0;
                int atual = i;
                while (pai_bfs[atual] != atual) {
                    dist++;
                    atual = pai_bfs[atual];
                }
                printf("%d)\n", dist);
            }
        }
        free(pai_bfs);
    }

    // Disciplinas mais importantes (maior grau de saída)
    printf("\n\n=== TESTE 5: Disciplinas Mais Importantes ===\n");
    printf("(aquelas que são pré-requisito para mais disciplinas)\n\n");
    int max_grau = 0;
    for (int i = 0; i < mapa->total; i++) {
        int grau = Grau(g, i);
        if (grau > max_grau) max_grau = grau;
    }

    for (int i = 0; i < mapa->total; i++) {
        int grau = Grau(g, i);
        if (grau == max_grau && grau > 0) {
            printf("  %s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
            printf("  → É pré-requisito (direto ou indireto) para %d disciplinas\n\n", grau);
        }
    }

    // Cleanup
    free(componentes);
    free(concluidas);
    DestroiGrafo(g);
    liberar_mapa(mapa);

    printf("\n=== Programa Finalizado ===\n");
    return 0;
}
