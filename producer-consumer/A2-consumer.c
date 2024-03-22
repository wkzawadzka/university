#include "A2.h"
void *consumer()
{
    int consumed = 0;
    int i, id, pid;
    pid = getpid();
    while (1)
    // for (i = 1; i <= N; i++)
    {
        sem_wait(Sc); // decrement Sc

        sem_wait(lock);

        id = dequeue(filled, 1); // get id of filled position to consume
        enqueue(empty, id, 0);   // add id at the end of empty indices queue
        consumed++;
        printf("[consumer id:%d] Consumed at index %d.\n", pid, id);

        sem_post(lock);

        sleep(rand() % 3 + 1);
        sem_post(Sp);
    }
    printf("[consumer id:%d] Finished. Total consumed: %d.\n", pid, consumed);
}