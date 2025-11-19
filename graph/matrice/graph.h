#ifndef GRAPH
#define GRAPH

typedef struct {
    int** adj;
    int n;
} Grafo;

typedef Grafo* p_grafo;

// Estrutura de pilha para busca em profundidade iterativa
typedef struct {
    int* dados;
    int topo;
    int capacidade;
} Pilha;

typedef Pilha* p_pilha;

// Estrutura de fila para busca em largura (BFS)
typedef struct {
    int* dados;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
} Fila;

typedef Fila* p_fila;

// Funcoes da pilha
p_pilha criar_pilha();
void destroi_pilha(p_pilha p);
void empilhar(p_pilha p, int valor);
int desempilhar(p_pilha p);
int pilha_vazia(p_pilha p);

// Funcoes da fila
p_fila criar_fila();
void destroi_fila(p_fila f);
void enfileira(p_fila f, int valor);
int desenfileira(p_fila f);
int fila_vazia(p_fila f);

// Funcoes do grafo
p_grafo CriarGrafo(int n);
void DestroiGrafo(p_grafo g);
void InsereAresta(p_grafo g, int u, int v);
void RemoveAresta(p_grafo g, int u, int v);
int TemAresta(p_grafo g, int u, int v);
void ImprimeArestas(p_grafo g);
int Grau(p_grafo g, int u);
int MaisPopular(p_grafo g);
void ImprimeRecomendacoes(p_grafo g, int u);
p_grafo LeGrafo();
int ExisteCaminho(p_grafo g, int s, int t);
int BuscaRec(p_grafo g, int* visitado, int v, int t);
int* EncontraComponentes(p_grafo g);
void VisitaRec(p_grafo g, int* componentes, int comp, int v);
int* encontraCaminhos(p_grafo g, int s);
void buscaEmProfundidade(p_grafo g, int* pai, int p, int v);
int* busca_em_profundidade(p_grafo g, int s);
int* busca_em_largura(p_grafo g, int s);

// Algoritmo de Prim (Arvore Geradora Minima)
int* prim(p_grafo g, int s);
#endif