
// Heap sort algoritm implementation //

void heapify(int *list, int size, int i)
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

float heapsort(int *array, int size, bool printing)
{
    float t;
    clock_t start = clock();
    int i;
    // i = size / 2 - 1 -> last parent index
    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }

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

// Merge sort implementation

void merge(int *list, int l, int r, int middle)
{
    int p1, p2, i;
    static int temparray[10000000];
    for (i = l; i <= r; i++)
    {
        temparray[i] = list[i];
    }

    p1 = l;
    p2 = middle + 1;
    i = l;

    while ((p1 <= middle) && (p2 <= r))
    {
        if (temparray[p1] <= temparray[p2])
        {
            list[i] = temparray[p1];
            p1++;
        }
        else
        {
            list[i] = temparray[p2];
            p2++;
        }
        i++;
    }

    while (p1 <= middle)
    {
        list[i] = temparray[p1];
        i++, p1++;
    }
}

void msort(int *list, int l, int r)
{
    int middle;
    if (l < r) // if we have more than 1 element in a list
    {
        middle = (l + r) / 2;
        msort(list, l, middle);
        msort(list, middle + 1, r);
        merge(list, l, r, middle);
    }
}

float mergesort(int *list, int size, bool printing)
{
    float t;
    clock_t start = clock();
    msort(list, 0, size - 1);
    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    int i = 0;
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", list[i]);
        }
    }
    return t;
}

// Quick sort implementation

void qcsort(int *list, int start, int end)
{
    int left, right, temp;
    int mid = (start + end) / 2;
    int pivot = list[mid];
    // if (start >= end)
    // {
    //     return;
    // }
    left = start;
    right = end;
    while (left <= right)
    {

        // Increment the start pointer till it finds an element greater than  pivot
        while (list[left] < pivot)
        {
            left++;
        }

        // Decrement the end pointer till it finds an element less than pivot
        while (list[right] > pivot)
        {
            right--;
        }

        if (left <= right)
        {
            temp = list[left];
            list[left] = list[right];
            list[right] = temp;
            left++;
            right--;
        }
    }

    if (start < right)
    {
        qcsort(list, start, right);
    }
    if (left < end)
    {
        qcsort(list, left, end);
    }
}

float quicksort(int *list, int size, bool printing)
{
    float t;
    clock_t start = clock();
    qcsort(list, 0, size - 1);
    clock_t end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;

    // printing sorted array
    int i = 0;
    if (printing == true)
    {
        for (i = 0; i < size; i++)
        {
            printf("%d ", list[i]);
        }
    }
    return t;
}