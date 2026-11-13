/*
 * Peterson's Solution for 2-Thread Mutual Exclusion
 *
 * Demonstrates software-based mutual exclusion between two threads using
 * atomic flags and turn variable.
 */

#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

atomic_int flag[2] = {0, 0};
atomic_int turn = 0;
int counter = 0;

void *worker(void *arg) {
    int self = *(int *)arg;
    int other = 1 - self;

    for (int i = 0; i < 100000; i++) {
        atomic_store(&flag[self], 1);
        atomic_store(&turn, other);
        while (atomic_load(&flag[other]) && atomic_load(&turn) == other) {
            /* busy wait */
        }

        /* Critical section */
        counter++;

        atomic_store(&flag[self], 0);
    }
    return NULL;
}

int main(void) {
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    pthread_create(&t0, NULL, worker, &id0);
    pthread_create(&t1, NULL, worker, &id1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Final counter = %d (expected 200000)\n", counter);
    return 0;
}

