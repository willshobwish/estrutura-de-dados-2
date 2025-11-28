# Estruturas de Dados 2 (ED2)

Repositório contendo implementações de estruturas de dados avançadas desenvolvidas durante a disciplina de Estrutura de Dados 2.

## Conteúdo

### Árvores

#### Árvore B (`b_tree/` e `b_tree_project/`)

Implementação completa de Árvore B com aplicação prática em processamento de imagens.

**Projeto Destaque** (`b_tree_project/`):

- Carrega imagens PNG
- Embaralha pixels aleatoriamente
- Armazena pixels em Árvore B usando índices como chaves
- Reconstrói a imagem recuperando dados da árvore
- Demonstra eficiência de busca em estruturas balanceadas

**Estruturas Principais**:

```c
typedef struct No {
    int n;                      // Número de chaves no nó
    int folha;                  // 1 se é folha, 0 caso contrário
    int chave[MAX];            // Array de chaves
    PixelData pixel[MAX];      // Dados dos pixels
    struct No *filho[MAX + 1]; // Ponteiros para filhos
} NoArvB, *ArvoreB;
```

**Funcionalidades**:

- Inserção de chaves
- Busca eficiente O(log n)
- Manipulação de imagens (usando stb_image)
- Algoritmo Fisher-Yates para embaralhamento

#### Árvore Básica (`arvore/`)

Implementação fundamental de Árvore B para fins didáticos.

### Árvores de Busca Digital

#### Trie (`trie/`)

Árvore de prefixos para busca eficiente de strings e padrões.

**Características**:

- Busca de padrões em O(m) onde m é o comprimento da chave
- Armazena chaves de 32 bits
- Diferencia nós internos de folhas
- Ideal para dicionários e autocompletar

```c
typedef struct No {
    unsigned chave;      // Significativo apenas em folhas
    int bit;            // Posição do bit testado
    int is_leaf;        // Flag de folha
    struct No *esq, *dir;
} No;
```

#### Radix Tree (`radix/`)

Árvore de busca digital compacta, otimização da Trie.

**Vantagens**:

- Reduz espaço ao comprimir caminhos
- Busca eficiente bit a bit
- Menor uso de memória que Trie padrão

#### Patricia Trie (`patricia_trie/`)

Practical Algorithm to Retrieve Information Coded in Alphanumeric.

**Otimizações**:

- Árvore binária compacta
- Busca e inserção recursivas
- Testa bits específicos para decisões de navegação
- Configurável: `bits_na_chave` define tamanho das chaves

### Grafos

Implementações completas de grafos com duas representações:

- **Matriz de Adjacência** (`graph/matrice/`)
- **Lista de Adjacência** (`graph/list/`)

#### Estruturas

**Matriz de Adjacência**:

```c
typedef struct {
    int** adj;  // Matriz n×n
    int n;      // Número de vértices
} Grafo;
```

**Lista de Adjacência**:

```c
typedef struct No {
    int v;          // Vértice destino
    struct No* prox;
    int peso;       // Peso da aresta
} No;

typedef struct {
    p_no* adjacencia;  // Array de listas
    int n;            // Número de vértices
} Grafo;
```

#### Algoritmos Implementados

**Busca e Travessia**:

- Busca em Profundidade (DFS) - recursiva e iterativa
- Busca em Largura (BFS)
- Encontrar componentes conexas
- Verificar existência de caminhos
- Encontrar caminhos entre vértices

**Algoritmos Avançados**:

- **Dijkstra**: Caminhos mínimos (grafos ponderados)
- **Prim**: Árvore Geradora Mínima (MST)
- **Ordenação Topológica**: Para DAGs

**Estruturas Auxiliares**:

- Pilha (DFS iterativa)
- Fila (BFS)
- Fila de Prioridade (Dijkstra/Prim)

#### Projeto: Grafo de Pré-Requisitos (`graph/project/`)

Sistema de análise de dependências de disciplinas usando grafos direcionados.

**Funcionalidades**:

_Implementação com Matriz_:

- Lista pré-requisitos e disciplinas dependentes
- Verifica ordem válida de cursada
- Disciplinas disponíveis após conclusões
- Identifica disciplinas com mais pré-requisitos

_Implementação com Lista_:

- Organização por níveis de pré-requisitos
- Caminho completo de pré-requisitos
- Sugestão de ordem otimizada (ordenação topológica)
- Estatísticas completas do grafo

**Entrada**: `Disciplinas.csv`

```csv
Ano,Semestre,Codigo,Disciplinas,Codigo-Pre-Requisito,Pre-Requisito
1,1,CIC022MAT3,Fundamentos de Matematica
1,2,CIC007MAT3,Calculo Diferencial e Integral I
2,1,CIC018MAT3,Estrutura de Dados I,CIC002MAT3,Algoritmos...
```

**Como funciona**:

- Grafo Direcionado Acíclico (DAG)
- Vértices = Disciplinas
- Aresta A→B = "A é pré-requisito de B"
- Análise de dependências usando DFS/BFS

