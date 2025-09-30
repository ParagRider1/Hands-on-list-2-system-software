/*
============================================================================
Name : 31a.c
Author : Parag Piprewar
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore

Date: 1st October 2025
============================================================================
*/



//binary semaphore

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int semid;
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem_attr;

    // Generate key
    key = ftok(".", 'B');
    if (key == -1) { perror("ftok"); exit(EXIT_FAILURE); }

    // Create semaphore set with 1 semaphore (binary)
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) { perror("semget"); exit(EXIT_FAILURE); }

    // Initialize semaphore to 1 (binary semaphore)
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl - SETVAL");
        exit(EXIT_FAILURE);
    }

    printf("Binary semaphore created. ID: %d, initial value: 1\n", semid);

    return 0;
}

/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem31$ gcc 31a.c -o 31a ; ./31a
Binary semaphore created. ID: 0, initial value: 1


*/


