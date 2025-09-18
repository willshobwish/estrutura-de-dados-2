/**
 * @file random_array_generator.c
 * @brief Geração de um array de inteiros aleatórios únicos dentro de um intervalo.
 *
 * Esta função cria dinamicamente um array de tamanho `n` preenchido com números
 * inteiros únicos escolhidos aleatoriamente no intervalo [`min`, `max`].
 */

#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Gera um array de números inteiros aleatórios únicos.
 *
 * @param n Número de elementos desejados no array.
 * @param min Valor mínimo do intervalo (inclusive).
 * @param max Valor máximo do intervalo (inclusive).
 * @return Ponteiro para o array alocado com números únicos; NULL se falha de alocação
 *         ou se o intervalo não tem elementos suficientes para gerar n números únicos.
 *
 * @note O usuário é responsável por liberar a memória alocada com `free()`.
 * @note A função verifica duplicatas usando busca linear, portanto para n grandes
 *       pode ser lenta. Para n muito grande, considerar outro algoritmo como Fisher-Yates.
 */
int* RandomArrayGenerator(int n, int min, int max) {
    if (max - min + 1 < n) {
        // Não há números suficientes no intervalo para gerar n únicos
        return NULL;
    }
    int* array = malloc(sizeof(int) * n);
    if (!array) return NULL;
    int count = 0;
    while (count < n) {
        int num = (rand() % (max - min + 1)) + min;
        // Verifica se o número já está no array
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (array[i] == num) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            array[count] = num;
            count++;
        }
    }
    return array;
}