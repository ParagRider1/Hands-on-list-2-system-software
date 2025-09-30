/*
============================================================================
Name : 8a.c
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

void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, handle_sigsegv);

    // Generate SIGSEGV
    int *ptr = NULL;
    *ptr = 42;  // Invalid memory access

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8a.c -o 8a ; ./8a
Caught SIGSEGV (Segmentation Fault)
*/

