/* 
Name: Alishba Riasat
Reg No: 23-NTU-CS-1135
Task 1: Thread Information Display
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_work(void* arg) {
int thread_no = *(int*) arg;
printf ("Thread %d: pthread_self()= %lu\n", thread_no, pthread_self());
if (thread_no == 1) {
    printf("Thread %d: I am the 1st thread.\n", thread_no);
}
else if(thread_no == 2) {
    printf("Thread %d: I am the 2nd thread.\n", thread_no);
}
else if(thread_no == 3) {
    printf("Thread %d: I am the 3rd thread.\n", thread_no);
}
else{
    printf("Thread %d: I am the %dth thread.\n", thread_no, thread_no);
}

int sleeptime = (rand()%3) + 1;
printf("Thread %d: Sleeping for %d seconds...\n", thread_no, sleeptime);
sleep(sleeptime);

printf("Thread %d: Completed and exiting.\n", thread_no);
    return NULL;
}

int main() {
srand(getpid()); //Seed rand with PID
pthread_t threads[5];
int ids[5];

printf("Main: Creating 5 threads...\n");

for(int i=0; i<5; i++){
    ids[i]= i+1;
    pthread_create(&threads[i], NULL, thread_work, &ids[i]);
    usleep(10000); // To avoid the race condition
}
for(int i=0; i<5; i++){
    pthread_join(threads[i], NULL);
}

printf("Main: All threads joined. Exiting.\n");
return 0;
}