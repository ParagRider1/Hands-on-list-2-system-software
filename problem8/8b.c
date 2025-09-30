#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught SIGINT (Ctrl+C)\n");
}

int main() {
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to trigger SIGINT\n");
    while(1) {
        sleep(1); // Keep program running
    }

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem8$ gcc 8b.c -o 8b ; ./8b
Press Ctrl+C to trigger SIGINT
^C Caught SIGINT (Ctrl+C)
*/
