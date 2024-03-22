#include "A2.h"
void *producer()
{
    int i;
    int value, id, pid;
    int produced = 0;
    pid = getpid();
    while (1)
    // for (i = 1; i <= N; i++)
    {
        value = rand() % 100; // some random value
        sem_wait(Sp);         // decrement Sp

        sem_wait(lock);

        id = dequeue(empty, 0); // get index of empty space
        buffer[id] = value;     // fill buffer at this id
        enqueue(filled, id, 1); // add id to filled positions
        produced++;
        printf("[producer id:%d] Produced at index %d.\n", pid, id);

        sem_post(lock);

        sleep(1 + rand() % 3); // delay randomly
        sem_post(Sc);          // increment Sc
    }
    printf("[producer id:%d] Finished. Total produced: %d.\n", pid, produced);
}
