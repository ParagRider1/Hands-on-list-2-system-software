/*
============================================================================
Name : 32c.c
Author : Parag Piprewar
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 1st October 2025
============================================================================
*/


//c. protect multiple pseudo resources ( may be two) using counting semaphore

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

void sem_wait(int semid) { struct sembuf sb = {0, -1, 0}; semop(semid, &sb, 1); }
void sem_signal(int semid) { struct sembuf sb = {0, 1, 0}; semop(semid, &sb, 1); }

int main() {
    key_t sem_key = ftok(".", 'C');
    int semid = semget(sem_key, 1, 0666 | IPC_CREAT);

    // Initialize counting semaphore to 2 (two resources)
    union semun sem_attr;
    sem_attr.val = 2;
    semctl(semid, 0, SETVAL, sem_attr);

    for (int i = 0; i < 5; i++) {
        sem_wait(semid); // acquire a resource
        printf("Process %d acquired a resource\n", getpid());
        sleep(2); // simulate resource usage
        sem_signal(semid); // release resource
        printf("Process %d released a resource\n", getpid());
        sleep(1);
    }

    semctl(semid, 0, IPC_RMID); // remove semaphore
    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem32$ gcc 32c.c -o 32c ; ./32c
Process 58487 acquired a resource
Process 58487 released a resource
Process 58487 acquired a resource
Process 58487 released a resource
Process 58487 acquired a resource
Process 58487 released a resource
Process 58487 acquired a resource
Process 58487 released a resource
Process 58487 acquired a resource
Process 58487 released a resource

*/