/*
 * Bounded buffer: 5 producers (20 iters), 10 consumers (10 iters), buffer size 10.
 * Semaphore solution.
 */

#include <fcntl.h>
#include <semaphore.h>
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
    int in, out;
} Buf;

int main(void) {
    Buf *buf = mmap(NULL, sizeof(Buf), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    buf->in = 0;
    buf->out = 0;

    sem_unlink("/s_mtx");
    sem_unlink("/s_emp");
    sem_unlink("/s_ful");

    sem_t *mtx = sem_open("/s_mtx", O_CREAT, 0644, 1);
    sem_t *emp = sem_open("/s_emp", O_CREAT, 0644, N);
    sem_t *ful = sem_open("/s_ful", O_CREAT, 0644, 0);

    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            int p = getpid();
            for (int k = 1; k <= 20; k++) {
                sem_wait(emp);
                sem_wait(mtx);
                buf->b[buf->in].pid = p;
                buf->b[buf->in].iter = k;
                buf->in = (buf->in + 1) % N;
                sem_post(mtx);
                sem_post(ful);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (fork() == 0) {
            int p = getpid();
            for (int k = 1; k <= 10; k++) {
                sem_wait(ful);
                sem_wait(mtx);
                Item it = buf->b[buf->out];
                buf->out = (buf->out + 1) % N;
                printf("Consumer PID %d read: Producer PID=%d, Iter=%d\n", p, it.pid, it.iter);
                sem_post(mtx);
                sem_post(emp);
            }
            exit(0);
        }
    }

    for (int i = 0; i < 15; i++) wait(NULL);

    sem_close(mtx);
    sem_close(emp);
    sem_close(ful);
    sem_unlink("/s_mtx");
    sem_unlink("/s_emp");
    sem_unlink("/s_ful");
    munmap(buf, sizeof(Buf));
    return 0;
}

