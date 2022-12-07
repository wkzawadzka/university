#include <stdbool.h>
static int arr[10000000];
#include <assert.h>

// A: random (uniform distribution)
int *A(int size, bool printing) {
    int i;
    srand(time(0));
    for (i = 0; i < size; i++) {
        arr[i] = rand();
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    return arr;
}

// B: constant value (e.g.equal to 0)

int *B(int size, bool printing) {
    int i, n;
    srand(time(0));
    n = rand();
    for (i = 0; i < size; i++) {
        arr[i] = n;
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    return arr;
}

// C:  increasing order (step equal to 1)
int *C(int size, bool printing) {
    int i, n;
    srand(time(0));
    n = rand();
    arr[0] = n;
    for (i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + 1;
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    return arr;
}

// D:  descending order (step equal to 1)

int *D(int size, bool printing) {
    int i, n;
    srand(time(0));
    n = rand() % (RAND_MAX + 1 - size) + size; // preventing negative numbers
    static int arr[10000000];
    arr[0] = n;
    for (i = 1; i < size; i++) {
        arr[i] = arr[i - 1] - 1;
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    return arr;
}

// F:  descending-ascending order (V -shape – decrease odd numbers - increase even)

int *F(int size, bool printing) {
    int n, i, el;
    el = size / 2;                             // this much even and odd (middle index)
    n = rand() % (RAND_MAX + 1 - size) + size; // random number but with negative num prevention
    while (n % 2 == 0) {
        n = rand() % (RAND_MAX + 1 - size) + size; // get odd number
    }
    assert(n >= 0);
    assert(n >= size);
    assert(n % 2 != 0);

    arr[0] = n;
    for (i = 1; i < el; i++) {
        arr[i] = arr[i - 1] - 2;
    }
    for (i = el; i < size; i++) {
        if (i == el) // if its pivot
        {
            arr[i] = arr[i - 1] + 1; // change from odd to even (with + so no minimum at pivot)
            continue;
        }
        arr[i] = arr[i - 1] + 2;
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }
    return arr;
}

int *E(int size, bool printing) {
    int i, el;
    el = size / 2;

    arr[0] = 1;
    for (i = 1; i < size; i++) {
        if (i < el) {
            arr[i] = arr[i - 1] + 2;
            continue;
        }
        if (i == el) {
            arr[i] = arr[i - 1] + 1;
            continue;
        }
        if (i > el) {
            arr[i] = arr[i - 1] - 2;
            continue;
        }
    }

    if (printing == true) {
        printf("\n____________________________________\nunsorted:\n");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }
    return arr;
}

// Data selector
int *select_data(int n, int size, bool printing) {
    if (n == 0) {
        return A(size, printing);
    }
    if (n == 1) {
        return B(size, printing);
    }
    if (n == 2) {
        return C(size, printing);
    }
    if (n == 3) {
        return D(size, printing);
    }
    if (n == 4) {
        return E(size, printing);
    }
    if (n == 5) {
        return F(size, printing);
    }
}
