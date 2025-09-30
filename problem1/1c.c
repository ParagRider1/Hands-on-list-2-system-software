// prof_timer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int signum) {
    printf("ITIMER_PROF expired! Signal = %d\n", signum);
}

int main() {
    struct itimerval timer;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1) {
        // Mix of user work and system calls (both counted)
        for (volatile long i = 0; i < 100000000; i++);
        sleep(1);
    }

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem1$ gcc 1c.c -o 1c ; ./1c
ITIMER_PROF expired! Signal = 27
*/
