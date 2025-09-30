/*
============================================================================
Name : 32d1.c
Author : Parag Piprewar
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 1st October 2025
============================================================================
*/

//Counting Semaphore (Use, but do not remove)


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int semid) { 
    struct sembuf sb = {0, -1, 0}; 
    semop(semid, &sb, 1); 
}

void sem_signal(int semid) { 
    struct sembuf sb = {0, 1, 0}; 
    semop(semid, &sb, 1); 
}

int main() {
    key_t sem_key = ftok(".", 'C');
    if (sem_key == -1) { perror("ftok"); exit(EXIT_FAILURE); }

    int semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (semid == -1) { perror("semget"); exit(EXIT_FAILURE); }

    // Initialize counting semaphore to 2 (two resources)
    union semun sem_attr;
    sem_attr.val = 2;
    semctl(semid, 0, SETVAL, sem_attr);

    printf("Counting semaphore created. ID: %d, initial value: 2\n", semid);

    for (int i = 0; i < 5; i++) {
        sem_wait(semid);
        printf("Process %d acquired a resource\n", getpid());
        sleep(2); // simulate resource usage
        sem_signal(semid);
        printf("Process %d released a resource\n", getpid());
        sleep(1);
    }

    printf("Counting semaphore usage complete. Do NOT remove it yet.\n");

    return 0;
}


/*
output


/*

output


parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem32$ gcc 32d1.c -o 32d1 ; ./32d1
Counting semaphore created. ID: 5, initial value: 2
Process 58970 acquired a resource
Process 58970 released a resource
Process 58970 acquired a resource
Process 58970 released a resource
Process 58970 acquired a resource
Process 58970 released a resource
Process 58970 acquired a resource
Process 58970 released a resource
Process 58970 acquired a resource
Process 58970 released a resource
Counting semaphore usage complete. Do NOT remove it yet.


parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem32$ gcc 32d2.c -o 32d2 ; ./32d2
Semaphore removed successfully.


*/





*/