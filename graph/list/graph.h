#ifndef GRAPH
#define GRAPH

typedef struct No {
    int v;
    struct No* prox;
    int peso;
} No;

typedef No* p_no;

typedef struct {
    p_no* adjacencia;
    int n;
} Grafo;

typedef struct {
    int prioridade;
    int vertice;
} Item;
typedef struct {
    Item* v;
    int* indice;
    int n, tamanho;
} FP;
typedef FP* p_fp;

typedef Grafo* p_grafo;
p_grafo CriarGrafo(int n);
void DestroiGrafo(p_grafo g);
void InsereAresta(p_grafo g, int u, int v);
void InsereArestaPonderada(p_grafo g, int u, int v, int peso);
void RemoveAresta(p_grafo g, int u, int v);
int TemAresta(p_grafo g, int u, int v);
p_grafo LeGrafo();
void ImprimeArestas(p_grafo g);
int Grau(p_grafo g, int u);
int MaisPopular(p_grafo g);
void ImprimeRecomendacoes(p_grafo g, int u);
int* EncontraComponentes(p_grafo g);
void VisitaRec(p_grafo g, int* componentes, int comp, int v);
int* encontraCaminhos(p_grafo g, int s);
void buscaEmProfundidade(p_grafo g, int* pai, int p, int v);
void ordenacao_topologica(p_grafo g);
void visita_rec(p_grafo g, int* visitado, int v);

// Funcoes da fila de prioridade (heap minimo)
p_fp criar_fprio(int tamanho);
void destroi_fprio(p_fp h);
void insere(p_fp h, int vertice, int prioridade);
int extrai_minimo(p_fp h);
int vazia(p_fp h);
int prioridade(p_fp h, int vertice);
void diminuiprioridade(p_fp h, int vertice, int nova_prioridade);

// Algoritmo de Dijkstra
int* dijkstra(p_grafo g, int s);

// Algoritmo de Prim (Arvore Geradora Minima)
int* prim(p_grafo g, int s);
#endif