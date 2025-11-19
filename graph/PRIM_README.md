# Algoritmo de Prim - Árvore Geradora Mínima (MST)

## O que é?

O algoritmo de Prim encontra a **Árvore Geradora Mínima (Minimum Spanning Tree - MST)** de um grafo ponderado conexo.

Uma MST é um subconjunto de arestas que:

- Conecta todos os vértices do grafo
- Não forma ciclos (é uma árvore)
- Tem o menor custo total possível (soma dos pesos das arestas)

## Como funciona?

1. **Inicialização**: Começa com um vértice qualquer
2. **Crescimento**: A cada passo, adiciona a aresta de menor peso que conecta um vértice já incluído na árvore a um vértice ainda não incluído
3. **Término**: Para quando todos os vértices estão na árvore

## Diferença: Prim vs Dijkstra

Embora similares na implementação, têm objetivos diferentes:

| Aspecto            | Prim                                 | Dijkstra                                    |
| ------------------ | ------------------------------------ | ------------------------------------------- |
| **Objetivo**       | Encontrar MST                        | Encontrar caminhos mínimos                  |
| **O que minimiza** | Peso da ARESTA que conecta à árvore  | DISTÂNCIA TOTAL da origem                   |
| **Resultado**      | Árvore que conecta todos os vértices | Caminhos mais curtos para todos os vértices |
| **Uso**            | Redes (cabos, estradas)              | Rotas (GPS, redes)                          |

### Exemplo Visual

Grafo: 0-1(peso 1), 0-2(peso 4), 1-2(peso 2)

**Prim (partindo de 0)**:

- Adiciona 0-1 (peso 1) - menor aresta saindo de 0
- Adiciona 1-2 (peso 2) - menor aresta conectando {0,1} a vértices fora
- **Custo total: 3**

**Dijkstra (partindo de 0)**:

- Caminho para 1: 0→1 (custo 1)
- Caminho para 2: 0→1→2 (custo 1+2=3)
- _(Não escolhe 0→2 direto, apesar de ser uma aresta)_

## Implementações

### Lista de Adjacência

- Usa **fila de prioridade (heap)** para eficiência
- Complexidade: O((V + E) log V)
- Melhor para grafos esparsos

### Matriz de Adjacência

- Busca linear pelo vértice de menor custo
- Complexidade: O(V²)
- Adequado para grafos densos

## Aplicações Práticas

1. **Redes de Computadores**: Minimizar cabo necessário
2. **Redes Elétricas**: Minimizar fios elétricos
3. **Redes de Água/Gás**: Otimizar tubulações
4. **Planejamento Urbano**: Conectar bairros com menor custo
5. **Aproximação de Problemas**: Base para TSP, Steiner Tree

## Propriedades

- ✅ Sempre encontra uma solução ótima
- ✅ Funciona para qualquer vértice inicial
- ⚠️ Requer grafo conexo (senão produz floresta geradora mínima)
- ⚠️ Não funciona com pesos negativos se não forem tratados adequadamente

## Como Usar

```c
// Cria grafo ponderado
p_grafo g = CriarGrafo(5);
InsereArestaPonderada(g, 0, 1, 2);
InsereArestaPonderada(g, 1, 2, 3);
// ... mais arestas

// Executa Prim
int* pai = prim(g, 0);  // Começa do vértice 0

// Imprime arestas da MST
for (int i = 0; i < g->n; i++) {
    if (pai[i] != -1 && pai[i] != i) {
        printf("Aresta MST: %d - %d\n", pai[i], i);
    }
}

free(pai);
```

## Observações

- O array `pai` retornado indica quais arestas fazem parte da MST
- `pai[v] = u` significa que a aresta (u,v) está na MST
- `pai[v] = -1` significa que v não é alcançável (grafo desconexo)
- `pai[s] = s` indica o vértice inicial (raiz)
