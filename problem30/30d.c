/*
============================================================================
Name : 30d.c
Author : Parag Piprewar
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory


Date: 1st October 2025
============================================================================
*/

//d. remove the shared memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;

    key = ftok(".", 'S');
    if (key == -1) { perror("ftok"); exit(EXIT_FAILURE); }

    shmid = shmget(key, 1024, 0666);
    if (shmid == -1) { perror("shmget"); exit(EXIT_FAILURE); }

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl - IPC_RMID");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}



/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem30$ gcc 30d.c -o 30d ; ./30d
Shared memory removed successfully.

*/