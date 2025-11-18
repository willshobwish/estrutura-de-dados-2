#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list/graph.h"
#include "requisitos_comum.h"

/*
 * Funcao construir_grafo_requisitos_lista
 * Constroi um grafo direcionado de pre-requisitos usando lista de adjacência
 * Aresta de A para B significa: A e pre-requisito de B
 */
p_grafo construir_grafo_requisitos_lista(const char* arquivo, MapaDisciplinas* mapa) {
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

        token = strtok(NULL, ",");  // pre-requisito
        if (!token || strlen(token) == 0) continue;

        strncpy(prereq, token, MAX_NOME - 1);
        prereq[MAX_NOME - 1] = '\0';

        // Extrai codigo da disciplina atual
        char codigo_disc[MAX_CODIGO];
        extrair_codigo(disciplina, codigo_disc);
        int idx_disc = buscar_indice_disciplina(mapa, codigo_disc);

        if (idx_disc == -1) continue;

        // Procura por "CIC" no pre-requisito para extrair o codigo
        char* pos = strstr(prereq, "CIC");
        if (pos) {
            char codigo_prereq[MAX_CODIGO];
            extrair_codigo(pos, codigo_prereq);
            int idx_prereq = buscar_indice_disciplina(mapa, codigo_prereq);

            if (idx_prereq != -1) {
                // Insere aresta: pre-requisito -> disciplina
                InsereAresta(g, idx_prereq, idx_disc);
                total_prereqs++;
            }
        }
    }

    fclose(fp);
    printf("\n=== Grafo de Pre-Requisitos (Lista) Construido ===\n");
    printf("Vertices: %d disciplinas\n", mapa->total);
    printf("Arestas: %d relacoes de pre-requisito\n", total_prereqs);

    return g;
}

/*
 * Funcao imprimir_prerequisitos_lista
 * Imprime os pre-requisitos de cada disciplina (versao lista)
 */
