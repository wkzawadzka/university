#ifndef A2_H_
#define A2_H_

#define N 10 // max items
#define P 5  // producers
#define C 7  // consumers

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>

typedef struct queue
{
    int *arr;
    int current_size;
    int head; // index of head
    int rear; // index of tail
} queue;

sem_t *Sp, *Sc, *lock;
queue *empty, *filled;
char *buffer;

#endif // A2_H_