#include "A2.h"

queue *create()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->arr = (int *)malloc(sizeof(int) * N);
    q->current_size = 0;
    q->head = 0;
    q->rear = -1;
    return q;
}

void enqueue(queue *q, int item, int type)
{
    // type just for prining 0->empty indices queue, 1->filled indices queue
    // printf("[+][%d] item: %d\n", type, item);
    if (q->current_size == N)
    {
        return;
    }
    else
    {
        q->current_size++;
        q->rear++;
        if (q->rear == N) // circular
        {
            q->rear = 0;
        }
        q->arr[q->rear] = item;
    }
    return;
}

int dequeue(queue *q, int type)
{
    // type just for prining 0->empty indices queue, 1->filled indices queue
    // printf("[-][%d] item: %d\n", type, q->head);
    if (q->current_size != 0)
    {
        int item = q->arr[q->head];
        q->current_size++;
        q->head++;
        if (q->head == N) // circullar
        {
            q->head = 0;
        }
        return item;
    }
}

void fill(queue *q)
{
    int i;
    for (i = 0; i < N; i++)
    {
        enqueue(q, i, 0);
    }
}

void free_queues(queue *q1, queue *q2)
{
    if (q1->arr != NULL)
    {
        free(q1->arr);
    }
    if (q2->arr != NULL)
    {
        free(q2->arr);
    }
    free(q1);
    free(q2);
}

// // TESTING
// int main()
// {
//     int id;
//     queue *empty = create();
//     fill(empty);
//     queue *filled = create();

//     // PRODUCE 2 ELEMENTS
//     id = dequeue(empty, 0);
//     enqueue(filled, id, 1);
//     id = dequeue(empty, 0);
//     enqueue(filled, id, 1);

//     // CONSUME 1 ELEMENT
//     id = dequeue(filled, 1);
//     enqueue(empty, id, 0);

//     // PRODUCE 1 ELEMENT
//     id = dequeue(empty, 0);
//     enqueue(filled, id, 1);

//     free_queues(filled, empty);

//     return 0;
// }