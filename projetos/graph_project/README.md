# Grafo de Pré-Requisitos de Disciplinas

Sistema de análise de pré-requisitos usando grafos direcionados com duas implementações: **matriz de adjacência** e **lista de adjacência**.

## Estrutura

```
project/
├── Disciplinas.csv          # Dados das disciplinas
├── requisitos_comum.h/c     # Funções compartilhadas
├── requisitos_matriz.c      # Implementação com matriz
├── requisitos_lista.c       # Implementação com lista
├── Makefile
matrice/                  # Biblioteca de grafos (matriz de adjacência)
├── graph.h
├── graph.c
└── main.c               # Possui códigos para execução das funções implementadas
list/                     # Biblioteca de grafos (lista de adjacência)
├── graph.h
├── graph.c
└── main.c               # Possui códigos para execução das funções implementadas
```

## Funcionalidades

### Matriz de Adjacência (`requisitos_matriz`)

- Listagem de pré-requisitos e disciplinas dependentes
- Verificação de ordem válida de cursada
- Disciplinas disponíveis após conclusão de um conjunto
- Busca em largura (BFS) e componentes conexas
- Identificação de disciplinas com mais pré-requisitos

### Lista de Adjacência (`requisitos_lista`)

- Organização por níveis de pré-requisitos
- Caminho completo de pré-requisitos para qualquer disciplina
- Sugestão de ordem otimizada (ordenação topológica)
- Estatísticas completas do grafo

## Como a teoria dos grafos foi utilizado no projeto

A teoria dos grafos foi utilizado para construir a dependencia entre as disciplinas (e.g., Makefile) facilitando a visualização das disciplinas necessárias, organização em níveis, sugestões e entre outras funcionalidades e teorias que são aplicados em grafos.

## Compilação e Execução

```bash
# Compilar tudo
make

# Compilar individualmente
make requisitos_matriz
make requisitos_lista

# Executar
./requisitos_matriz
./requisitos_lista

# Ou usar atalhos
make run-matriz
make run-lista
make run-all

# Limpar (funciona apenas no Linux por causa do comando rm)
make clean
```

## Formato do CSV

```csv
Ano,Semestre,Codigo,Disciplinas,Codigo-Pre-Requisito,Pre-Requisito
1,1,CIC022MAT3,Fundamentos de Matematica
1,2,CIC007MAT3,Calculo Diferencial e Integral I
2,1,CIC018MAT3,Estrutura de Dados I,CIC002MAT3,Algoritmos e Tecnicas de Programacao I
```

- Disciplinas sem pré-requisitos: deixar últimas colunas vazias
- Múltiplos pré-requisitos: uma linha por pré-requisito

## Estrutura do Grafo

- **Vértices**: Cada um representa uma disciplina única
- **Arestas direcionadas**: A => B significa "A é pré-requisito de B"
- **Tipo**: DAG (Directed Acyclic Graph) - sem ciclos

## Algoritmos

- **Busca em Profundidade (DFS)**: Componentes conexas, níveis
- **Busca em Largura (BFS)**: Distâncias entre disciplinas
- **Ordenação Topológica**: Ordem otimizada de cursada
- **Análise de grau**: Pré-requisitos diretos
