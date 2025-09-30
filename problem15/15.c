/*
============================================================================
Name : 15.c
Author : Parag Piprewar
Description : Write a simple program to send some data from parent to the child process.

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd[2];            // pipe file descriptors
    pid_t pid;
    char write_msg[] = "Hello Child, this is Parent!";
    char read_msg[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) {
        // ---- Parent process ----
        close(fd[0]);  // Close unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);  // Close write end after writing
    }
    else {
        // ---- Child process ----
        close(fd[1]);  // Close unused write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);  // Close read end after reading
    }

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem15$ gcc 15.c -o 15 ;./15
Child received: Hello Child, this is Parent!


*/