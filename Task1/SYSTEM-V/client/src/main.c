#include "../include/shm_client.h"

int main() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Received message from server: %s\n", shared_memory);

    strcpy(shared_memory, "Hello!");

    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
