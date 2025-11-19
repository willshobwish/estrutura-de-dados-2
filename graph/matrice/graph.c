#include "graph.h"  // Inclui o cabeçalho com a definição da estrutura 'Grafo' e as funções declaradas

#include <limits.h>  // Inclui constantes como INT_MAX
#include <stdio.h>   // Inclui funções de entrada/saída, como printf e scanf
#include <stdlib.h>  // Inclui funções de alocação e liberação de memória (malloc, free)

// Funções de pilha (utilizados em busca em profundidade (DFS))
/*
 * Funcao criar_pilha
 * Cria e inicializa uma pilha dinamica para armazenar inteiros
 * Capacidade inicial de 100 elementos (pode ser expandida)
 */
p_pilha criar_pilha() {
    p_pilha p = malloc(sizeof(Pilha));
    p->capacidade = 100;
    p->dados = malloc(p->capacidade * sizeof(int));
    p->topo = -1;  // Pilha vazia tem topo -1
    return p;
}

/*
 * Funcao destroi_pilha
 * Libera toda a memoria alocada pela pilha
 */
void destroi_pilha(p_pilha p) {
    free(p->dados);
    free(p);
}

/*
 * Funcao empilhar
 * Insere um valor no topo da pilha
 * Expande a capacidade se necessario
 */
void empilhar(p_pilha p, int valor) {
    // Se a pilha estiver cheia, dobra a capacidade
    if (p->topo == p->capacidade - 1) {
        p->capacidade *= 2;
        p->dados = realloc(p->dados, p->capacidade * sizeof(int));
    }
    // Incrementa o topo e insere o valor
    p->topo++;
    p->dados[p->topo] = valor;
}

/*
 * Funcao desempilhar
 * Remove e retorna o valor do topo da pilha
 * Retorna -1 se a pilha estiver vazia (cuidado: pode ser um valor valido)
 */
int desempilhar(p_pilha p) {
    if (p->topo == -1) {
        return -1;  // Pilha vazia
    }
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}

/*
 * Funcao pilha_vazia
 * Verifica se a pilha esta vazia
 * Retorna 1 se vazia, 0 caso contrario
 */
int pilha_vazia(p_pilha p) {
    return p->topo == -1;
}

// ========== FUNCOES DA FILA ==========

/*
 * Funcao criar_fila
 * Cria e inicializa uma fila circular dinamica para armazenar inteiros
 * Capacidade inicial de 100 elementos (pode ser expandida)
 */
p_fila criar_fila() {
    p_fila f = malloc(sizeof(Fila));
    f->capacidade = 100;
    f->dados = malloc(f->capacidade * sizeof(int));
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

/*
 * Funcao destroi_fila
 * Libera toda a memoria alocada pela fila
 */
void destroi_fila(p_fila f) {
    free(f->dados);
    free(f);
}

/*
 * Funcao enfileira
 * Insere um valor no final da fila
 * Expande a capacidade se necessario
 */
void enfileira(p_fila f, int valor) {
    // Se a fila estiver cheia, dobra a capacidade
    if (f->tamanho == f->capacidade) {
        int nova_capacidade = f->capacidade * 2;
        int* novos_dados = malloc(nova_capacidade * sizeof(int));

        // Copia os elementos para o novo array
        for (int i = 0; i < f->tamanho; i++) {
            novos_dados[i] = f->dados[(f->inicio + i) % f->capacidade];
        }

        free(f->dados);
        f->dados = novos_dados;
        f->inicio = 0;
        f->fim = f->tamanho;
        f->capacidade = nova_capacidade;
    }

    // Insere o valor no final da fila
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

/*
 * Funcao desenfileira
 * Remove e retorna o valor do inicio da fila
 * Retorna -1 se a fila estiver vazia (cuidado: pode ser um valor valido)
 */
int desenfileira(p_fila f) {
    if (f->tamanho == 0) {
        return -1;  // Fila vazia
    }

    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}

/*
 * Funcao fila_vazia
 * Verifica se a fila esta vazia
 * Retorna 1 se vazia, 0 caso contrario
 */
int fila_vazia(p_fila f) {
    return f->tamanho == 0;
}

// Funções de grafo
// Função que cria um grafo com 'n' vértices
p_grafo CriarGrafo(int n) {
    int i, j;
    p_grafo g = malloc(sizeof(Grafo));  // Aloca memória para a estrutura principal do grafo
    g->n = n;                           // Define o número de vértices
    g->adj = malloc(n * sizeof(int*));  // Aloca memória para o vetor de ponteiros das listas de adjacência (matriz)

    for (i = 0; i < n; i++) {
        g->adj[i] = malloc(n * sizeof(int));  // Aloca memória para cada linha da matriz de adjacência
    }

    // Inicializa a matriz de adjacência com zeros (sem arestas)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            g->adj[i][j] = 0;  // 0 indica ausência de aresta
        }
    }

    return g;  // Retorna o ponteiro para o grafo criado
}

