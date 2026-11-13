/*
 * Topic 1 - Q2(a): Bounded Buffer Problem (Semaphore Solution)
 *
 * 5 producers x 20 iterations = 100 items produced.
 * 10 consumers x 10 iterations = 100 items consumed.
 * Buffer size = 10. Each item holds (producer_pid, iteration_number).
 * Uses POSIX named semaphores (works on both macOS and Linux) and mmap shared memory.
 */

#include <fcntl.h>
#include <semaphore.h>
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
} SharedBuffer;

int main(void) {
    SharedBuffer *sb = mmap(NULL, sizeof(SharedBuffer),
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANON, -1, 0);
    if (sb == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    sb->in = 0;
    sb->out = 0;

    sem_unlink("/bb_empty");
    sem_unlink("/bb_full");
    sem_unlink("/bb_mutex");

    sem_t *empty = sem_open("/bb_empty", O_CREAT | O_EXCL, 0644, BUFFER_SIZE);
    sem_t *full  = sem_open("/bb_full",  O_CREAT | O_EXCL, 0644, 0);
    sem_t *mutex = sem_open("/bb_mutex", O_CREAT | O_EXCL, 0644, 1);

    for (int p = 0; p < NUM_PRODUCERS; p++) {
        if (fork() == 0) {
            int my_pid = (int)getpid();
            for (int i = 1; i <= PROD_ITERS; i++) {
                sem_wait(empty);
                sem_wait(mutex);

                sb->buf[sb->in].pid = my_pid;
                sb->buf[sb->in].iter = i;
                sb->in = (sb->in + 1) % BUFFER_SIZE;

                sem_post(mutex);
                sem_post(full);
            }
            exit(0);
        }
    }

    for (int c = 0; c < NUM_CONSUMERS; c++) {
        if (fork() == 0) {
            int my_pid = (int)getpid();
            for (int i = 1; i <= CONS_ITERS; i++) {
                sem_wait(full);
                sem_wait(mutex);

                Item item = sb->buf[sb->out];
                sb->out = (sb->out + 1) % BUFFER_SIZE;
                printf("Consumer %d read: (Producer PID=%d, Iter=%d)\n",
                       my_pid, item.pid, item.iter);

                sem_post(mutex);
                sem_post(empty);
            }
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PRODUCERS + NUM_CONSUMERS; i++) {
        wait(NULL);
    }

    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/bb_empty");
    sem_unlink("/bb_full");
    sem_unlink("/bb_mutex");
    munmap(sb, sizeof(SharedBuffer));
    return 0;
}

