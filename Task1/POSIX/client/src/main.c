#include "../include/shm_client.h"

int main() {
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    char *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(1);
    }

    printf("Received message from server: %s\n", shared_memory);

    strcpy(shared_memory, "Hello!");

    munmap(shared_memory, SHARED_MEMORY_SIZE);
    close(shm_fd);

    return 0;
}
