#include "graph.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

p_grafo CriarGrafo(int n) {
    /*
     * Função CriarGrafo
     * Cria e inicializa um grafo com n vértices usando lista de adjacência.
     * Cada vértice terá uma lista (inicialmente vazia) para armazenar seus vizinhos.
     */
    int i;  // Variável para iteração
    // Aloca espaço para a estrutura principal do grafo
    p_grafo g = malloc(sizeof(Grafo));
    // Define o número de vértices do grafo
    g->n = n;
    // Aloca um vetor de ponteiros para listas de adjacência, um para cada vértice
    g->adjacencia = malloc(n * sizeof(p_no));
    // Inicializa todas as listas de adjacência como vazias (NULL)
    for (i = 0; i < n; i++) {
        g->adjacencia[i] = NULL;
    }
    // Retorna o ponteiro para o grafo criado
    return g;
}

/*
 * Função LiberaLista
 * Libera recursivamente todos os nós de uma lista de adjacência.
 * Utilizada para liberar a memória de cada lista de vizinhos de um vértice.
 */
void LiberaLista(p_no lista) {
    // Se a lista não está vazia
    if (lista != NULL) {
        // Libera recursivamente o próximo nó da lista
        LiberaLista(lista->prox);
        // Libera o nó atual
        free(lista);
    }
}

void DestroiGrafo(p_grafo g) {
    // Função que libera toda a memória alocada para o grafo.
    int i;
    // Para cada vértice, libera a lista de adjacência (os vizinhos).
    for (i = 0; i < g->n; i++) {
        LiberaLista(g->adjacencia[i]);
    }
    // Libera o vetor de ponteiros para as listas de adjacência.
    free(g->adjacencia);
    // Libera a estrutura principal do grafo.
    free(g);
}

p_no InsereNaLista(p_no lista, int v, int peso) {
    // Função que insere um novo elemento (v) no início da lista de adjacência.
    // Aloca memória para um novo nó da lista de adjacência.
    p_no novo = malloc(sizeof(No));
    // Define o valor do vértice armazenado neste nó.
    novo->v = v;
    // Define o peso da aresta
    novo->peso = peso;
    // Faz o novo nó apontar para o início da lista recebida (inserção no início).
    novo->prox = lista;
    // Retorna o ponteiro para o novo nó, que agora é o início da lista.
    return novo;
}

/*
 * Função InsereAresta
 * Insere uma aresta não direcionada entre os vértices u e v com peso padrão 1.
 * Para lista de adjacência: adiciona v na lista de u e u na lista de v.
 */
void InsereAresta(p_grafo g, int u, int v) {
    InsereArestaPonderada(g, u, v, 1);
}

/*
 * Função InsereArestaPonderada
 * Insere uma aresta não direcionada entre os vértices u e v com peso especificado.
 */
void InsereArestaPonderada(p_grafo g, int u, int v, int peso) {
    // Adiciona u na lista de adjacência de v (v passa a ter u como vizinho)
    g->adjacencia[v] = InsereNaLista(g->adjacencia[v], u, peso);
    // Adiciona v na lista de adjacência de u (u passa a ter v como vizinho)
    g->adjacencia[u] = InsereNaLista(g->adjacencia[u], v, peso);
}

/*
 * Função RemoveDaLista
 * Remove o nó com valor v da lista de adjacência.
 * Retorna o ponteiro para o início da lista após a remoção.
 * Utiliza recursão para encontrar e remover o nó desejado.
 */
p_no RemoveDaLista(p_no lista, int v) {
    p_no proximo;
    // Caso base: lista vazia, nada para remover
    if (lista == NULL) {
        return NULL;
    }
    // Se o nó atual tem o valor v, remove este nó
    else if (lista->v == v) {
        proximo = lista->prox;  // Guarda o próximo nó
        free(lista);            // Libera o nó atual
        return proximo;         // Retorna o próximo nó como novo início da lista
    }
    // Caso contrário, continua procurando na lista
    else {
        lista->prox = RemoveDaLista(lista->prox, v);  // Chama recursivamente para o próximo
        return lista;                                 // Retorna o início da lista (que não mudou)
    }
}

// Função que remove uma aresta não direcionada entre os vértices u e v.
// Ou seja, remove v da lista de adjacência de u e u da lista de adjacência de v.
void RemoveAresta(p_grafo g, int u, int v) {
    // Remove v da lista de adjacência de u.
    g->adjacencia[u] = RemoveDaLista(g->adjacencia[u], v);
    // Remove u da lista de adjacência de v.
    g->adjacencia[v] = RemoveDaLista(g->adjacencia[v], u);
    // Após essas operações, a aresta entre u e v deixa de existir no grafo.
}

