#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (using alarm())\n");
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    printf("Setting alarm for 3 seconds\n");
    alarm(3);

    while(1) {
        pause(); // Wait for signal
    }

    return 0;
}


//output

/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8d.c -o 8d ; ./8d
Setting alarm for 3 seconds
Caught SIGALRM (using alarm())
*/