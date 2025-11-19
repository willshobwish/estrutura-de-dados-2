#include "requisitos_comum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Funcao extrair_codigo
 * Extrai o codigo da disciplina (primeiros caracteres ate o espaco)
 */
void extrair_codigo(const char* texto, char* codigo) {
    int i = 0;
    // Copia caracteres ate encontrar espaco ou fim da string
    while (texto[i] != ' ' && texto[i] != '\0' && i < MAX_CODIGO - 1) {
        codigo[i] = texto[i];
        i++;
    }
    codigo[i] = '\0';
}

/*
 * Funcao buscar_indice_disciplina
 * Busca o índice de uma disciplina pelo codigo
 * Retorna o índice se encontrado, -1 caso contrario
 */
int buscar_indice_disciplina(MapaDisciplinas* mapa, const char* codigo) {
    for (int i = 0; i < mapa->total; i++) {
        if (strcmp(mapa->disciplinas[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Funcao carregar_disciplinas
 * Lê o arquivo CSV e carrega todas as disciplinas únicas
 * Retorna um mapa com todas as disciplinas e seus índices
 */
MapaDisciplinas* carregar_disciplinas(const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return NULL;
    }

    MapaDisciplinas* mapa = malloc(sizeof(MapaDisciplinas));
    mapa->total = 0;

    char linha[MAX_LINHA];
    // Pula cabecalho
    fgets(linha, sizeof(linha), fp);

    while (fgets(linha, sizeof(linha), fp)) {
        int ano, semestre;
        char codigo[MAX_CODIGO];
        char disciplina[MAX_NOME];

        // Remove newline
        linha[strcspn(linha, "\n")] = 0;

        // Parsing da linha CSV: Ano,Semestre,Codigo,Disciplinas,Codigo-Pre-Requisito,Pre-Requisito
        char* token = strtok(linha, ",");
        if (!token) continue;
        ano = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        semestre = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(codigo, token, MAX_CODIGO - 1);
        codigo[MAX_CODIGO - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(disciplina, token, MAX_NOME - 1);
        disciplina[MAX_NOME - 1] = '\0';

        // Verifica se a disciplina ja foi adicionada
        if (buscar_indice_disciplina(mapa, codigo) == -1) {
            strcpy(mapa->disciplinas[mapa->total].codigo, codigo);
            strncpy(mapa->disciplinas[mapa->total].nome, disciplina, MAX_NOME - 1);
            mapa->disciplinas[mapa->total].nome[MAX_NOME - 1] = '\0';
            mapa->disciplinas[mapa->total].ano = ano;
            mapa->disciplinas[mapa->total].semestre = semestre;
            mapa->total++;

            if (mapa->total >= MAX_DISCIPLINAS) {
                printf("AVISO: Limite de disciplinas atingido!\n");
                break;
            }
        }
    }

    fclose(fp);
    return mapa;
}

/*
 * Funcao imprimir_mapa_disciplinas
 * Imprime todas as disciplinas carregadas
 */
void imprimir_mapa_disciplinas(MapaDisciplinas* mapa) {
    printf("\nDisciplinas Carregadas\n");
    printf("Total: %d disciplinas\n\n", mapa->total);
    for (int i = 0; i < mapa->total; i++) {
        printf("[%2d] %s - %s (Ano %d, Sem %d)\n",
               i,
               mapa->disciplinas[i].codigo,
               mapa->disciplinas[i].nome,
               mapa->disciplinas[i].ano,
               mapa->disciplinas[i].semestre);
    }
}

/*
 * Funcao liberar_mapa
 * Libera memoria do mapa de disciplinas
 */
void liberar_mapa(MapaDisciplinas* mapa) {
    free(mapa);
}
