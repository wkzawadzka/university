#include "algorithms.c"
#include "input.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global variables
int size;
float t;
bool printing = true; // print sorted arrays or not

int main() {
    // input and output
    int i, *arr, repeats, stepsize, j;
    srand(time(0));
    FILE *output = fopen("teoutput.csv", "w+");
    fprintf(output, "type,n,data,time\n");
    printf("\nenter first size of a list: ");
    scanf("%d", &size);
    printf("\nenter stepsize: ");
    scanf("%d", &stepsize);
    printf("\nenter number of measuring points: ");
    scanf("%d", &repeats);

    char *short_sorts[3] = {"HS", "MS", "QS"};
    char *long_sorts[3] = {"HEAPSORT", "MERGESORT", "QUICKSORT"};
    char *data[6] = {"random", "constant", "increasing", "decreasing", "A-shaped", "V-shaped"};

    for (i = 0; i < repeats; i++) {
        printf("\n\nn equals to %d:", size);
        for (j = 0; j < 6; j++) {
            printf("\n{%s:", data[j], j);
            // // HS [heap sort]
            arr = select_data(j, size, printing);
            printf("\n%s:", long_sorts[0]);
            t = heapsort(arr, size, printing);
            printf("\n  time: %f s", t);
            fprintf(output, "%s,%d,%s,%f\n", short_sorts[0], size, data[j], t);

            // // // MS [merge sort]
            arr = select_data(j, size, printing);
            printf("\n%s:", long_sorts[1]);
            t = mergesort(arr, size, printing);
            printf("\n  time: %f s", t);
            fprintf(output, "%s,%d,%s,%f\n", short_sorts[1], size, data[j], t);

            // QS [quick sort with middle pivot]
            arr = select_data(j, size, printing);
            printf("\n%s:", long_sorts[2]);
            t = quicksort(arr, size, printing);
            printf("\n  time: %f s", t);
            printf("}\n");
            fprintf(output, "%s,%d,%s,%f\n", short_sorts[2], size, data[j], t);
        }
        size = size + stepsize;
    }

    fclose(output);
    return 0;
}