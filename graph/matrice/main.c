#include "graph.h"
#include <stdio.h>

int main(void){
    p_grafo g = CriarGrafo(2);
    InsereAresta(g,0,0);
    InsereAresta(g,1,1);
    // printf("%d\n",TemAresta(g,1,1));
    // printf("%d\n",TemAresta(g,0,0));
    // printf("%d\n",TemAresta(g,0,1));
    ImprimeArestas(g);
    return 0;
}