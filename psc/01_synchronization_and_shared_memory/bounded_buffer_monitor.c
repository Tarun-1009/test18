/*
 * Topic 1 - Q2(b): Bounded Buffer Problem (Monitor Solution)
 *
 * 5 producers x 20 iterations = 100 items produced.
 * 10 consumers x 10 iterations = 100 items consumed.
 * Buffer size = 10. Monitor implemented with a process-shared pthread mutex
 * and two condition variables (not_full, not_empty) inside mmap shared memory.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 10
#define PROD_ITERS 20
#define CONS_ITERS 10

typedef struct {
    int pid;
    int iter;
} Item;

typedef struct {
    Item buf[BUFFER_SIZE];
    int in;
    int out;
    int count;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Monitor;

void monitor_init(Monitor *m) {
    m->in = 0;
    m->out = 0;
    m->count = 0;

    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&m->lock, &mattr);
    pthread_mutexattr_destroy(&mattr);

    pthread_condattr_t cattr;
    pthread_condattr_init(&cattr);
    pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&m->not_full, &cattr);
    pthread_cond_init(&m->not_empty, &cattr);
    pthread_condattr_destroy(&cattr);
}

void monitor_insert(Monitor *m, Item item) {
    pthread_mutex_lock(&m->lock);
    while (m->count == BUFFER_SIZE) {
        pthread_cond_wait(&m->not_full, &m->lock);
    }
    m->buf[m->in] = item;
    m->in = (m->in + 1) % BUFFER_SIZE;
    m->count++;
    pthread_cond_signal(&m->not_empty);
    pthread_mutex_unlock(&m->lock);
}

Item monitor_remove(Monitor *m) {
    pthread_mutex_lock(&m->lock);
    while (m->count == 0) {
        pthread_cond_wait(&m->not_empty, &m->lock);
    }
    Item item = m->buf[m->out];
    m->out = (m->out + 1) % BUFFER_SIZE;
    m->count--;
    pthread_cond_signal(&m->not_full);
    pthread_mutex_unlock(&m->lock);
    return item;
}

int main(void) {
    Monitor *m = mmap(NULL, sizeof(Monitor),
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANON, -1, 0);
    if (m == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    monitor_init(m);

    for (int p = 0; p < NUM_PRODUCERS; p++) {
        if (fork() == 0) {
            int my_pid = (int)getpid();
            for (int i = 1; i <= PROD_ITERS; i++) {
                Item item = {my_pid, i};
                monitor_insert(m, item);
            }
            exit(0);
        }
    }

    for (int c = 0; c < NUM_CONSUMERS; c++) {
        if (fork() == 0) {
            int my_pid = (int)getpid();
            for (int i = 1; i <= CONS_ITERS; i++) {
                Item item = monitor_remove(m);
                printf("Consumer %d read: (Producer PID=%d, Iter=%d)\n",
                       my_pid, item.pid, item.iter);
            }
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PRODUCERS + NUM_CONSUMERS; i++) {
        wait(NULL);
    }

    pthread_mutex_destroy(&m->lock);
    pthread_cond_destroy(&m->not_full);
    pthread_cond_destroy(&m->not_empty);
    munmap(m, sizeof(Monitor));
    return 0;
}