void imprimir_prerequisitos_lista(p_grafo g, MapaDisciplinas* mapa) {
    printf("\n=== Pre-Requisitos por Disciplina ===\n");
    for (int i = 0; i < mapa->total; i++) {
        int tem_prereq = 0;
        printf("\n%s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
        printf("  Pre-requisitos: ");

        // Percorre todas as disciplinas procurando quais apontam para i
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
 * Funcao calcular_nivel_disciplina
 * Calcula o nivel de uma disciplina (maxima cadeia de pre-requisitos)
 */
int calcular_nivel_disciplina(p_grafo g, int disc, int* niveis, int* visitado) {
    if (niveis[disc] != -1) return niveis[disc];
    if (visitado[disc]) return 0;  // Evita ciclos

    visitado[disc] = 1;
    int max_nivel = 0;

    // Procura pre-requisitos (arestas que chegam em disc)
    for (int i = 0; i < g->n; i++) {
        if (TemAresta(g, i, disc)) {
            int nivel = calcular_nivel_disciplina(g, i, niveis, visitado);
            if (nivel + 1 > max_nivel) {
                max_nivel = nivel + 1;
            }
        }
    }

    visitado[disc] = 0;
    niveis[disc] = max_nivel;
    return max_nivel;
}

/*
 * Funcao organizar_por_niveis
 * Organiza disciplinas por niveis de pre-requisitos
 */
void organizar_por_niveis(p_grafo g, MapaDisciplinas* mapa) {
    printf("\n=== Organizacao por Niveis de Pre-Requisitos ===\n");

    int* niveis = malloc(mapa->total * sizeof(int));
    int* visitado = calloc(mapa->total, sizeof(int));

    for (int i = 0; i < mapa->total; i++) {
        niveis[i] = -1;
    }

    // Calcula nivel de cada disciplina
    int max_nivel = 0;
    for (int i = 0; i < mapa->total; i++) {
        int nivel = calcular_nivel_disciplina(g, i, niveis, visitado);
        if (nivel > max_nivel) max_nivel = nivel;
    }

    // Imprime por nivel
    for (int nivel = 0; nivel <= max_nivel; nivel++) {
        printf("\nNivel %d (podem ser cursadas apos %d semestre(s)):\n", nivel, nivel);
        for (int i = 0; i < mapa->total; i++) {
            if (niveis[i] == nivel) {
                printf("  %s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
            }
        }
    }

    free(niveis);
    free(visitado);
}

/*
 * Funcao caminho_para_disciplina
 * Mostra um caminho de pre-requisitos ate uma disciplina especifica
 */
void caminho_para_disciplina(p_grafo g, MapaDisciplinas* mapa, const char* codigo) {
    int idx = buscar_indice_disciplina(mapa, codigo);
    if (idx == -1) {
        printf("Disciplina %s nao encontrada!\n", codigo);
        return;
    }

    printf("\n=== Caminho de Pre-Requisitos para %s ===\n", codigo);
    printf("%s - %s\n\n", mapa->disciplinas[idx].codigo, mapa->disciplinas[idx].nome);

    // Busca em profundidade a partir da disciplina
    int* pai = encontraCaminhos(g, idx);

    printf("Todas as disciplinas necessarias (diretas e indiretas):\n");
    int count = 0;
    for (int i = 0; i < g->n; i++) {
        if (pai[i] != -1 && i != idx) {
            printf("  %s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
            count++;
        }
    }

    if (count == 0) {
        printf("  (nao ha pre-requisitos)\n");
    } else {
        printf("\nTotal: %d disciplinas necessarias antes de %s\n", count, codigo);
    }

    free(pai);
}

/*
 * Funcao sugerir_ordem_otimizada
 * Sugere uma ordem de cursada que minimiza o tempo
 */
void sugerir_ordem_otimizada(p_grafo g, MapaDisciplinas* mapa) {
    printf("\n=== Sugestao de Ordem de Cursada Otimizada ===\n");
    printf("(Baseada em pre-requisitos - ordem topologica)\n\n");

    int* grau_entrada = calloc(mapa->total, sizeof(int));
    int* concluidas = calloc(mapa->total, sizeof(int));

    // Calcula grau de entrada (numero de pre-requisitos diretos)
    for (int i = 0; i < mapa->total; i++) {
        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i)) {
                grau_entrada[i]++;
            }
        }
    }

    int semestre = 1;
    int total_concluidas = 0;

    while (total_concluidas < mapa->total) {
        printf("Semestre %d:\n", semestre);
        int cursadas_neste_sem = 0;

        // Encontra disciplinas disponiveis
        for (int i = 0; i < mapa->total; i++) {
            if (concluidas[i]) continue;

            // Verifica se todos pre-requisitos foram concluidos
            int pode_cursar = 1;
            for (int j = 0; j < g->n; j++) {
                if (TemAresta(g, j, i) && !concluidas[j]) {
                    pode_cursar = 0;
                    break;
                }
            }

            if (pode_cursar) {
                printf("  %s - %s\n", mapa->disciplinas[i].codigo, mapa->disciplinas[i].nome);
                concluidas[i] = 1;
                cursadas_neste_sem++;
                total_concluidas++;
            }
        }

        if (cursadas_neste_sem == 0) {
            printf("  (nenhuma disciplina disponivel - possivel ciclo)\n");
            break;
        }

        printf("  Total: %d disciplinas\n\n", cursadas_neste_sem);
        semestre++;
    }

    printf("Tempo minimo estimado: %d semestres\n", semestre - 1);

    free(grau_entrada);
    free(concluidas);
}

int main(void) {
    // Carrega todas as disciplinas do CSV
    MapaDisciplinas* mapa = carregar_disciplinas("Disciplinas.csv");
    if (!mapa) {
        return 1;
    }

    // Imprime disciplinas carregadas
    imprimir_mapa_disciplinas(mapa);

    // Constroi grafo de pre-requisitos usando lista
    p_grafo g = construir_grafo_requisitos_lista("Disciplinas.csv", mapa);

    // Imprime pre-requisitos
    imprimir_prerequisitos_lista(g, mapa);

    // Organiza disciplinas por niveis
    organizar_por_niveis(g, mapa);

    // Mostra caminho de pre-requisitos para disciplinas especificas
    printf("\n\n=== TESTE 1: Pre-Requisitos de TCC ===\n");
    caminho_para_disciplina(g, mapa, "CIC047MAT3");

    printf("\n\n=== TESTE 2: Pre-Requisitos de Compiladores ===\n");
    caminho_para_disciplina(g, mapa, "CIC013MAT3");

    printf("\n\n=== TESTE 3: Pre-Requisitos de TCC ===\n");
    caminho_para_disciplina(g, mapa, "CIC047MAT3");

    // Sugere ordem otimizada de cursada
    printf("\n\n=== TESTE 4: Ordem Otimizada de Cursada ===\n");
    sugerir_ordem_otimizada(g, mapa);

    // Encontra componentes conexas
    printf("\n\n=== TESTE 5: Analise de Componentes ===\n");
    int* componentes = EncontraComponentes(g);
    int max_comp = 0;
    for (int i = 0; i < mapa->total; i++) {
        if (componentes[i] > max_comp) max_comp = componentes[i];
    }
    printf("Total de componentes conexas: %d\n", max_comp + 1);
    printf("(Um unico componente indica que todas as disciplinas estao relacionadas)\n");

    // Estatisticas do grafo
    printf("\n\n=== TESTE 6: Estatisticas do Grafo ===\n");
    int total_arestas = 0;
    int disciplinas_sem_prereq = 0;
    int disciplinas_sem_dependentes = 0;

    for (int i = 0; i < mapa->total; i++) {
        int prereqs = 0;
        int dependentes = 0;

        for (int j = 0; j < g->n; j++) {
            if (TemAresta(g, j, i)) prereqs++;
            if (TemAresta(g, i, j)) dependentes++;
        }

        total_arestas += dependentes;
        if (prereqs == 0) disciplinas_sem_prereq++;
        if (dependentes == 0) disciplinas_sem_dependentes++;
    }

    printf("Total de disciplinas: %d\n", mapa->total);
    printf("Total de relacoes de pre-requisito: %d\n", total_arestas);
    printf("Disciplinas sem pre-requisitos: %d\n", disciplinas_sem_prereq);
    printf("Disciplinas sem dependentes: %d\n", disciplinas_sem_dependentes);
    printf("Grau medio: %.2f\n", (float)(total_arestas * 2) / mapa->total);

    // Cleanup
    free(componentes);
    DestroiGrafo(g);
    liberar_mapa(mapa);

    printf("\n=== Programa Finalizado ===\n");
    return 0;
}
