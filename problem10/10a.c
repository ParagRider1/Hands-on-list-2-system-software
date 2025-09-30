/*
============================================================================
Name : 10a.c
Author : Parag Piprewar
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 30th September 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigsegv(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handle_sigsegv;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGSEGV, &sa, NULL);

    // Generate SIGSEGV
    int *ptr = NULL;
    *ptr = 42; // Invalid memory access

    return 0;
}


//output

/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem10$ gcc 10a.c -o 10a ;./10a
Caught SIGSEGV (Segmentation Fault)
*/
