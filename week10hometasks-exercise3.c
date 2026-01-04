#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define K 4       // Number of computers
#define STUDENTS 8 // Total students trying to use the lab

sem_t computers;   // Counting semaphore for available computers
pthread_mutex_t mutex;  // Mutex for protecting shared array
int lab[K];      // Array to track which student is using which computer (0 = free)

void* student(void* arg) {
    int id = *(int*)arg;
    int comp_index = -1;

    printf("Student %d is waiting for a computer...\n", id);
    sem_wait(&computers); // Wait for an available computer

    // Find a free computer
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < K; i++) {
        if(lab[i] == 0) { // Computer free
            lab[i] = id;  // Assign student to computer
            comp_index = i;
            break;
        }
    }
    printf("Student %d started using computer %d.\n", id, comp_index + 1);
    pthread_mutex_unlock(&mutex);

    sleep(1 + rand() % 3); // Simulate lab usage 1-3 seconds

    // Free the computer
    pthread_mutex_lock(&mutex);
    lab[comp_index] = 0; // Mark computer as free
    printf("Student %d finished using computer %d.\n", id, comp_index + 1);
    pthread_mutex_unlock(&mutex);

    sem_post(&computers); // Release a computer slot
    return NULL;
}

int main() {
    pthread_t students[STUDENTS];
    int ids[STUDENTS];

    srand(time(NULL)); // Seed random numbers

    // Initialize semaphore and mutex
    sem_init(&computers, 0, K);
    pthread_mutex_init(&mutex, NULL);

    // Initialize lab array to 0 (all computers free)
    for(int i = 0; i < K; i++)
        lab[i] = 0;

    // Create student threads
    for(int i = 0; i < STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&students[i], NULL, student, &ids[i]);
    }

    // Wait for all students to finish
    for(int i = 0; i < STUDENTS; i++)
        pthread_join(students[i], NULL);

    // Cleanup
    sem_destroy(&computers);
    pthread_mutex_destroy(&mutex);

    return 0;
}
