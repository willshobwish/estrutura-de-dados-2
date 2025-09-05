
#include <stddef.h>
#include <stdlib.h>

int* RandomArrayGenerator(int n, int min, int max) {
    if (max - min + 1 < n) {
        // Not enough unique numbers in the range
        return NULL;
    }
    int* array = malloc(sizeof(int) * n);
    if (!array) return NULL;
    int count = 0;
    while (count < n) {
        int num = (rand() % (max - min + 1)) + min;
        // Check if the number is already in the array
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