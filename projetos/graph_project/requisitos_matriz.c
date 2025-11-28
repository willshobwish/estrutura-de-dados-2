#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../matrice/graph.h"
#include "requisitos_comum.h"

/*
 * Funcao construir_grafo_requisitos_matriz
 * Constroi um grafo direcionado de pre-requisitos usando matriz de adjacência
 * Aresta de A para B significa: A e pre-requisito de B
 */
p_grafo construir_grafo_requisitos_matriz(const char* arquivo, MapaDisciplinas* mapa) {
    p_grafo g = CriarGrafo(mapa->total);

    FILE* fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return g;
    }

    char linha[MAX_LINHA];
    // Pula cabecalho
    fgets(linha, sizeof(linha), fp);

    int total_prereqs = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        char codigo_disc[MAX_CODIGO];
        char nome_disc[MAX_NOME];
        char codigo_prereq[MAX_CODIGO];

        // Remove newline
        linha[strcspn(linha, "\n")] = 0;

        // Parsing da linha CSV: Ano,Semestre,Codigo,Disciplinas,Codigo-Pre-Requisito,Pre-Requisito
        char* token = strtok(linha, ",");
        if (!token) continue;  // ano

        token = strtok(NULL, ",");
        if (!token) continue;  // semestre

        token = strtok(NULL, ",");
        if (!token) continue;  // codigo
        strncpy(codigo_disc, token, MAX_CODIGO - 1);
        codigo_disc[MAX_CODIGO - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;  // nome da disciplina
        strncpy(nome_disc, token, MAX_NOME - 1);
        nome_disc[MAX_NOME - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token || strlen(token) == 0) continue;  // codigo pre-requisito
        strncpy(codigo_prereq, token, MAX_CODIGO - 1);
        codigo_prereq[MAX_CODIGO - 1] = '\0';

        // Busca indices das disciplinas
        int idx_disc = buscar_indice_disciplina(mapa, codigo_disc);
        int idx_prereq = buscar_indice_disciplina(mapa, codigo_prereq);

        if (idx_disc != -1 && idx_prereq != -1) {
            // Insere aresta: pre-requisito -> disciplina
            InsereAresta(g, idx_prereq, idx_disc);
            total_prereqs++;
        }
    }

    fclose(fp);
    printf("\nGrafo de Pre-Requisitos (matriz) Construido\n");
    printf("Vertices: %d disciplinas\n", mapa->total);
    printf("Arestas: %d relacoes de pre-requisito\n", total_prereqs);

    return g;
}

/*
 * Funcao imprimir_prerequisitos
 * Imprime os pre-requisitos de cada disciplina
 */
