#ifndef REQUISITOS_COMUM_H
#define REQUISITOS_COMUM_H

#define MAX_DISCIPLINAS 100
#define MAX_LINHA 500
#define MAX_NOME 100
#define MAX_CODIGO 20

// Estrutura para armazenar informações de uma disciplina
typedef struct {
    char codigo[MAX_CODIGO];
    char nome[MAX_NOME];
    int ano;
    int semestre;
} Disciplina;

// Estrutura para mapear códigos de disciplinas para índices
typedef struct {
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int total;
} MapaDisciplinas;

// Funções comuns para ambas implementações
MapaDisciplinas* carregar_disciplinas(const char* arquivo);
int buscar_indice_disciplina(MapaDisciplinas* mapa, const char* codigo);
void extrair_codigo(const char* texto, char* codigo);
void imprimir_mapa_disciplinas(MapaDisciplinas* mapa);
void liberar_mapa(MapaDisciplinas* mapa);

#endif
