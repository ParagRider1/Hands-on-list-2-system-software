/*
============================================================================
Name : 16.c
Author : Parag Piprewar
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd1[2], fd2[2];   // fd1 for Parent->Child, fd2 for Child->Parent
    pid_t pid;
    char parent_msg[] = "Hello Child, this is Parent!";
    char child_msg[] = "Hello Parent, this is Child!";
    char buffer[100];

    // Create two pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
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
        close(fd1[0]); // Close unused read end of fd1
        close(fd2[1]); // Close unused write end of fd2

        // Send message to child
        write(fd1[1], parent_msg, strlen(parent_msg) + 1);
        close(fd1[1]);

        // Read reply from child
        read(fd2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd2[0]);
    }
    else {
        // ---- Child process ----
        close(fd1[1]); // Close unused write end of fd1
        close(fd2[0]); // Close unused read end of fd2

        // Read message from parent
        read(fd1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd1[0]);

        // Send reply to parent
        write(fd2[1], child_msg, strlen(child_msg) + 1);
        close(fd2[1]);
    }

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem16$ gcc 16.c -o 16 ;./16
Child received: Hello Child, this is Parent!
Parent received: Hello Parent, this is Child!

*/