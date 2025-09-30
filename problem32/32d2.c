/*
============================================================================
Name : 32d2.c
Author : Parag Piprewar
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 1st October 2025
============================================================================
*/


//Remove Semaphore (Safe Removal)

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok(".", 'C'); // same key as counting semaphore
    if (key == -1) { perror("ftok"); exit(EXIT_FAILURE); }

    int semid = semget(key, 1, 0666); // do NOT use IPC_CREAT
    if (semid == -1) {
        perror("semget - semaphore may not exist");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl - IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore removed successfully.\n");
    return 0;
}


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


