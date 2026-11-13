/*
 * Multithreaded bank transaction simulation in C.
 * Shared balance array protected by pthread_mutex_t.
 * Tracks successful and failed transactions per thread.
 */

#include <pthread.h>
#include <stdio.h>

#define ACCOUNTS 3
#define THREADS 3

typedef struct {
    int type; /* 1: deposit, 2: withdraw, 3: transfer */
    int from;
    int to;
    int amt;
} Tx;

typedef struct {
    int id;
    Tx *list;
    int count;
    int ok;
    int fl;
} Worker;

int bal[ACCOUNTS] = {1000, 1500, 2000};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *f_tx(void *arg) {
    Worker *w = (Worker *)arg;
    w->ok = 0;
    w->fl = 0;

    for (int i = 0; i < w->count; i++) {
        Tx t = w->list[i];
        pthread_mutex_lock(&mtx);
        if (t.type == 1) { /* deposit */
            bal[t.to] += t.amt;
            w->ok++;
        } else if (t.type == 2) { /* withdraw */
            if (bal[t.from] >= t.amt) {
                bal[t.from] -= t.amt;
                w->ok++;
            } else {
                w->fl++;
            }
        } else if (t.type == 3) { /* transfer */
            if (bal[t.from] >= t.amt) {
                bal[t.from] -= t.amt;
                bal[t.to] += t.amt;
                w->ok++;
            } else {
                w->fl++;
            }
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    Tx t0[] = {{1, -1, 0, 500}, {2, 1, -1, 300}, {3, 0, 2, 400}};
    Tx t1[] = {{2, 0, -1, 3000}, {3, 2, 1, 500}, {1, -1, 1, 200}};
    Tx t2[] = {{3, 1, 0, 250}, {2, 2, -1, 1000}, {1, -1, 2, 100}};

    Worker w[THREADS] = {
        {1, t0, 3, 0, 0},
        {2, t1, 3, 0, 0},
        {3, t2, 3, 0, 0}
    };

    pthread_t th[THREADS];
    for (int i = 0; i < THREADS; i++) pthread_create(&th[i], NULL, f_tx, &w[i]);
    for (int i = 0; i < THREADS; i++) pthread_join(th[i], NULL);

    printf("Final Account Balances:\n");
    for (int i = 0; i < ACCOUNTS; i++) printf("  Account %d: %d\n", i, bal[i]);

    printf("\nTransaction Summary:\n");
    for (int i = 0; i < THREADS; i++) {
        printf("  Thread %d: success = %d, failed = %d\n", w[i].id, w[i].ok, w[i].fl);
    }
    return 0;
}

