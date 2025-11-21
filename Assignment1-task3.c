/* 
Name: Alishba Riasat
Reg No: 23-NTU-CS-1135
Task 3: Number Info Thread
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* number_info(void* arg) {
    int n = *(int*) arg;
    printf("Thread: Number = %d\n", n);
    printf("Thread: Square = %d\n", n*n);
    printf("Thread: Cube = %d\n", n*n*n);
    return NULL;
}

int main() {
    pthread_t tid;
    int number;

    printf("Enter an integer: ");
    if (scanf("%d", &number) !=1 ) {
        printf("Invalid Input. \n");
        return 1;
    }
    pthread_create(&tid, NULL, number_info, &number);
    pthread_join(tid, NULL);
    printf("Main thread: Work Completed.\n");
    return 0;
}