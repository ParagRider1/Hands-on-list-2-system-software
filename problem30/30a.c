/*
============================================================================
Name : 30a.c
Author : Parag Piprewar
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory


Date: 1st October 2025
============================================================================
*/

//a. write some data to the shared memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key;
    int shmid;
    char *shm_ptr;

    // Generate key
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create shared memory
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created. ID: %d\n", shmid);

    // Attach and write
    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    strcpy(shm_ptr, "Hello, this is shared memory!");
    printf("Data written: %s\n", shm_ptr);

    // Detach
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("Detached after writing.\n");
    return 0;
}







/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem30$ gcc 30a.c -o 30a ; ./30a
Shared memory created. ID: 524322
Data written: Hello, this is shared memory!
Detached after writing.

*/