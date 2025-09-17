# Projeto bimestral da disciplina de estrutura de dados 2

Este projeto implementa uma estrutura de dados B-Tree para armazenar e recuperar dados de pixels de uma imagem, demonstrando conceitos de estruturas de dados aplicados ao processamento de imagens.

## Descrição

O programa carrega uma imagem PNG, extrai os dados de cada pixel, embaralha aleatoriamente os pixels, armazena-os em uma B-Tree e depois reconstrói a imagem original recuperando os pixels da árvore. É uma demonstração prática de como estruturas de dados podem ser utilizadas para organizar e acessar informações de forma eficiente.

## Estrutura do Projeto

```
├── main.c                      # Programa principal
├── b_tree.c                    # Implementação da B-Tree
├── b_tree.h                    # Cabeçalho da B-Tree
├── pixel_data.c                # Funções para manipulação de pixels
├── pixel_data.h                # Estrutura e funções de pixels
├── random_array_generator.c    # Gerador de arrays aleatórios
├── random_array_generator.h    # Cabeçalho do gerador
├── stb_image.h                 # Biblioteca para carregar imagens (externa)
└── stb_image_write.h          # Biblioteca para salvar imagens (externa)
```

## Funcionalidades

- **Carregamento de Imagem**: Carrega uma imagem PNG usando a biblioteca stb_image
- **Extração de Pixels**: Converte a imagem em um array de estruturas PixelData
- **Embaralhamento**: Randomiza a ordem dos pixels usando o algoritmo Fisher-Yates
- **Armazenamento em B-Tree**: Insere cada pixel na árvore usando o índice como chave
- **Recuperação**: Busca todos os pixels na árvore para reconstruir a imagem
- **Reconstrução**: Gera uma nova imagem PNG com os dados recuperados

## Estruturas de Dados

### PixelData
```c
typedef struct {
    unsigned int index;    // Índice do pixel na imagem original
    unsigned int height;   // Altura da imagem
    unsigned int width;    // Largura da imagem
    unsigned char R;       // Componente vermelha (0-255)
    unsigned char G;       // Componente verde (0-255)
    unsigned char B;       // Componente azul (0-255)
} PixelData;
```

### B-Tree Node
```c
typedef struct No {
    int n;                      // Número de chaves no nó
    int folha;                  // 1 se é folha, 0 caso contrário
    int chave[MAX];            // Array de chaves (índices dos pixels)
    PixelData pixel[MAX];      // Array de dados dos pixels
    struct No *filho[MAX + 1]; // Array de ponteiros para filhos
} NoArvB, *ArvoreB;
```

## Compilação

### Pré-requisitos
- Compilador C (GCC recomendado)
- Bibliotecas stb_image.h e stb_image_write.h

### Comandos de Compilação

Usando apenas o terminal

```bash
# Compilação básica
gcc -o image_btree main.c b_tree.c pixel_data.c random_array_generator.c -lm

# Com flags de otimização e debug
gcc -Wall -Wextra -O2 -g -o image_btree main.c b_tree.c pixel_data.c random_array_generator.c -lm
```

Ou usando Makefile

```bash
make run
```

## Execução

1. Coloque uma imagem PNG no diretório do projeto (já existe o uma imagem chamada `Labrador Retriever.png`)
2. Execute o programa:
```bash
./image_btree
```
3. O programa gerará uma imagem reconstruída chamada `reconstructed.png`

## Configurações

### Parâmetros da B-Tree
- `MAX`: Define o grau máximo da B-Tree (padrão: 1000)
- Grau mínimo `t = (MAX + 1) / 2`
- Cada nó pode ter entre `t-1` e `2t-1` chaves

### Formato de Imagem
- Suporta imagens PNG
- Força conversão para RGB (3 canais)
- Sem suporte a transparência

## Exemplo de Uso

```c
// Carrega imagem
unsigned char *img = stbi_load("input.png", &width, &height, &channels, 3);

// Cria array de pixels
PixelData *pixels = malloc(sizeof(PixelData) * pixel_count);

// Embaralha pixels
shuffle_pixels(pixels, pixel_count);

// Constrói B-Tree
ArvoreB root = AllocateNode();
for (size_t i = 0; i < pixel_count; i++) {
    root = InsereArvoreB(root, pixels[i].index, pixels[i]);
}

// Recupera e reconstrói imagem
for (size_t i = 0; i < pixel_count; i++) {
    PixelData recovered = BuscaArvoreB(root, original_indices[i]);
    // Processa pixel recuperado...
}
```

## Tratamento de Erros

O programa inclui verificações para:
- Falha no carregamento da imagem
- Falha na alocação de memória
- Falha na criação de nós da árvore
- Pixels não encontrados na busca
- Falha na gravação da imagem

## Notas de Implementação

- A B-Tree usa o índice do pixel como chave de ordenação
- O embaralhamento usa o algoritmo Fisher-Yates para distribuição uniforme
- A implementação segue os algoritmos clássicos de B-Tree do Cormen
- Gerenciamento manual de memória com verificações de erro