/*
============================================================================
Name : 1a.c
Author : Parag Piprewar
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 30th September 2025
============================================================================
*/



// real_timer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int signum) {
    printf("ITIMER_REAL expired! Signal = %d\n", signum);
}

int main() {
    struct itimerval timer;

    // Install handler for SIGALRM
    signal(SIGALRM, handler);

    // Set initial expiration
    timer.it_value.tv_sec = 10;      // 10 seconds
    timer.it_value.tv_usec = 10;     // 10 microseconds

    // Set interval (repeatedly fire)
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    // Start timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}




//output
/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem1$ gcc 1a.c -o 1a ; ./1a
ITIMER_REAL expired! Signal = 14

ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14

*/