#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STATIONS 2   // Number of washing stations
#define CARS 6       // Total cars arriving

sem_t wash_stations;      // Semaphore for available washing stations
pthread_mutex_t mutex;    // Mutex to optionally track queue length
int queue_length = 0;     // Optional: track cars waiting

void* car(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    queue_length++; // Car joins the queue
    printf("Car %d arrived. Queue length: %d\n", id, queue_length);
    pthread_mutex_unlock(&mutex);

    sem_wait(&wash_stations); // Wait for a free washing station

    pthread_mutex_lock(&mutex);
    queue_length--; // Car leaves queue
    printf("Car %d is being washed. Queue length: %d\n", id, queue_length);
    pthread_mutex_unlock(&mutex);

    sleep(3); // Simulate car wash for 3 seconds
    printf("Car %d finished washing and left.\n", id);

    sem_post(&wash_stations); // Free the washing station
    return NULL;
}

int main() {
    pthread_t cars[CARS];
    int ids[CARS];

    sem_init(&wash_stations, 0, STATIONS); // Initialize semaphore
    pthread_mutex_init(&mutex, NULL);      // Initialize mutex

    // Create car threads
    for(int i = 0; i < CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
    }

    // Wait for all cars to finish
    for(int i = 0; i < CARS; i++)
        pthread_join(cars[i], NULL);

    // Cleanup
    sem_destroy(&wash_stations);
    pthread_mutex_destroy(&mutex);

    return 0;
}