## Compilação e Execução

Cada projeto possui seu próprio `Makefile`:

```bash
# Navegar até o projeto desejado
cd b_tree_project/    # ou graph/project/, trie/, etc.

# Compilar
make

# Executar
make run

# Limpar binários
make clean
```

### Compilação Manual

```bash
# Árvore B com imagens
gcc -o image_btree main.c b_tree.c pixel_data.c random_array_generator.c -lm

# Grafos
gcc -Wall -Wextra -g graph.c main.c -o main

# Trie/Radix/Patricia
gcc -o trie main.c trie.c
```

## Estrutura do Repositório

```
ed2/
├── arvore/              # Árvore B básica
├── b_tree/              # Árvore B completa
├── b_tree_project/      # Projeto com processamento de imagens
├── graph/
│   ├── doc/            # Documentação LaTeX
│   ├── list/           # Implementação com lista de adjacência
│   ├── matrice/        # Implementação com matriz de adjacência
│   └── project/        # Sistema de pré-requisitos
├── trie/               # Árvore Trie
├── radix/              # Radix Tree
├── patricia_trie/      # Patricia Trie
└── docs/               # Documentação geral em LaTeX
```

## Conceitos Abordados

### Árvores

- Balanceamento automático
- Operações em O(log n)
- Trade-offs: tempo vs espaço
- Aplicações em bancos de dados e sistemas de arquivos

### Busca Digital

- Representação compacta de conjuntos
- Busca por prefixo
- Análise bit a bit
- Otimização de espaço

### Grafos

- Representações: matriz vs lista
- Algoritmos de travessia
- Caminhos mínimos
- Árvores geradoras
- Aplicações em redes e dependências

### Complexidade

| Estrutura      | Busca    | Inserção | Remoção  | Espaço       |
| -------------- | -------- | -------- | -------- | ------------ |
| Árvore B       | O(log n) | O(log n) | O(log n) | O(n)         |
| Trie           | O(m)     | O(m)     | O(m)     | O(n×m)       |
| Radix          | O(m)     | O(m)     | O(m)     | O(n)         |
| Patricia       | O(m)     | O(m)     | O(m)     | O(n)         |
| Grafo (Lista)  | O(V+E)   | O(1)     | O(E)     | O(V+E)       |
| Grafo (Matriz) | O(1)     | O(1)     | O(1)     | O(V²)        |
| Dijkstra       | -        | -        | -        | O((V+E)logV) |
| Prim           | -        | -        | -        | O((V+E)logV) |

_m = comprimento da chave, n = número de elementos, V = vértices, E = arestas_

## Tecnologias

- **Linguagem**: C
- **Compilador**: GCC
- **Build System**: Make
- **Bibliotecas externas**:
  - stb_image.h (carregamento de imagens)
  - stb_image_write.h (salvamento de imagens)
- **Documentação**: LaTeX

## Documentação Adicional

- `graph/PRIM_README.md`: Detalhes sobre Algoritmo de Prim
- `graph/project/README.md`: Sistema de pré-requisitos
- `b_tree_project/readme.md`: Projeto de processamento de imagens
- `docs/`: Documentação em LaTeX com teoria e implementação

## Aplicações Práticas

### Árvores B

- Bancos de dados (índices)
- Sistemas de arquivos (ext4, NTFS)
- Cache de memória

### Tries

- Autocompletar
- Correção ortográfica
- Roteamento IP
- Compressão de dados

### Grafos

- Redes sociais (recomendações)
- GPS e mapas (caminhos mínimos)
- Redes de computadores (roteamento)
- Planejamento de projetos (dependências)
- Compiladores (análise de dependências)

## Contribuições

Este é um repositório acadêmico. Sugestões e melhorias são bem-vindas através de issues e pull requests.

## Licença

Projeto acadêmico desenvolvido para fins educacionais.

## Destaques do Repositório

- Múltiplas implementações de cada estrutura
- Código bem documentado com comentários em português
- Exemplos práticos e aplicações reais
- Testes e validações incluídos
- Makefiles para fácil compilação
- Documentação técnica em LaTeX
- Comparações entre diferentes abordagens

## Análise Comparativa

### Quando usar cada estrutura?

**Árvore B**:

- Muitos dados
- Acesso em disco
- Necessidade de ordenação
- Evitar em estruturas pequenas (overhead)

**Trie/Radix/Patricia**:

- Busca por prefixo
- Conjunto de strings
- Autocompletar
- Evitar com chaves muito variadas (espaço)

**Grafo (Lista)**:

- Grafos esparsos (E << V²)
- Iteração por vizinhos
- Evitar se há verificação frequente de arestas

**Grafo (Matriz)**:

- Grafos densos
- Verificação rápida de arestas
- Evitar com muitos vértices e poucas arestas

---

**Disciplina**: Estrutura de Dados 2  
**Instituição**: Universidade Federal de Ouro Preto (UFOP)
