/*
 * Dining Philosophers Problem (Deadlock-Free Using Asymmetric Fork Pickup)
 *
 * 5 philosophers, 5 forks (mutexes). Even-numbered philosophers pick up left
 * fork first; odd-numbered pick up right fork first to break circular wait.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHIL 5
#define ROUNDS 2

pthread_mutex_t forks[NUM_PHIL];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHIL;

    for (int r = 1; r <= ROUNDS; r++) {
        printf("Philosopher %d is thinking (round %d)\n", id, r);
        usleep(50000);

        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        printf("Philosopher %d is eating (round %d)\n", id, r);
        usleep(50000);

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_PHIL];
    int ids[NUM_PHIL];

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}

