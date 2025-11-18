# Projeto: Grafo de Pré-Requisitos de Disciplinas

Este projeto implementa um sistema de análise de pré-requisitos de disciplinas usando grafos, com duas implementações diferentes: **matriz de adjacência** e **lista de adjacência**.

## Estrutura do Projeto

```
graph/
├── Disciplinas.csv              # Dados das disciplinas e pré-requisitos
├── requisitos_comum.h           # Cabeçalho com estruturas comuns
├── requisitos_comum.c           # Funções compartilhadas (leitura CSV)
├── requisitos_matriz.c          # Implementação usando matriz de adjacência
├── requisitos_lista.c           # Implementação usando lista de adjacência
├── Makefile                     # Compilação automatizada
├── matrice/                     # Implementação de grafo com matriz
│   ├── graph.h
│   └── graph.c
└── list/                        # Implementação de grafo com lista
    ├── graph.h
    └── graph.c
```

## Funcionalidades

### Programa com Matriz (`requisitos_matriz`)

1. **Carregamento de disciplinas** do arquivo CSV
2. **Construção do grafo direcionado** de pré-requisitos
3. **Listagem de pré-requisitos** por disciplina
4. **Listagem de disciplinas dependentes** (que requerem cada disciplina)
5. **Verificação de ordem válida** de cursada
6. **Disciplinas disponíveis** dado um conjunto de disciplinas concluídas
7. **Componentes conexas** do grafo
8. **Busca em largura** para encontrar caminhos
9. **Disciplinas mais importantes** (maior número de dependentes)

### Programa com Lista (`requisitos_lista`)

1. **Carregamento de disciplinas** do arquivo CSV
2. **Construção do grafo direcionado** de pré-requisitos
3. **Organização por níveis** de pré-requisitos
4. **Caminho de pré-requisitos** para disciplinas específicas
5. **Sugestão de ordem otimizada** de cursada (ordenação topológica)
6. **Análise de componentes** conexas
7. **Estatísticas completas** do grafo

## Compilação

### Compilar ambos os programas:

```bash
make
```

### Compilar apenas o programa com matriz:

```bash
make requisitos_matriz
```

### Compilar apenas o programa com lista:

```bash
make requisitos_lista
```

### Limpar arquivos compilados:

```bash
make clean
```

## Execução

### Executar programa com matriz:

```bash
make run-matriz
# ou
./requisitos_matriz
```

### Executar programa com lista:

```bash
make run-lista
# ou
./requisitos_lista
```

### Executar ambos:

```bash
make run-all
```

## Formato do Arquivo CSV

O arquivo `Disciplinas.csv` deve seguir o formato:

```csv
Ano,Semestre,Disciplinas,Pré-Requisito
1,1,CIC002MAT3 Algoritmos I,
2,1,CIC018MAT3 Estrutura de Dados I,Pré-Requisito: CIC002MAT3 Algoritmos I
```

- **Ano**: Ano do curso (1-4)
- **Semestre**: Semestre dentro do ano (1-2)
- **Disciplinas**: Código e nome completo da disciplina
- **Pré-Requisito**: Campo opcional com código da disciplina pré-requisito

## Estrutura de Dados

### Grafo Direcionado

- **Vértices**: Cada disciplina é um vértice
- **Arestas**: Aresta de A para B significa "A é pré-requisito de B"
- **Direção**: O grafo é direcionado (pré-requisito → disciplina)

### MapaDisciplinas

Estrutura que mapeia códigos de disciplinas para índices no grafo:

```c
typedef struct {
    char codigo[MAX_CODIGO];    // Ex: "CIC002MAT3"
    char nome[MAX_NOME];        // Nome completo
    int ano;                    // Ano do curso
    int semestre;               // Semestre
} Disciplina;
```

## Algoritmos Utilizados

### Programa com Matriz

- **Busca em Profundidade (DFS)** - Encontrar componentes conexas
- **Busca em Largura (BFS)** - Calcular distâncias entre disciplinas
- **Verificação de ordem** - Validar sequência de cursada

### Programa com Lista

- **DFS Recursiva** - Calcular níveis de pré-requisitos
- **Ordenação Topológica** - Sugerir ordem de cursada
- **Cálculo de grau** - Estatísticas do grafo

## Exemplos de Uso

### Encontrar pré-requisitos de uma disciplina

O programa lista todos os pré-requisitos diretos e indiretos necessários.

### Verificar disciplinas disponíveis

Dado um conjunto de disciplinas já cursadas, o programa lista quais podem ser cursadas no próximo semestre.

### Otimizar ordem de cursada

O programa sugere uma ordem que minimiza o número de semestres necessários para concluir o curso.

### Analisar dependências

Identifica disciplinas "gargalo" que são pré-requisito para muitas outras.

## Diferenças entre Implementações

| Aspecto              | Matriz        | Lista           |
| -------------------- | ------------- | --------------- |
| **Espaço**           | O(n²)         | O(n + m)        |
| **Verificar aresta** | O(1)          | O(grau)         |
| **Listar vizinhos**  | O(n)          | O(grau)         |
| **Inserir aresta**   | O(1)          | O(1)            |
| **Melhor para**      | Grafos densos | Grafos esparsos |

## Testes Implementados

### Matriz

1. Disciplinas do 1º ano (sem pré-requisitos)
2. Disciplinas disponíveis após 1º ano
3. Componentes conexas
4. Busca em largura a partir de Algoritmos I
5. Disciplinas mais importantes

### Lista

1. Pré-requisitos do TCC
2. Pré-requisitos de Compiladores
3. Pré-requisitos de Banco de Dados II
4. Ordem otimizada de cursada
5. Análise de componentes
6. Estatísticas do grafo

## Observações

- O grafo de pré-requisitos do curso de Ciência da Computação é **esparso** (poucas arestas em relação ao número de vértices)
- A implementação com **lista de adjacência** é mais eficiente em espaço para este caso
- O grafo é **acíclico** (DAG - Directed Acyclic Graph), pois não pode haver ciclos em pré-requisitos
- Algumas disciplinas não têm pré-requisitos (1º semestre) e outras não são pré-requisito de nenhuma (disciplinas finais)

## Autor

Projeto desenvolvido para a disciplina de Estrutura de Dados II.
