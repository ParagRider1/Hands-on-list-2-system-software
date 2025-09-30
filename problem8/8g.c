/*
============================================================================
Name : 8g.c
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

void handle_sigprof(int sig) {
    printf("Caught SIGPROF (profiling timer)\n");
}

int main() {
    signal(SIGPROF, handle_sigprof);

    struct itimerval timer;
    timer.it_value.tv_sec = 1;  // First expiration
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1; // Repeat every 1 sec
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    while(1) {
        for(volatile long i=0; i<100000000; i++); // Consume CPU time
    }

    return 0;
}


//output

/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8g.c -o 8g ; ./8g
Caught SIGPROF (profiling timer)
Caught SIGPROF (profiling timer)
*/