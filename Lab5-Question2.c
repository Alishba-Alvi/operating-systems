#include <stdio.h>
#include <pthread.h>

void* print_number(void* arg) {
    float num = *(float*)arg;  // Cast back to float*
    printf("Thread received number: %.2f\n", num);
    printf("Square: %.2f\n", num * num);
    return NULL;
}

int main() {
    pthread_t thread_id;
    float number = 3.5;
    printf("Creating thread with argument: %.2f\n", number);
    pthread_create(&thread_id, NULL, print_number, &number);
    pthread_join(thread_id, NULL);
    printf("Main thread done.\n");
    return 0;
}
