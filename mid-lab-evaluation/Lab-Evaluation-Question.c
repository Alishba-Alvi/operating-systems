/*
Name: Alishba Riasat
Reg.No: 23-NTU-CS-1135
Question: Write a C program that uses threads to perform operations on shared variables:
1.  Create two global variables:
  initialized to 0
  initialized to 0
2.  Create 3 threads:
    Thread 1: Adds all of the numbers between 1 to 100 to 100 times
   Thread 2: Adds all of the numbers between 101 to 200 to 100 times
   Thread 3: Adds all of the numbers between 201 to 300 to 100 times
3.  Use mutex to protect access to both shared variables
4.  Each thread prints when it starts and finishes
5.  Main thread prints final results:
  Total sum (should be 45150, which is sum of 1 to 300)   Total count (should be 300) */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int total_sum=0; 
int total_count=0; 

pthread_mutex_t mutex; 

void* calculate_sum(void* arg){
  int thread_id = *(int*)arg;
  int start;
  int end;

  if(thread_id==1){
    start=1;
    end=100; 
  }
  else if(thread_id==2){ 
    start=101;
    end=200;
  }
  else{ 
    start=201; 
    end=300; 
  }

  printf("Thread %d: Starting calculation for range %d to %d\n", thread_id, start, end);

  int local_sum = 0;

  for(int repeat=0;repeat<100;repeat++){
    for(int i=start;i<=end;i++){
      local_sum+=i;
    }
  }

  local_sum/=100;

  pthread_mutex_lock(&mutex);
  total_sum+=local_sum;
  total_count+=(end-start+1);
  pthread_mutex_unlock(&mutex);

  printf("Thread %d: Finished Calculation.\n", thread_id);
  return NULL;
}

int main(){
  pthread_t t1,t2,t3;
  int thread_ids[3]={1,2,3};

  pthread_mutex_init(&mutex, NULL); 

  pthread_create(&t1,NULL,calculate_sum,&thread_ids[0]);
  pthread_create(&t2,NULL,calculate_sum,&thread_ids[1]);
  pthread_create(&t3,NULL,calculate_sum,&thread_ids[2]);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);

  pthread_mutex_destroy(&mutex); 

  printf("\nAll threads finished.\n");
  printf("Final Total Sum: %d\n", total_sum);
  printf("Final Total Count: %d\n", total_count);

  return 0;
}

/*
Final Remark:
In this program, I created two shared variables, total_sum and total_count, both starting at 0. 
I made three threads. Each thread adds numbers in its range (1-100, 101-200, 201-300) 
and repeats the addition 100 times. 

I used a mutex to make sure only one thread changes the shared variables at a time. 
Each thread prints messages when it starts and finishes. 
The main thread waits for all threads to finish and then prints the final total sum (45150) 
and total count (300).

Basically, This program shows how to use threads safely to work with shared data.
*/
