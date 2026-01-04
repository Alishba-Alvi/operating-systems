#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5     // Total hotel rooms
#define PEOPLE 10 // Total people trying to enter

sem_t rooms;           // Counting semaphore for available rooms
pthread_mutex_t mutex; // Mutex for updating occupancy
int occupied = 0;      // Current rooms occupied

void* person(void* arg) {
    int id = *(int*)arg;

    printf("Person %d is waiting for a room...\n", id);
    sem_wait(&rooms); // Try to get a room

    pthread_mutex_lock(&mutex);
    occupied++; // Increment occupied rooms
    printf("Person %d entered. Rooms occupied: %d/%d\n", id, occupied, N);
    pthread_mutex_unlock(&mutex);

    sleep(1 + rand() % 3); // Stay for 1-3 seconds

    pthread_mutex_lock(&mutex);
    occupied--; // Free the room
    printf("Person %d left. Rooms occupied: %d/%d\n", id, occupied, N);
    pthread_mutex_unlock(&mutex);

    sem_post(&rooms); // Release the room
    return NULL;
}

int main() {
    pthread_t people[PEOPLE];
    int ids[PEOPLE];

    srand(time(NULL)); // Seed random numbers

    sem_init(&rooms, 0, N);         // Initialize semaphore with N rooms
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create threads for people
    for(int i = 0; i < PEOPLE; i++) {
        ids[i] = i + 1;
        pthread_create(&people[i], NULL, person, &ids[i]);
    }

    // Wait for all people to finish
    for(int i = 0; i < PEOPLE; i++)
        pthread_join(people[i], NULL);

    // Cleanup
    sem_destroy(&rooms);
    pthread_mutex_destroy(&mutex);

    return 0;
}
