/*
============================================================================
Name : 32b.c
Author : Parag Piprewar
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore

Date: 1st October 2025
============================================================================
*/

//b. protect shared memory from concurrent write access

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int semid) { struct sembuf sb = {0, -1, 0}; semop(semid, &sb, 1);}
void sem_signal(int semid) { struct sembuf sb = {0, 1, 0}; semop(semid, &sb, 1); }

int main() {
    key_t sem_key = ftok(".", 'A');
    key_t shm_key = ftok(".", 'B');

    int semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    int shmid = shmget(shm_key, 1024, 0666 | IPC_CREAT);

    union semun sem_attr;
    sem_attr.val = 1;
    semctl(semid, 0, SETVAL, sem_attr);

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);

    for (int i = 0; i < 5; i++) {
        sem_wait(semid);
        sprintf(shm_ptr, "Process %d writing iteration %d", getpid(), i+1);
        printf("%s\n", shm_ptr);
        sem_signal(semid);
        sleep(1);
    }

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem32$ gcc 32b.c -o 32b ; ./32b
Process 58408 writing iteration 1
Process 58408 writing iteration 2
Process 58408 writing iteration 3
Process 58408 writing iteration 4
Process 58408 writing iteration 5

*/