// Função que libera toda a memória usada pelo grafo
void DestroiGrafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++) {
        free(g->adj[i]);  // Libera cada linha da matriz
    }
    free(g->adj);  // Libera o vetor de ponteiros
    free(g);       // Libera a estrutura principal do grafo
}

// Função que insere uma aresta entre os vértices u e v (grafo não direcionado)
void InsereAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 1;  // Marca a conexão de u para v
    g->adj[v][u] = 1;  // Marca a conexão de v para u (pois o grafo é não direcionado)
}

// Função que remove uma aresta entre os vértices u e v
void RemoveAresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 0;  // Remove a conexão de u para v
    g->adj[v][u] = 0;  // Remove a conexão de v para u
}

// Função que verifica se há uma aresta entre u e v
int TemAresta(p_grafo g, int u, int v) {
    return g->adj[u][v];  // Retorna 1 se há aresta, 0 caso contrário
}

// Função que lê um grafo da entrada padrão
p_grafo LeGrafo() {
    int n, m, i, u, v;
    p_grafo g;
    scanf("%d %d", &n, &m);  // Lê número de vértices (n) e número de arestas (m)
    g = CriarGrafo(n);       // Cria o grafo com n vértices

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);  // Lê os pares de vértices conectados por arestas
        InsereAresta(g, u, v);   // Insere cada aresta no grafo
    }
    return g;  // Retorna o grafo criado
}

// Função que imprime todas as arestas do grafo
void ImprimeArestas(p_grafo g) {
    int u, v;
    for (u = 0; u < g->n; u++) {
        for (v = 0; v < g->n; v++) {
            if (g->adj[u][v]) {             // Se existe uma aresta entre u e v
                printf("{%d %d}\n", u, v);  // Imprime a aresta
            }
        }
    }
}

// Função que calcula o grau (número de conexões) de um vértice u
int Grau(p_grafo g, int u) {
    int v, grau = 0;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {  // Conta quantas arestas saem de u
            grau++;
        }
    }
    return grau;  // Retorna o grau total
}

// Função que encontra o vértice mais popular (com maior grau)
int MaisPopular(p_grafo g) {
    int u, max, grauMax, grauAtual;
    max = 0;               // Inicializa o mais popular como o vértice 0
    grauMax = Grau(g, 0);  // Calcula o grau do vértice 0

    for (u = 1; u < g->n; u++) {
        grauAtual = Grau(g, u);     // Calcula o grau do vértice u
        if (grauAtual > grauMax) {  // Se tiver grau maior, atualiza o máximo
            grauMax = grauAtual;
            max = u;
        }
    }
    return max;  // Retorna o vértice com maior grau
}

// Função que imprime "recomendações" de vértices conectados a amigos de 'u'
void ImprimeRecomendacoes(p_grafo g, int u) {
    int v, w;
    for (v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {  // Se v é amigo de u
            for (w = 0; w < g->n; w++) {
                if (g->adj[v][w] && w != u && !g->adj[u][w])
                    // Se w é amigo de v, mas não de u e não é o próprio u
                    printf("%d\n", w);  // Recomenda w a u
            }
        }
    }
}

// Função que verifica se existe caminho entre os vértices s e t
int ExisteCaminho(p_grafo g, int s, int t) {
    int encontrou, i, *visitado = malloc(g->n * sizeof(int));  // Vetor para marcar vértices visitados
    for (i = 0; i < g->n; i++) {
        visitado[i] = 0;  // Inicializa todos como não visitados
    }
    encontrou = BuscaRec(g, visitado, s, t);  // Faz busca recursiva (DFS)
    free(visitado);                           // Libera a memória
    return encontrou;                         // Retorna 1 se encontrou caminho, 0 se não
}

