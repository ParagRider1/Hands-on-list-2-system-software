#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigtimer(int sig) {
    printf("Caught SIGVTALRM (virtual timer)\n");
}

int main() {
    signal(SIGVTALRM, handle_sigtimer);

    struct itimerval timer;
    timer.it_value.tv_sec = 2;  // First expiration
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 2; // Repeat every 2 sec
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    while(1) {
        for(volatile long i=0; i<100000000; i++); // Consume CPU time
    }

    return 0;
}


//output 

/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8f.c -o 8f ; ./8f
Caught SIGVTALRM (virtual timer)
Caught SIGVTALRM (virtual timer)
*/