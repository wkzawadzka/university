#include "algorithms.c"
#include "random.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size;
float t;
bool printing = true; // print sorted arrays or not

int main() {
    // input and output
    int i, *arr, repeats, stepsize;
    FILE *output = fopen("output.csv", "w+");
    fprintf(output, "type,n,time\n");
    printf("\nenter first size of a list: ");
    scanf("%d", &size);
    printf("\nenter stepsize: ");
    scanf("%d", &stepsize);
    printf("\nenter number of measuring points: ");
    scanf("%d", &repeats);

    for (i = 0; i < repeats; i++) {
        printf("\n\n\nfor n equal to %d:", size);
        // // // BS [bubble sort]
        arr = inp(size, printing);
        printf("\n____________________________________\nsorted by bubble sort:\n");
        t = bubblesort(arr, size, printing);
        printf("\ntime: %f s", t);
        fprintf(output, "BS,%d,%f\n", size, t);

        // HS [heap sort]
        arr = inp(size, printing);
        printf("\n____________________________________\nsorted by heap sort:\n");
        t = heapsort(arr, size, printing);
        printf("\ntime: %f s", t);
        fprintf(output, "HS,%d,%f\n", size, t);

        // // ShS [shell sort]
        arr = inp(size, printing);
        printf("\n____________________________________\nsorted by shell sort:\n");
        t = shellsort(arr, size, printing);
        printf("\ntime: %f s", t);
        fprintf(output, "ShS,%d,%f\n", size, t);

        // // CS [counting sort]
        arr = inp(size, printing);
        printf("\n____________________________________\nsorted by counting sort:\n");
        t = countingsort(arr, size, printing);
        printf("\ntime: %f s", t);
        fprintf(output, "CS,%d,%f\n", size, t);

        size = size + stepsize;
    }

    fclose(output);
    return 0;
}