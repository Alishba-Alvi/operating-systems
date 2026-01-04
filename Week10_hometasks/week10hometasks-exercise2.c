#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_DOWNLOADS 3  // Maximum concurrent downloads
#define TOTAL_FILES 8    // Total files to download

sem_t download_slots;   // Counting semaphore for available download slots

void* download(void* arg) {
    int id = *(int*)arg;

    printf("File %d is waiting to download...\n", id);
    sem_wait(&download_slots); // Try to acquire a download slot

    printf("File %d started downloading.\n", id);
    sleep(1 + rand() % 5); // Simulate download time 1-5 seconds
    printf("File %d finished downloading.\n", id);

    sem_post(&download_slots); // Release the slot
    return NULL;
}

int main() {
    pthread_t files[TOTAL_FILES];
    int ids[TOTAL_FILES];

    srand(time(NULL)); // Seed random numbers

    sem_init(&download_slots, 0, MAX_DOWNLOADS); // Initialize semaphore with 3 slots

    // Create download threads
    for(int i = 0; i < TOTAL_FILES; i++) {
        ids[i] = i + 1;
        pthread_create(&files[i], NULL, download, &ids[i]);
    }

    // Wait for all downloads to complete
    for(int i = 0; i < TOTAL_FILES; i++)
        pthread_join(files[i], NULL);

    sem_destroy(&download_slots); // Cleanup

    return 0;
}
