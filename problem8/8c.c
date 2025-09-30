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