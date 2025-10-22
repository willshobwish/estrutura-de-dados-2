#ifndef GRAPH
#define GRAPH

typedef struct {
    int **adj;
    int n;
}Grafo;

typedef Grafo *p_grafo;
p_grafo CriarGrafo(int n);
void DestroiGrafo(p_grafo g);
void InsereAresta(p_grafo g, int u, int v);
void RemoveAresta(p_grafo g, int u, int v);
int TemAresta(p_grafo g, int u, int v);
void ImprimeArestas(p_grafo g);
int Grau(p_grafo g, int u);
int MaisPopular(p_grafo g);
void ImprimeRecomendacoes(p_grafo g, int u);
#endif