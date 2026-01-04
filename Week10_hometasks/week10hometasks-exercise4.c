#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define WORKERS 3  // Number of worker threads available
#define TASKS 10   // Total tasks to process

sem_t available_workers; // Semaphore to track free workers

void* task(void* arg) {
    int id = *(int*)arg;

    printf("Task %d is waiting for a worker...\n", id);
    sem_wait(&available_workers); // Wait for a free worker

    printf("Task %d is being processed by a worker.\n", id);
    sleep(1 + rand() % 2); // Simulate task execution 1-2 seconds
    printf("Task %d completed.\n", id);

    sem_post(&available_workers); // Release the worker
    return NULL;
}

int main() {
    pthread_t tasks[TASKS];
    int ids[TASKS];

    srand(time(NULL)); // Seed random numbers

    sem_init(&available_workers, 0, WORKERS); // Initialize semaphore with 3 workers

    // Create threads for tasks
    for(int i = 0; i < TASKS; i++) {
        ids[i] = i + 1;
        pthread_create(&tasks[i], NULL, task, &ids[i]);
    }

    // Wait for all tasks to finish
    for(int i = 0; i < TASKS; i++)
        pthread_join(tasks[i], NULL);

    sem_destroy(&available_workers); // Cleanup

    return 0;
}
