/* 
Name: Alishba Riasat
Reg No: 23-NTU-CS-1135
Task 2: Personalized Greeting Thread 
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* greet(void* arg) {
    char* name = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    return NULL;
}

int main(){
    pthread_t tid;
    char name[50];

    printf("Enter your name: ");
    if(scanf("%49s",name) !=1){
        printf("Input Error.\n");
        return 1;
    }

    printf("Main thread: Waiting for greeting...\n");
    pthread_create(&tid, NULL, greet, name);
    pthread_join(tid, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}