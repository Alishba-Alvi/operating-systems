/* 
Name: Alishba Riasat
Reg No: 23-NTU-CS-1135
Task 4: Thread Return Values 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* compute_factorial (void* arg) {
    int n = *(int*)arg;
    long long*result =  malloc(sizeof(long long));
    if (!result) pthread_exit(NULL);
    *result = 1;
    for (int i=2; i<=n; i++) {
        *result= (*result) * i;
    }
    // return pointer to heap memory
    return (void*)result;
}

int main(){
    pthread_t tid;
    int number;

    printf("Enter a non-negative integer: ");
    if (scanf("%d", &number) !=1 || number <0) {
        printf("Invalid Input. \n");
        return 1;
    }

    pthread_create(&tid, NULL, compute_factorial, &number);
    void* ret;
    pthread_join(tid, &ret);
    if (ret != NULL) {
        long long* factorial = (long long*)ret;
        printf("Factorial of %d is: %lld\n", number, *factorial);
        free (factorial);
    }
    else {
        printf("Thread returned NULL.\n");
    }
    return 0;
}