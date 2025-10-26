/* 
Name: Alishba Riasat
Reg No: 23-NTU-CS-1135
Task 5: Struct‑Based Thread Communication 
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

typedef struct {
    Student s;
    int index;
} ThreadArg;

void* student_worker(void* arg) {
    ThreadArg* ta = (ThreadArg*)arg;
    Student st = ta->s;
    printf("Thread %d: Student ID: %d, Name: %s, GPA: %.2f\n", ta->index, st.student_id, st.name, st.gpa);
    if (st.gpa >= 3.5f) {
        printf("Thread %d: %s made the Dean's List.\n", ta->index, st.name);
    } else {
        printf("Thread %d: %s did NOT make the Dean's List.\n", ta->index, st.name);
    }
    return NULL;
}

int main() {
    pthread_t tid[3];
    ThreadArg args[3];

    args[0].s.student_id= 101; strcpy(args[0].s.name, "Alishba");
    args[0].s.gpa= 3.8f; args[0].index= 1;

    args[1].s.student_id= 102; strcpy(args[1].s.name, "Zara");
    args[1].s.gpa= 3.3f; args[1].index= 2;

    args[2].s.student_id= 103; strcpy(args[2].s.name, "Fatima");
    args[2].s.gpa= 3.6f; args[2].index= 3;

    // Create threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, student_worker, &args[i]);
    }

    // Wait for threads
    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    // Count Dean's list
    int count = 0;
    for (int i = 0; i < 3; i++) if (args[i].s.gpa >= 3.5f) count++;

    printf("Main: Total students on Dean's List = %d out of 3\n", count);

    return 0;
}
