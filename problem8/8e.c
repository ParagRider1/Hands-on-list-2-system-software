/*
============================================================================
Name : 8e.c
Author : Parag Piprewar
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)

Date: 30th September 2025
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (using setitimer)\n");
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    struct itimerval timer;
    timer.it_value.tv_sec = 5;  // First expiration
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // No repeat
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while(1) {
        pause(); // Wait for signal
    }

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8e.c -o 8e ; ./8e
Caught SIGALRM (using setitimer)
*/