// Função auxiliar recursiva para busca de caminho (DFS)
int BuscaRec(p_grafo g, int* visitado, int v, int t) {
    int w;
    if (v == t) {  // Se encontrou o vértice destino
        return 1;
    }
    visitado[v] = 1;  // Marca o vértice atual como visitado
    for (w = 0; w < g->n; w++) {
        if (g->adj[v][w] && !visitado[w]) {   // Se existe aresta e w ainda não foi visitado
            if (BuscaRec(g, visitado, w, t))  // Continua a busca a partir de w
                return 1;                     // Se achou o destino, retorna 1
        }
    }
    return 0;  // Se não encontrou, retorna 0
}

/*
 * RACIOCINIO GERAL:
 * Para encontrar componentes conexas em um grafo:
 * 1. Marcar todos os vertices como "nao visitados" (-1)
 * 2. Para cada vertice nao visitado:
 *    - Fazer uma busca (DFS) marcando todos os vertices alcancaveis com o mesmo numero de componente
 *    - Incrementar o contador de componentes
 * 3. Retornar o array com o componente de cada vertice
 */
int* EncontraComponentes(p_grafo g) {
    // Declaracao das variaveis:
    // s = vertice sendo analisado
    // c = contador de componentes (comeca em 0)
    // componentes = array que armazena qual componente cada vertice pertence
    int s, c = 0, *componentes = malloc(g->n * sizeof(int));

    // PASSO 1: Inicializar todos os vertices como nao visitados (-1)
    // Percorre todos os n vertices do grafo
    for (s = 0; s < g->n; s++) {
        componentes[s] = -1;  // -1 indica que o vertice ainda nao foi visitado
    }

    // PASSO 2: Para cada vertice nao visitado, explorar sua componente conexa
    // Percorre novamente todos os vertices
    for (s = 0; s < g->n; s++) {
        // Se o vertice s ainda nao foi visitado (componentes[s] == -1)
        if (componentes[s] == -1) {
            // Visita recursivamente todos os vertices alcancaveis a partir de s
            // marcando-os com o numero do componente atual (c)
            VisitaRec(g, componentes, c, s);

            // Incrementa o contador de componentes para a proxima componente conexa
            c++;
        }
    }

    // PASSO 3: Retornar o array com os componentes
    // Cada posicao i do array contem o numero do componente ao qual o vertice i pertence
    return componentes;
}

/*
 * RACIOCINIO DA BUSCA EM PROFUNDIDADE (DFS):
 * Esta funcao implementa uma DFS (Depth-First Search) recursiva
 * que marca todos os vertices alcancaveis a partir de v com o mesmo numero de componente
 * Versao para matriz de adjacencia
 */
void VisitaRec(p_grafo g, int* componentes, int comp, int v) {
    int w;

    // PASSO 1: Marcar o vertice atual v como pertencente ao componente comp
    componentes[v] = comp;

    // PASSO 2: Percorrer todos os possiveis vizinhos do vertice v
    // Para matriz de adjacencia, verifica todos os vertices
    for (w = 0; w < g->n; w++) {
        // Se existe aresta entre v e w E w ainda nao foi visitado
        if (g->adj[v][w] && componentes[w] == -1) {
            // RECURSAO: Visita o vizinho nao visitado
            // Isso garante que todos os vertices alcancaveis serao marcados
            VisitaRec(g, componentes, comp, w);
        }
    }
    // Quando a recursao terminar, todos os vertices da componente conexa
    // estarao marcados com o mesmo numero (comp)
}

/*
 * Funcao encontraCaminhos
 * Encontra caminhos de um vertice origem s para todos os vertices alcancaveis
 * Retorna um array onde pai[i] indica o pai do vertice i na arvore de busca
 * -1 indica vertice nao alcancavel, i indica raiz (pai de si mesmo)
 */
int* encontraCaminhos(p_grafo g, int s) {
    int i, *pai = malloc(g->n * sizeof(int));
    // Inicializa todos os vertices como nao visitados (-1)
    for (i = 0; i < g->n; i++) {
        pai[i] = -1;
    }
    // Inicia busca em profundidade a partir de s
    // s e pai de si mesmo (raiz da busca)
    buscaEmProfundidade(g, pai, s, s);
    return pai;
}

/*
 * Funcao buscaEmProfundidade (recursiva)
 * Implementa DFS recursiva para construir arvore de caminhos
 * g = grafo, pai = array de pais, p = pai do vertice atual, v = vertice atual
 * Versao para matriz de adjacencia
 */
