/*
============================================================================
Name : 8c.c
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
#include <stdlib.h>
#include <signal.h>

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(1);
}

int main() {
    signal(SIGFPE, handle_sigfpe);

    int a = 1;
    int b = 0;
    int c = a / b;  // Generates divide by zero
    printf("Result: %d\n", c);

    return 0;
}


//output

/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8c.c -o 8c ; ./8c
Caught SIGFPE (Floating Point Exception)
*/