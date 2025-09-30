// virtual_timer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int signum) {
    printf("ITIMER_VIRTUAL expired! Signal = %d\n", signum);
}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1) {
        // Busy loop ensures CPU usage so timer decreases
        for (volatile long i = 0; i < 100000000; i++);
    }

    return 0;
}


//output 
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem1$ gcc 1b.c -o 1b ; ./1b
ITIMER_VIRTUAL expired! Signal = 26
ITIMER_VIRTUAL expired! Signal = 26
*/