/*
============================================================================
Name : 17a.c
Author : Parag Piprewar
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl

Date: 1st October 2025
============================================================================
*/

//using dup

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // ---- Child process ----
        printf("Child: running 'ls -l' and sending output to parent through pipe...\n");
        close(fd[0]);               // close read end
        close(STDOUT_FILENO);       // close stdout
        dup(fd[1]);                 // duplicate write end into stdout
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }
    else {
        // ---- Parent process ----
        printf("Parent: running 'wc' and receiving data from child through pipe...\n");
        close(fd[1]);               // close write end
        close(STDIN_FILENO);        // close stdin
        dup(fd[0]);                 // duplicate read end into stdin
        close(fd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    return 0;
}

/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem17$ gcc 17a.c -o 17a ;./17a
Parent: running 'wc' and receiving data from child through pipe...
Child: running 'ls -l' and sending output to parent through pipe...
      5      38     279






      //That’s wc output = (lines words chars). The first number = total directories.

*/