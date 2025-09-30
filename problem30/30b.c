/*
============================================================================
Name : 30b.c
Author : Parag Piprewar
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory


Date: 1st October 2025
============================================================================
*/

//b. attach with O_RDONLY and check whether you are able to overwrite.

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key;
    int shmid;
    char *shm_ptr;

    key = ftok(".", 'S');
    if (key == -1) { perror("ftok"); exit(EXIT_FAILURE); }

    shmid = shmget(key, 1024, 0666);
    if (shmid == -1) { perror("shmget"); exit(EXIT_FAILURE); }

    // Attach read-only
    shm_ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shm_ptr == (char *)-1) { perror("shmat"); exit(EXIT_FAILURE); }

    printf("Attached read-only. Current data: %s\n", shm_ptr);

    // Uncommenting below line will cause a crash (segmentation fault)
    strcpy(shm_ptr, "Trying to overwrite!");

    if (shmdt(shm_ptr) == -1) { perror("shmdt"); exit(EXIT_FAILURE); }
    printf("Detached read-only.\n");

    return 0;
}





/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem30$ gcc 30b.c -o 30b ; ./30b
Attached read-only. Current data: Hello, this is shared memory!
Segmentation fault (core dumped)

*/