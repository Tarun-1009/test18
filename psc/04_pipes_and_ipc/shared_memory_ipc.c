/*
 * POSIX Shared Memory IPC (shm_open + mmap)
 *
 * Parent writes a message into POSIX shared memory; child reads it.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/os_lab_shm_demo"
#define SHM_SIZE 256

int main(void) {
    shm_unlink(SHM_NAME);
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        perror("shm_open");
        return 1;
    }
    ftruncate(fd, SHM_SIZE);

    char *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    snprintf(ptr, SHM_SIZE, "Message from Parent (PID %d)", getpid());

    if (fork() == 0) {
        printf("Child (PID %d) read: %s\n", getpid(), ptr);
        munmap(ptr, SHM_SIZE);
        close(fd);
        return 0;
    }

    wait(NULL);
    munmap(ptr, SHM_SIZE);
    close(fd);
    shm_unlink(SHM_NAME);
    return 0;
}

