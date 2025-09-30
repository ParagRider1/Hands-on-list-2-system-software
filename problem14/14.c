/*
============================================================================
Name : 14.c
Author : Parag Piprewar
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.

Date: 1st october 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd[2];  // file descriptors for the pipe
    char write_msg[] = "Hello from the pipe!";
    char read_msg[100];
    pid_t pid;

    // create pipe
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
        // Parent process -> writer
        close(fd[0]);  // close unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);  // close write end after writing
    } 
    else {
        // Child process -> reader
        close(fd[1]);  // close unused write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);  // close read end after reading
    }

    return 0;
}



/*
output
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem14$ gcc 14.c -o 14 ;./14
Child received: Hello from the pipe!

*/
