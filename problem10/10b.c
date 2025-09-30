#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGINT (Ctrl+C)\n");
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handle_sigint;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger SIGINT\n");
    while(1) {
        sleep(1); // Keep program running
    }

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem10$ gcc 10b.c -o 10b ;./10b
Press Ctrl+C to trigger SIGINT
^CCaught SIGINT (Ctrl+C)
^CCaught SIGINT (Ctrl+C)
*/

