/*
============================================================================
Name : 17b.c
Author : Parag Piprewar
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl

Date: 1st October 2025
============================================================================
*/

//using dup2

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
        printf("Child: running 'ls -l' → pipe → parent.\n");
        close(fd[0]);               
        dup2(fd[1], STDOUT_FILENO); // redirect stdout
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }
    else {
        printf("Parent: running 'wc' ← pipe ← child.\n");
        close(fd[1]);               
        dup2(fd[0], STDIN_FILENO);  // redirect stdin
        close(fd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem17$ gcc 17b.c -o 17b ;./17b
Child: running 'ls -l' → pipe → parent.
Parent: running 'wc' ← pipe ← child.
      6      47     345




      //That’s wc output = (lines words chars). The first number = total directories
*/

