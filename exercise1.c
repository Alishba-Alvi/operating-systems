#include <stdio.h>
#include <pthread.h>

void* print_message(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d: Hello from thread %d!\n", id, id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3];

    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, print_message, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads completed.\n");
    return 0;
}
