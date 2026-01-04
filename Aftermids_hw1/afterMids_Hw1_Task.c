#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in=0;  
int out=0;  

sem_t emptySlots; 
sem_t fullSlots; 
pthread_mutex_t bufferLock;

// Producer thread function
void* producer(void* arg) {
    int id=*(int*)arg;

    for(int i=0; i<3; i++) {
        int item=id*100 +i;

        sem_wait(&emptySlots); // Wait if buffer is full 
        pthread_mutex_lock(&bufferLock); 

        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n",id,item,in);
        in=(in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&bufferLock); 
        sem_post(&fullSlots); // Signal that buffer has a new item  

        sleep(1);
    }

    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    int id=*(int*)arg;

    for(int i=0; i<3; i++) {
      
        sem_wait(&fullSlots); // Wait if buffer is empty       
        pthread_mutex_lock(&bufferLock);

        int item=buffer[out];
        printf("Consumer %d consumed item %d from position %d\n",id,item,out);
        out=(out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&bufferLock); 
        
        sem_post(&emptySlots); // Signal that buffer has an empty slot          

        sleep(2); 
    }

    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int ids[2]={1, 2};

    sem_init(&emptySlots, 0, BUFFER_SIZE); // Initially, all slots empty
    sem_init(&fullSlots, 0, 0); // No slots full initially
    pthread_mutex_init(&bufferLock, NULL);

    // Create producer and consumer threads
    for(int i=0; i<2; i++) {
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    // Wait for all threads to finish
    for(int i = 0; i<2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }


    // Cleanup
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&bufferLock);

    return 0;
}