void buscaEmProfundidade(p_grafo g, int* pai, int p, int v) {
    int w;
    // Marca o pai do vertice atual
    pai[v] = p;

    // Percorre todos os possiveis vizinhos
    for (w = 0; w < g->n; w++) {
        // Se existe aresta entre v e w E w ainda nao foi visitado
        if (g->adj[v][w] && pai[w] == -1) {
            // Continua a busca recursivamente
            // v se torna o pai de w
            buscaEmProfundidade(g, pai, v, w);
        }
    }
}

/*
 * Funcao busca_em_profundidade (iterativa com pilha)
 * Implementa DFS iterativa usando pilha explicita
 * Alternativa a versao recursiva, evita estouro de pilha em grafos grandes
 * Retorna array de pais formando arvore de busca
 */
int* busca_em_profundidade(p_grafo g, int s) {
    int w, v;
    int* pai = malloc(g->n * sizeof(int));
    int* visitado = malloc(g->n * sizeof(int));
    p_pilha p = criar_pilha();
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }
    empilhar(p, s);
    pai[s] = s;
    while (!pilha_vazia(p)) {
        v = desempilhar(p);
        visitado[v] = 1;
        for (w = 0; w < g->n; w++)
            if (g->adj[v][w] && !visitado[w]) {
                pai[w] = v;
                empilhar(p, w);
            }
    }
    destroi_pilha(p);
    free(visitado);
    return pai;
}

/*
 * Funcao busca_em_largura (BFS - Breadth-First Search)
 * Implementa BFS usando fila para explorar o grafo nivel por nivel
 * Retorna array de pais formando arvore de busca
 * BFS encontra o caminho mais curto (em numero de arestas) entre vertices
 */
int* busca_em_largura(p_grafo g, int s) {
    int w, v;
    int* pai = malloc(g->n * sizeof(int));
    int* visitado = malloc(g->n * sizeof(int));
    p_fila f = criar_fila();

    // Inicializa todos os vertices como nao visitados
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }

    // Enfileira o vertice inicial
    enfileira(f, s);
    pai[s] = s;
    visitado[s] = 1;

    // Processa vertices nivel por nivel
    while (!fila_vazia(f)) {
        v = desenfileira(f);

        // Explora todos os vizinhos de v
        for (w = 0; w < g->n; w++) {
            if (g->adj[v][w] && !visitado[w]) {
                visitado[w] = 1;  // Marca como visitado para evitar repeticao na fila
                pai[w] = v;       // Define v como pai de w
                enfileira(f, w);  // Enfileira w para processar seus vizinhos depois
            }
        }
    }

    destroi_fila(f);
    free(visitado);
    return pai;
}

/*
 * Funcao prim
 * Implementa o algoritmo de Prim para encontrar a Arvore Geradora Minima (MST)
 * usando matriz de adjacencia
 * g: grafo com arestas ponderadas (matriz contem os pesos, 0 = sem aresta)
 * s: vertice inicial
 * Retorna: array de pais representando a MST
 *          pai[v] = -1 se v nao eh alcancavel de s
 *          pai[v] = v se v eh a raiz
 *          pai[v] = u significa que a aresta (u,v) faz parte da MST
 */
int* prim(p_grafo g, int s) {
    int v, w, *pai = malloc(g->n * sizeof(int));
    int* custo = malloc(g->n * sizeof(int));   // Custo minimo para conectar cada vertice
    int* na_mst = malloc(g->n * sizeof(int));  // Marca vertices ja incluidos na MST

    // Inicializa todos os vertices
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        custo[v] = INT_MAX;
        na_mst[v] = 0;
    }

    // Define o vertice inicial
    pai[s] = s;
    custo[s] = 0;

    // Processa todos os vertices
    for (int i = 0; i < g->n; i++) {
        // Encontra o vertice com menor custo que ainda nao esta na MST
        int min_custo = INT_MAX;
        int u = -1;
        for (v = 0; v < g->n; v++) {
            if (!na_mst[v] && custo[v] < min_custo) {
                min_custo = custo[v];
                u = v;
            }
        }

        // Se nao encontrou vertice alcancavel, o grafo eh desconexo
        if (u == -1) {
            break;
        }

        // Adiciona u a MST
        na_mst[u] = 1;

        // Atualiza os custos dos vizinhos de u
        for (w = 0; w < g->n; w++) {
            // Se existe aresta (u,w), w nao esta na MST e o peso eh menor
            if (g->adj[u][w] != 0 && !na_mst[w] && g->adj[u][w] < custo[w]) {
                custo[w] = g->adj[u][w];
                pai[w] = u;
            }
        }
    }

    free(custo);
    free(na_mst);
    return pai;
}
