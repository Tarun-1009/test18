#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ACCOUNTS 3
#define THREADS 3

// Assignment 6 - Q5: Multithreaded Bank System
int bal[ACCOUNTS] = {1000, 1000, 1000};
pthread_mutex_t lock[ACCOUNTS];
int success_ops[THREADS], fail_ops[THREADS];

void *bank_ops(void *arg) {
    long id = (long)arg;
    for (int i = 0; i < 5; i++) {
        int acc = rand() % ACCOUNTS;
        int amt = 100;
        pthread_mutex_lock(&lock[acc]);
        if (bal[acc] >= amt) {
            bal[acc] -= amt;
            success_ops[id]++;
        } else {
            fail_ops[id]++;
        }
        pthread_mutex_unlock(&lock[acc]);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t[THREADS];
    for (int i = 0; i < ACCOUNTS; i++) pthread_mutex_init(&lock[i], NULL);

    for (long i = 0; i < THREADS; i++) pthread_create(&t[i], NULL, bank_ops, (void *)i);
    for (int i = 0; i < THREADS; i++) pthread_join(t[i], NULL);

    printf("Final Account Balances:\n");
    for (int i = 0; i < ACCOUNTS; i++) printf("Account %d: $%d\n", i, bal[i]);

    printf("Transaction Summary:\n");
    for (int i = 0; i < THREADS; i++)
        printf("Thread %d: Success = %d, Failed = %d\n", i, success_ops[i], fail_ops[i]);

    return 0;
}
