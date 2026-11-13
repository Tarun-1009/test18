/*
 * Multithreaded Bank Transaction System in C
 *
 * Multiple threads perform deposits, withdrawals, and transfers on a shared
 * account balance array protected by pthread_mutex_t.
 */

#include <pthread.h>
#include <stdio.h>

#define NUM_ACCOUNTS 3
#define NUM_THREADS 3

typedef enum { DEPOSIT, WITHDRAW, TRANSFER } TxType;

typedef struct {
    TxType type;
    int from_acc;
    int to_acc;
    int amount;
} Transaction;

typedef struct {
    int tid;
    const Transaction *txns;
    int count;
    int success;
    int failed;
} WorkerArg;

int balances[NUM_ACCOUNTS] = {1000, 1500, 2000};
pthread_mutex_t bank_mutex = PTHREAD_MUTEX_INITIALIZER;

void *process_transactions(void *arg) {
    WorkerArg *w = (WorkerArg *)arg;
    w->success = 0;
    w->failed = 0;

    for (int i = 0; i < w->count; i++) {
        Transaction tx = w->txns[i];
        pthread_mutex_lock(&bank_mutex);

        if (tx.type == DEPOSIT) {
            balances[tx.to_acc] += tx.amount;
            w->success++;
        } else if (tx.type == WITHDRAW) {
            if (balances[tx.from_acc] >= tx.amount) {
                balances[tx.from_acc] -= tx.amount;
                w->success++;
            } else {
                w->failed++;
            }
        } else if (tx.type == TRANSFER) {
            if (balances[tx.from_acc] >= tx.amount) {
                balances[tx.from_acc] -= tx.amount;
                balances[tx.to_acc] += tx.amount;
                w->success++;
            } else {
                w->failed++;
            }
        }

        pthread_mutex_unlock(&bank_mutex);
    }
    return NULL;
}

int main(void) {
    const Transaction w0[] = {
        {DEPOSIT, -1, 0, 500},
        {WITHDRAW, 1, -1, 300},
        {TRANSFER, 0, 2, 400}
    };
    const Transaction w1[] = {
        {WITHDRAW, 0, -1, 2000},
        {TRANSFER, 2, 1, 500},
        {DEPOSIT, -1, 1, 200}
    };
    const Transaction w2[] = {
        {TRANSFER, 1, 0, 250},
        {WITHDRAW, 2, -1, 1000},
        {DEPOSIT, -1, 2, 100}
    };

    WorkerArg args[NUM_THREADS] = {
        {0, w0, 3, 0, 0},
        {1, w1, 3, 0, 0},
        {2, w2, 3, 0, 0}
    };

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, process_transactions, &args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final Account Balances:\n");
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        printf("  Account %d: %d\n", i, balances[i]);
    }

    printf("\nTransaction Summary:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("  Thread %d: success = %d, failed = %d\n",
               args[i].tid, args[i].success, args[i].failed);
    }
    return 0;
}

