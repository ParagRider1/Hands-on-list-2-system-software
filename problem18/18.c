/*
============================================================================
Name : 18.c
Author : Parag Piprewar
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.

Date: 1st October 2025
============================================================================
*/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd1[2], fd2[2];
    pid_t pid1, pid2, pid3;

    // Create first pipe (ls -> grep)
    if (pipe(fd1) == -1) {
        perror("pipe1 failed");
        exit(1);
    }

    // Create second pipe (grep -> wc)
    if (pipe(fd2) == -1) {
        perror("pipe2 failed");
        exit(1);
    }

    // ---- First child: ls -l ----
    pid1 = fork();
    if (pid1 == 0) {
        // Redirect stdout to pipe1 write end
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]); // not used here

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    // ---- Second child: grep ^d ----
    pid2 = fork();
    if (pid2 == 0) {
        // stdin from pipe1 read end
        dup2(fd1[0], STDIN_FILENO);
        // stdout to pipe2 write end
        dup2(fd2[1], STDOUT_FILENO);

        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]);

        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep failed");
        exit(1);
    }

    // ---- Third child: wc ----
    pid3 = fork();
    if (pid3 == 0) {
        // stdin from pipe2 read end
        dup2(fd2[0], STDIN_FILENO);

        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]);

        execlp("wc", "wc", NULL);
        perror("execlp wc failed");
        exit(1);
    }

    // ---- Parent process ----
    close(fd1[0]); close(fd1[1]);
    close(fd2[0]); close(fd2[1]);

    // Wait for children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem18$ mkdir testdir
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem18$ gcc 18.c -o 18 ;./18
      1       9      70



      //That’s wc output = (lines words chars). The first number = total directories.

*/