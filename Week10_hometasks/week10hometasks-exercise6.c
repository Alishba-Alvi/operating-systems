#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_CARS 3    // Maximum cars allowed on the bridge at once
#define TOTAL_CARS 10 // Total cars trying to cross

sem_t bridge;           // Semaphore for bridge capacity
pthread_mutex_t mutex;  // Mutex for safe printing

void* car(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    printf("Car %d is waiting to cross the bridge.\n", id);
    pthread_mutex_unlock(&mutex);

    sem_wait(&bridge); // Wait for a free spot on the bridge

    pthread_mutex_lock(&mutex);
    printf("Car %d is crossing the bridge.\n", id);
    pthread_mutex_unlock(&mutex);

    sleep(1 + rand() % 3); // Random crossing time 1-3 seconds

    pthread_mutex_lock(&mutex);
    printf("Car %d has crossed the bridge.\n", id);
    pthread_mutex_unlock(&mutex);

    sem_post(&bridge); // Leave the bridge
    return NULL;
}

int main() {
    pthread_t cars[TOTAL_CARS];
    int ids[TOTAL_CARS];

    srand(time(NULL)); // Seed for random numbers

    sem_init(&bridge, 0, MAX_CARS);       // Initialize semaphore with max cars
    pthread_mutex_init(&mutex, NULL);     // Initialize mutex

    // Create car threads
    for(int i = 0; i < TOTAL_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
    }

    // Wait for all cars to finish crossing
    for(int i = 0; i < TOTAL_CARS; i++)
        pthread_join(cars[i], NULL);

    // Cleanup
    sem_destroy(&bridge);
    pthread_mutex_destroy(&mutex);

    return 0;
}