// Função que verifica se existe uma aresta entre os vértices u e v.
// Retorna 1 se existe, 0 caso contrário.
int TemAresta(p_grafo g, int u, int v) {
    p_no t;  // Ponteiro para percorrer a lista de adjacência de u.
    // Percorre a lista de adjacência de u.
    for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
        // Se encontrar o vértice v na lista, retorna 1 (aresta existe).
        if (t->v == v) {
            return 1;
        }
    }
    // Se não encontrar v na lista, retorna 0 (aresta não existe).
    return 0;
}

// Função que lê um grafo da entrada padrão.
// Espera receber o número de vértices (n) e arestas (m), seguido de m pares de vértices representando as arestas.
p_grafo LeGrafo() {
    int n, m, i, u, v;  // n: número de vértices, m: número de arestas, u/v: vértices da aresta, i: contador
    p_grafo g;          // Ponteiro para o grafo

    // Lê o número de vértices e arestas
    scanf("%d %d", &n, &m);

    // Cria e inicializa o grafo com n vértices
    g = CriarGrafo(n);

    // Para cada aresta, lê os vértices u e v e insere a aresta no grafo
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        InsereAresta(g, u, v);
    }

    // Retorna o ponteiro para o grafo preenchido
    return g;
}

// Função que imprime todas as arestas do grafo.
// Para cada vértice, percorre sua lista de adjacência e imprime cada conexão.
void ImprimeArestas(p_grafo g) {
    int u;   // Variável para iterar sobre os vértices
    p_no t;  // Ponteiro para percorrer a lista de adjacência de cada vértice
    // Para cada vértice u do grafo
    for (u = 0; u < g->n; u++) {
        // Percorre a lista de adjacência de u
        for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
            // Imprime a aresta entre u e t->v
            printf("{%d %d}\n", u, t->v);
        }
    }
    // Ao final, todas as arestas do grafo são exibidas no formato {u v}
}

/*
 * Função Grau
 * Calcula o grau (número de conexões) de um vértice u.
 * Para lista de adjacência: percorre a lista e conta os nós.
 * O grau representa quantos vizinhos (arestas) o vértice possui.
 */
int Grau(p_grafo g, int u) {
    int grau = 0;  // Variável para contar o grau
    p_no t;        // Ponteiro para percorrer a lista de adjacência
    // Percorre toda a lista de adjacência do vértice u
    for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
        grau++;  // Incrementa o grau para cada vizinho encontrado
    }
    // Retorna o número total de vizinhos (grau do vértice)
    return grau;
}

// Função que encontra o vértice mais popular (com maior grau)
int MaisPopular(p_grafo g) {
    int u, max, grauMax, grauAtual;
    max = 0;               // Inicializa o mais popular como o vértice 0
    grauMax = Grau(g, 0);  // Calcula o grau do vértice 0

    // Percorre todos os vértices a partir do 1
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
// Para lista: percorre a lista de adjacência de u, depois a lista de cada vizinho
void ImprimeRecomendacoes(p_grafo g, int u) {
    p_no t, w;
    // Percorre todos os vizinhos de u (amigos diretos)
    for (t = g->adjacencia[u]; t != NULL; t = t->prox) {
        int v = t->v;  // v é um amigo de u
        // Percorre todos os vizinhos de v (amigos dos amigos)
        for (w = g->adjacencia[v]; w != NULL; w = w->prox) {
            // Se w não é u E w não é amigo de u, então recomenda
            if (w->v != u && !TemAresta(g, u, w->v)) {
                printf("%d\n", w->v);  // Recomenda w a u
            }
        }
    }
}

/*
 * RACIOCÍNIO GERAL:
 * Para encontrar componentes conexas em um grafo:
 * 1. Marcar todos os vértices como "não visitados" (-1)
 * 2. Para cada vértice não visitado:
 *    - Fazer uma busca (DFS) marcando todos os vértices alcançáveis com o mesmo número de componente
 *    - Incrementar o contador de componentes
 * 3. Retornar o array com o componente de cada vértice
 */
int* EncontraComponentes(p_grafo g) {
    // Declaração das variáveis:
    // s = vértice sendo analisado
    // c = contador de componentes (começa em 0)
    // componentes = array que armazena qual componente cada vértice pertence
    int s, c = 0, *componentes = malloc(g->n * sizeof(int));

    // PASSO 1: Inicializar todos os vértices como não visitados (-1)
    // Percorre todos os n vértices do grafo
    for (s = 0; s < g->n; s++) {
        componentes[s] = -1;  // -1 indica que o vértice ainda não foi visitado
    }

    // PASSO 2: Para cada vértice não visitado, explorar sua componente conexa
    // Percorre novamente todos os vértices
    for (s = 0; s < g->n; s++) {
        // Se o vértice s ainda não foi visitado (componentes[s] == -1)
        if (componentes[s] == -1) {
            // Visita recursivamente todos os vértices alcançáveis a partir de s
            // marcando-os com o número do componente atual (c)
            VisitaRec(g, componentes, c, s);

            // Incrementa o contador de componentes para a próxima componente conexa
            c++;
        }
    }

    // PASSO 3: Retornar o array com os componentes
    // Cada posição i do array contém o número do componente ao qual o vértice i pertence
    return componentes;
}

/*
 * RACIOCÍNIO DA BUSCA EM PROFUNDIDADE (DFS):
 * Esta função implementa uma DFS (Depth-First Search) recursiva
 * que marca todos os vértices alcançáveis a partir de v com o mesmo número de componente
 */
void VisitaRec(p_grafo g, int* componentes, int comp, int v) {
    // t = ponteiro para percorrer a lista de adjacência
    p_no t;

    // PASSO 1: Marcar o vértice atual v como pertencente ao componente comp
    componentes[v] = comp;

    // PASSO 2: Percorrer todos os vizinhos do vértice v
    // t começa no primeiro nó da lista de adjacência de v
    // e avança enquanto não chegar ao fim (NULL)
    for (t = g->adjacencia[v]; t != NULL; t = t->prox) {
        // Se o vizinho t->v ainda não foi visitado (componentes[t->v] == -1)
        if (componentes[t->v] == -1) {
            // RECURSÃO: Visita o vizinho não visitado
            // Isso garante que todos os vértices alcançáveis serão marcados
            VisitaRec(g, componentes, comp, t->v);
        }
    }
    // Quando a recursão terminar, todos os vértices da componente conexa
    // estarão marcados com o mesmo número (comp)
}

int* encontraCaminhos(p_grafo g, int s) {
    int i, *pai = malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++) {
        pai[i] = -1;
    }
    buscaEmProfundidade(g, pai, s, s);
    return pai;
}

