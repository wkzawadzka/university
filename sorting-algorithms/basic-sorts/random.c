// input generator

#include <stdbool.h>
int *inp(int size, bool printing) {
    int i;
    srand(time(0));
    static int arr[5000000];
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    return arr;
}