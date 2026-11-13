/*
 * Bounded buffer: 5 producers (20 iters), 10 consumers (10 iters), buffer size 10.
 * Monitor solution using process-shared mutex and condition variables.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 10

typedef struct {
    int pid;
    int iter;
} Item;

typedef struct {
    Item b[N];
    int in, out, cnt;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Mon;

Mon *m;

void put(Item it) {
    pthread_mutex_lock(&m->lock);
    while (m->cnt == N) pthread_cond_wait(&m->not_full, &m->lock);
    m->b[m->in] = it;
    m->in = (m->in + 1) % N;
    m->cnt++;
    pthread_cond_signal(&m->not_empty);
    pthread_mutex_unlock(&m->lock);
}

Item get(void) {
    pthread_mutex_lock(&m->lock);
    while (m->cnt == 0) pthread_cond_wait(&m->not_empty, &m->lock);
    Item it = m->b[m->out];
    m->out = (m->out + 1) % N;
    m->cnt--;
    pthread_cond_signal(&m->not_full);
    pthread_mutex_unlock(&m->lock);
    return it;
}

int main(void) {
    m = mmap(NULL, sizeof(Mon), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    m->in = m->out = m->cnt = 0;

    pthread_mutexattr_t ma;
    pthread_mutexattr_init(&ma);
    pthread_mutexattr_setpshared(&ma, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&m->lock, &ma);

    pthread_condattr_t ca;
    pthread_condattr_init(&ca);
    pthread_condattr_setpshared(&ca, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&m->not_full, &ca);
    pthread_cond_init(&m->not_empty, &ca);

    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            int p = getpid();
            for (int k = 1; k <= 20; k++) {
                Item it = {p, k};
                put(it);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (fork() == 0) {
            int p = getpid();
            for (int k = 1; k <= 10; k++) {
                Item it = get();
                printf("Consumer PID %d read: Producer PID=%d, Iter=%d\n", p, it.pid, it.iter);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 15; i++) wait(NULL);

    pthread_mutex_destroy(&m->lock);
    pthread_cond_destroy(&m->not_full);
    pthread_cond_destroy(&m->not_empty);
    munmap(m, sizeof(Mon));
    return 0;
}