void buscaEmProfundidade(p_grafo g, int* pai, int p, int v) {
    p_no t;
    pai[v] = p;
    for (t = g->adjacencia[v]; t != NULL; t = t->prox) {
        if (pai[t->v] == -1) {
            buscaEmProfundidade(g, pai, v, t->v);
        }
    }
}

void ordenacao_topologica(p_grafo g) {
    int s, *visitado = malloc(g->n * sizeof(int));
    for (s = 0; s < g->n; s++)
        visitado[s] = 0;
    for (s = 0; s < g->n; s++)
        if (!visitado[s])
            visita_rec(g, visitado, s);
    free(visitado);
    printf("\n");
}
void visita_rec(p_grafo g, int* visitado, int v) {
    p_no t;
    visitado[v] = 1;
    for (t = g->adjacencia[v]; t != NULL; t = t->prox)
        if (!visitado[t->v])
            visita_rec(g, visitado, t->v);
    printf("%d ", v);
}

// ========== FUNCOES DA FILA DE PRIORIDADE (HEAP MINIMO) ==========

/*
 * Funcao auxiliar para trocar dois itens na fila de prioridade
 */
void troca(p_fp h, int i, int j) {
    Item temp = h->v[i];
    h->v[i] = h->v[j];
    h->v[j] = temp;

    // Atualiza os indices
    h->indice[h->v[i].vertice] = i;
    h->indice[h->v[j].vertice] = j;
}

/*
 * Funcao auxiliar para subir um elemento no heap (heapify up)
 */
void sobe(p_fp h, int k) {
    int pai;
    while (k > 0) {
        pai = (k - 1) / 2;
        if (h->v[k].prioridade < h->v[pai].prioridade) {
            troca(h, k, pai);
            k = pai;
        } else {
            break;
        }
    }
}

/*
 * Funcao auxiliar para descer um elemento no heap (heapify down)
 */
void desce(p_fp h, int k) {
    int filho;
    while (2 * k + 1 < h->n) {
        filho = 2 * k + 1;

        // Escolhe o menor filho
        if (filho + 1 < h->n && h->v[filho + 1].prioridade < h->v[filho].prioridade) {
            filho++;
        }

        if (h->v[filho].prioridade < h->v[k].prioridade) {
            troca(h, k, filho);
            k = filho;
        } else {
            break;
        }
    }
}

/*
 * Funcao criar_fprio
 * Cria e inicializa uma fila de prioridade (min-heap) para armazenar vertices
 * tamanho: numero maximo de elementos (geralmente o numero de vertices do grafo)
 */
