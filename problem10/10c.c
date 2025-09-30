#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigfpe(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(1);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handle_sigfpe;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGFPE, &sa, NULL);

    // Generate SIGFPE (divide by zero)
    int a = 1;
    int b = 0;
    int c = a / b;  // Causes SIGFPE
    printf("Result: %d\n", c);

    return 0;
}


//output
/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem10$ gcc 10c.c -o 10c ;./10c
Caught SIGFPE (Floating Point Exception)
*/
