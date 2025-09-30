/*
============================================================================
Name : 23.c
Author : Parag Piprewar
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>

#ifndef F_GETPIPE_SZ
#define F_GETPIPE_SZ 1032   // define manually if not available
#endif

int main() {
    struct rlimit rl;

    // Get maximum number of open files per process
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("Maximum number of open files per process: %ld\n", (long)rl.rlim_cur);

    // Create a pipe
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Get pipe (circular buffer) size
    int pipe_size = fcntl(fd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("Default pipe (circular buffer) size: %d bytes\n", pipe_size);

    close(fd[0]);
    close(fd[1]);
    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem23$ gcc 23.c -o 23 ; ./23
Maximum number of open files per process: 1048576
Default pipe (circular buffer) size: 65536 bytes



*/