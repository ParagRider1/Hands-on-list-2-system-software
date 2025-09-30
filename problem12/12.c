/*
============================================================================
Name : 12.c
Author : Parag Piprewar
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 30th September 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid;

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        printf("Child process: My PID is %d\n", getpid());
        printf("Child process: Killing parent process (PID %d) now...\n", getppid());

        // Send SIGKILL to parent
        kill(getppid(), SIGKILL);

        // Sleep for a while to show it becomes orphaned
        sleep(5);
        printf("Child process: My new parent PID is %d (should be 1 if adopted by init)\n", getppid());
        exit(0);
    } else { // Parent process
        printf("Parent process: My PID is %d\n", getpid());
        printf("Parent process: Sleeping for 10 seconds...\n");
        sleep(10);  // Parent will be killed by child before this finishes
        printf("Parent process: This line will likely never be printed\n");
    }

    return 0;
}


//output

/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem12$ gcc 12.c -o 12 ;./12
Parent process: My PID is 16814
Parent process: Sleeping for 10 seconds...
Child process: My PID is 16815
Child process: Killing parent process (PID 16814) now...
Killed
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem12$ Child process: My new parent PID is 2151 (should be 1 if adopted by init)
*/
