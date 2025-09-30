/*
============================================================================
Name : 32a.c
Author : Parag Piprewar
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 1st October 2025
============================================================================
*/

//a. rewrite the ticket number creation program using semaphore

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
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
    key_t sem_key = ftok(".", 'S');
    key_t shm_key = ftok(".", 'M');

    int semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    int shmid = shmget(shm_key, sizeof(int), 0666 | IPC_CREAT);

    // Initialize semaphore to 1
    union semun sem_attr;
    sem_attr.val = 1;
    semctl(semid, 0, SETVAL, sem_attr);

    int *ticket = (int *)shmat(shmid, NULL, 0);
    *ticket = 0;

    for (int i = 0; i < 5; i++) { // simulate multiple ticket generations
        sem_wait(semid); // enter critical section
        (*ticket)++;
        printf("Ticket number: %d\n", *ticket);
        sem_signal(semid); // exit critical section
        sleep(1);
    }

    shmdt(ticket);
    // Optional: remove shm and semaphore at the end
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem32$ gcc 32a.c -o 32a ; ./32a
Ticket number: 1
Ticket number: 2
Ticket number: 3
Ticket number: 4
Ticket number: 5

*/
