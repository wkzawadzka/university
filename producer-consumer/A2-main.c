#include "A2.h"
#include "func.c"
#include "A2-consumer.c"
#include "A2-producer.c"
/*
Write two programs implementing the producer and the consumer of the problem
discussed in Section 12.2.3, but in a generalized version that makes
it possible to run several producers and several consumers at the same time.
A buffer of N slots should allow for running up to N concurrent processes,
producing and consuming different items.
The processes should run in loops, with different and variable speeds.
The ordering of items being consumed should reflect production end times
*/

int main()
{
    int fd1, fd2, fd3, value, id;
    srand(time(NULL));

    // shared memory: 2 queues + buffer
    fd1 = shm_open("/buffer", O_CREAT | O_RDWR, 0600);
    fd2 = shm_open("/filled", O_CREAT | O_RDWR, 0600);
    fd3 = shm_open("/empty", O_CREAT | O_RDWR, 0600);
    ftruncate(fd1, N * sizeof(int));
    ftruncate(fd2, N * sizeof(int));
    ftruncate(fd3, N * sizeof(int));
    buffer = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    filled = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    empty = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd3, 0);
    if (buffer == MAP_FAILED || filled == MAP_FAILED || empty == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    empty = create();
    fill(empty);       // [0,1,2,...,N] initially
    filled = create(); // [] initially

    // 4 semaphores
    Sp = sem_open("/Sp", O_CREAT, 0600, N);
    Sc = sem_open("/Sc", O_CREAT, 0600, 0);
    // free_lock = sem_open("/freelock", O_CREAT, 0600, 1);     // binary
    // filled_lock = sem_open("/filledlock", O_CREAT, 0600, 1); // binary
    lock = sem_open("/lock", O_CREAT, 0600, 1); // binary
    // if (Sp == SEM_FAILED || Sc == SEM_FAILED || free_lock == SEM_FAILED || filled_lock == SEM_FAILED)
    if (Sp == SEM_FAILED || Sc == SEM_FAILED || lock == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    int i, j;
    pthread_t producers[P], consumers[C];
    for (i = 0; i < P; i++)
    {
        if (pthread_create(&producers[i], NULL, (void *)producer, NULL))
        {
            perror("pthread_create()");
            exit(1);
        }
    }
    for (j = 0; j < C; j++)
    {
        if (pthread_create(&consumers[j], NULL, (void *)consumer, NULL))
        {
            perror("pthread_create()");
            exit(1);
        }
    }

    // I think I get deadlock here unfortunately, but I was not able to solve the problem
    for (i = 0; i < P; i++)
    {
        pthread_join(producers[i], NULL); // pthread_join - join with a <<terminated>> thread
    }
    for (j = 0; j < C; j++)
    {
        pthread_join(consumers[j], NULL); // pthread_join - join with a <<terminated>> thread
    }

    // end~
    // free queue memory
    free_queues(filled, empty);
    // semaphores
    sem_close(Sp);
    sem_close(Sc);
    // sem_close(free_lock);
    // sem_close(filled_lock);
    sem_close(lock);
    shm_unlink("/Sp");
    shm_unlink("/Sc");
    shm_unlink("/lock");
    // shm_unlink("/freelock");
    // shm_unlink("/filledlock");
    // unmap buffer and queues
    munmap(buffer, N * sizeof(int));
    munmap(filled, N * sizeof(int));
    munmap(empty, N * sizeof(int));

    return EXIT_SUCCESS;
}
