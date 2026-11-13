/*
 * Readers-Writers Problem (Readers Priority)
 *
 * Multiple readers can read concurrently; writers get exclusive access.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared_data = 0;
int read_count = 0;
pthread_mutex_t rc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&rc_mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&rw_mutex);
        }
        pthread_mutex_unlock(&rc_mutex);

        printf("Reader %d read shared_data = %d\n", id, shared_data);
        usleep(30000);

        pthread_mutex_lock(&rc_mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&rw_mutex);
        }
        pthread_mutex_unlock(&rc_mutex);
        usleep(30000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&rw_mutex);
        shared_data += 10;
        printf("Writer %d updated shared_data = %d\n", id, shared_data);
        usleep(40000);
        pthread_mutex_unlock(&rw_mutex);
        usleep(40000);
    }
    return NULL;
}

int main(void) {
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3};
    int w_id[2] = {1, 2};

    for (int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    return 0;
}