p_fp criar_fprio(int tamanho) {
    p_fp h = malloc(sizeof(FP));
    h->v = malloc(tamanho * sizeof(Item));
    h->indice = malloc(tamanho * sizeof(int));
    h->n = 0;
    h->tamanho = tamanho;

    // Inicializa os indices como -1 (nao presente)
    for (int i = 0; i < tamanho; i++) {
        h->indice[i] = -1;
    }

    return h;
}

/*
 * Funcao destroi_fprio
 * Libera toda a memoria alocada pela fila de prioridade
 */
void destroi_fprio(p_fp h) {
    free(h->v);
    free(h->indice);
    free(h);
}

/*
 * Funcao insere
 * Insere um vertice com uma dada prioridade na fila
 * vertice: identificador do vertice
 * prioridade: valor da prioridade (menor = maior prioridade)
 */
void insere(p_fp h, int vertice, int prioridade) {
    h->v[h->n].vertice = vertice;
    h->v[h->n].prioridade = prioridade;
    h->indice[vertice] = h->n;
    h->n++;
    sobe(h, h->n - 1);
}

/*
 * Funcao extrai_minimo
 * Remove e retorna o vertice com menor prioridade
 * Retorna o identificador do vertice
 */
int extrai_minimo(p_fp h) {
    int minimo = h->v[0].vertice;
    h->indice[minimo] = -1;  // Marca como removido

    h->n--;
    if (h->n > 0) {
        h->v[0] = h->v[h->n];
        h->indice[h->v[0].vertice] = 0;
        desce(h, 0);
    }

    return minimo;
}

/*
 * Funcao vazia
 * Verifica se a fila de prioridade esta vazia
 * Retorna 1 se vazia, 0 caso contrario
 */
int vazia(p_fp h) {
    return h->n == 0;
}

/*
 * Funcao prioridade
 * Retorna a prioridade atual de um vertice
 * vertice: identificador do vertice
 * Retorna INT_MAX se o vertice nao estiver na fila
 */
int prioridade(p_fp h, int vertice) {
    int idx = h->indice[vertice];
    if (idx == -1) {
        return INT_MAX;  // Vertice nao esta na fila
    }
    return h->v[idx].prioridade;
}

/*
 * Funcao diminuiprioridade
 * Diminui a prioridade de um vertice ja presente na fila
 * vertice: identificador do vertice
 * nova_prioridade: novo valor de prioridade (deve ser menor que o atual)
 * IMPORTANTE: Esta funcao assume que nova_prioridade < prioridade atual
 */
void diminuiprioridade(p_fp h, int vertice, int nova_prioridade) {
    int idx = h->indice[vertice];

    if (idx == -1) {
        return;  // Vertice nao esta na fila
    }

    // Atualiza a prioridade
    h->v[idx].prioridade = nova_prioridade;

    // Sobe o elemento no heap (pois a prioridade diminuiu)
    sobe(h, idx);
}

// ========== ALGORITMO DE DIJKSTRA ==========

/*
 * Funcao dijkstra
 * Implementa o algoritmo de Dijkstra para encontrar caminhos minimos
 * g: grafo com arestas ponderadas
 * s: vertice origem
 * Retorna: array de pais representando a arvore de caminhos minimos
 *          pai[v] = -1 se v nao eh alcancavel de s
 *          pai[v] = v se v eh a origem
 *          pai[v] = u significa que u eh o predecessor de v no caminho minimo
 */
int* dijkstra(p_grafo g, int s) {
    int v, *pai = malloc(g->n * sizeof(int));
    int* dist = malloc(g->n * sizeof(int));  // Array de distâncias
    p_no t;
    p_fp h = criar_fprio(g->n);

    // Inicializa todos os vertices com distancia infinita
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        dist[v] = INT_MAX;
        insere(h, v, INT_MAX);
    }

    // Define o vertice origem
    pai[s] = s;
    dist[s] = 0;
    diminuiprioridade(h, s, 0);

    // Processa vertices em ordem de distancia crescente
    while (!vazia(h)) {
        v = extrai_minimo(h);

        // Se a distancia eh infinita, vertices restantes sao inalcancaveis
        if (dist[v] != INT_MAX) {
            // Relaxa todas as arestas saindo de v
            for (t = g->adjacencia[v]; t != NULL; t = t->prox) {
                // Se encontrou um caminho mais curto para t->v
                int nova_dist = dist[v] + t->peso;
                if (nova_dist < dist[t->v]) {
                    dist[t->v] = nova_dist;
                    diminuiprioridade(h, t->v, nova_dist);
                    pai[t->v] = v;
                }
            }
        }
    }

    destroi_fprio(h);
    free(dist);
    return pai;
}
