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

