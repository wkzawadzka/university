
// Bubble sort algoritm implementation //

float bubblesort(int *list, int size, bool printing)
{
    clock_t start = clock();
    int i, j;
    float t;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (list[j] > list[j + 1])
            {
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", list[i]);
        }
    }
    return t;
}

// Heap sort algoritm implementation //

int *heapify(int *list, int size, int i)
{
    int croot = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((left < size) && (list[croot] < list[left]))
    {
        croot = left;
    }

    if ((right < size) && (list[croot] < list[right]))
    {
        croot = right;
    }

    if (croot != i)
    {
        int temp = list[i];
        list[i] = list[croot];
        list[croot] = temp;

        heapify(list, size, croot);
    }
}

void print_list(int *array, int size)
{
    printf("Max heap:\n\n");
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

float heapsort(int *array, int size, bool printing)
{
    clock_t start = clock();
    int i;
    float t;
    // i = size / 2 - 1 -> last parent index
    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }
    print_list(array, size);

    for (i = size - 1; i > 0; i--)
    {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        heapify(array, i, 0);
    }
    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", array[i]);
        }
    }
    return t;
}

// Shell sort algoritm implementation //

float shellsort(int *array, int size, bool printing)
{
    clock_t start = clock();
    int i, j, temp, gap;
    float t;

    for (gap = size / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < size; i++)
        {
            for (j = i - gap; j >= 0; j = j - gap)
            {
                if (array[j + gap] >= array[j])
                {
                    break;
                }
                else
                {
                    temp = array[j];
                    array[j] = array[j + gap];
                    array[j + gap] = temp;
                }
            }
        }
    }

    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", array[i]);
        }
    }
    return t;
}

// Counting sort algoritm implementation //

float countingsort(int *array, int size, bool printing)
{
    clock_t start = clock();
    int i, max;
    float t;
    static int counts[100];
    static int final[100000000];
    t = 5; // for now, after change to clock

    // find maximum
    max = array[0];
    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    // make a list with elements' comulative counts
    for (int i = 0; i <= max; ++i)
    {
        counts[i] = 0;
    }
    for (int i = 0; i < size; ++i)
    {
        counts[array[i]]++;
    }
    for (int i = 1; i <= max; ++i)
    {
        counts[i] = counts[i] + counts[i - 1];
    }

    // final position
    for (i = size - 1; i >= 0; i--)
    {
        final[counts[array[i]] - 1] = array[i];
        counts[array[i]]--; // to account for repeated numbers
    }

    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", final[i]);
        }
    }
    return t;
}