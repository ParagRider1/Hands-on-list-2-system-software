/*
============================================================================
Name : 17c.c
Author : Parag Piprewar
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl

Date: 1st October 2025
============================================================================
*/

//using fcntl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
        printf("Child: executing 'ls -l', output will go to pipe.\n");
        close(fd[0]);               
        fcntl(fd[1], F_DUPFD, STDOUT_FILENO); // duplicate write end to stdout
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }
    else {
        printf("Parent: executing 'wc', input comes from pipe.\n");
        close(fd[1]);               
        fcntl(fd[0], F_DUPFD, STDIN_FILENO);  // duplicate read end to stdin
        close(fd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem17$ gcc 17c.c -o 17c ;./17c
Parent: executing 'wc', input comes from pipe.
Child: executing 'ls -l', output will go to pipe.
total 60
-rwxrwxr-x 1 parag-piprewar parag-piprewar 16248 Oct  1 00:23 17a
-rw-rw-r-- 1 parag-piprewar parag-piprewar  1842 Oct  1 00:23 17a.c
-rwxrwxr-x 1 parag-piprewar parag-piprewar 16248 Oct  1 00:24 17b
-rw-rw-r-- 1 parag-piprewar parag-piprewar  1505 Oct  1 00:24 17b.c
-rwxrwxr-x 1 parag-piprewar parag-piprewar 16248 Oct  1 00:26 17c
-rw-rw-r-- 1 parag-piprewar parag-piprewar  1293 Oct  1 00:25 17c.c



*/