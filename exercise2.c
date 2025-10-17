#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* check_prime(void* arg) {
    int n = *(int*)arg;
    int* result = malloc(sizeof(int));
    *result = 1;

    if (n <= 1) *result = 0;
    else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                *result = 0;
                break;
            }
        }
    }

    return result;
}

int main() {
    pthread_t thread;
    int n;
    void* result;

    printf("Enter a number: ");
    scanf("%d", &n);

    pthread_create(&thread, NULL, check_prime, &n);
    pthread_join(thread, &result);

    if (*(int*)result)
        printf("%d is a prime number.\n", n);
    else
        printf("%d is not a prime number.\n", n);

    free(result);
    return 0;
}