void imprimir_prerequisitos(p_grafo g, MapaDisciplinas* mapa) {
    printf("\nPre-requisitos por disciplina\n");
    for (int i = 0; i < mapa->total; i++) {
        int tem_prereq = 0;
        printf("\n%s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
        printf("  Pre-requisitos: ");

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
 * Funcao imprimir_dependentes
 * Imprime as disciplinas que dependem de cada uma
 */
void imprimir_dependentes(p_grafo g, MapaDisciplinas* mapa) {
    printf("\nDisciplinas Dependentes\n");
    for (int i = 0; i < mapa->total; i++) {
        int tem_dep = 0;
        printf("\n%s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
        printf("  e pre-requisito de: ");

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
 * Funcao verificar_ordem_possivel
 * Verifica se uma sequência de disciplinas respeita os pre-requisitos
 */
int verificar_ordem_possivel(p_grafo g, MapaDisciplinas* mapa, int* ordem, int tamanho) {
    int* concluidas = calloc(mapa->total, sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        int disc = ordem[i];

        // Verifica se todos os pre-requisitos foram concluidos
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, disc) && !concluidas[j]) {
                printf("ERRO: %s requer %s que ainda nao foi cursada!\n",
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
 * Funcao disciplinas_podem_cursar
 * Lista disciplinas que podem ser cursadas dado um conjunto de disciplinas ja concluidas
 */
void disciplinas_podem_cursar(p_grafo g, MapaDisciplinas* mapa, int* concluidas) {
    printf("\nDisciplinas disponiveis para cursar\n");
    int count = 0;

    for (int i = 0; i < mapa->total; i++) {
        if (concluidas[i]) continue;  // Ja concluida

        int pode_cursar = 1;
        // Verifica se todos os pre-requisitos foram concluidos
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
        printf("  (nenhuma disponivel)\n");
    } else {
        printf("\nTotal: %d disciplinas disponiveis\n", count);
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

    // Constroi grafo de pre-requisitos usando matriz
    p_grafo g = construir_grafo_requisitos_matriz("Disciplinas.csv", mapa);

    // Imprime pre-requisitos
    imprimir_prerequisitos(g, mapa);

    // Imprime dependentes
    imprimir_dependentes(g, mapa);

    // Testa ordem das disciplinas do 1o ano, 1o semestre
    printf("\n\nDisciplinas do 1o ano, 1o semestre\n");
    printf("Estas disciplinas nao têm pre-requisitos, podem ser cursadas em qualquer ordem.\n");
    int ordem1[] = {0, 1, 2, 3, 4, 5};  // Primeiras 6 disciplinas
    printf("Ordem testada: ");
    for (int i = 0; i < 6; i++) {
        printf("%s ", mapa->disciplinas[ordem1[i]].codigo);
    }
    printf("\n");
    if (verificar_ordem_possivel(g, mapa, ordem1, 6)) {
        printf("Ordem valida!\n");
    }

    // Simula estudante que concluiu 1o ano
    printf("\n\nApos Concluir 1o Ano\n");
    int* concluidas = calloc(mapa->total, sizeof(int));
    // Marca disciplinas do 1o ano como concluidas
    for (int i = 0; i < mapa->total; i++) {
        if (mapa->disciplinas[i].ano == 1) {
            concluidas[i] = 1;
        }
    }
    disciplinas_podem_cursar(g, mapa, concluidas);

    // Encontra componentes conexas (disciplinas relacionadas)
    printf("\n\nComponentes Conexas\n");
    int* componentes = EncontraComponentes(g);
    printf("Analise de componentes conexas do grafo (desconsiderando direcao):\n");
    int max_comp = 0;
    for (int i = 0; i < mapa->total; i++) {
        if (componentes[i] > max_comp) max_comp = componentes[i];
    }
    printf("Total de componentes: %d\n", max_comp + 1);

    // Busca em largura a partir de uma disciplina base
    printf("\n\nBusca em Largura\n");
    int idx_atp1 = buscar_indice_disciplina(mapa, "CIC002MAT3");  // Algoritmos I
    if (idx_atp1 != -1) {
        printf("Disciplinas alcancaveis a partir de %s:\n", mapa->disciplinas[idx_atp1].nome);
        int* pai_bfs = busca_em_largura(g, idx_atp1);

        for (int i = 0; i < mapa->total; i++) {
            if (pai_bfs[i] != -1 && i != idx_atp1) {
                printf("  %s (distancia: ", mapa->disciplinas[i].nome);
                // Calcula distancia
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

    // Disciplinas com mais pre-requisitos (maior grau de entrada)
    printf("\n\nDisciplinas com mais pre-requisitos\n");
    printf("(aquelas que exigem mais disciplinas antes)\n\n");
    int max_prereqs = 0;
    for (int i = 0; i < mapa->total; i++) {
        int num_prereqs = 0;
        // Conta quantos pre-requisitos esta disciplina tem (grau de entrada)
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i)) {
                num_prereqs++;
            }
        }
        if (num_prereqs > max_prereqs) max_prereqs = num_prereqs;
    }

    for (int i = 0; i < mapa->total; i++) {
        int num_prereqs = 0;
        // Conta quantos pre-requisitos esta disciplina tem
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i)) {
                num_prereqs++;
            }
        }
        if (num_prereqs == max_prereqs && num_prereqs > 0) {
            printf("  %s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
            printf(" -> requer %d pre-requisitos diretos\n\n", num_prereqs);
        }
    }

    free(componentes);
    free(concluidas);
    DestroiGrafo(g);
    liberar_mapa(mapa);
    return 0;
}
