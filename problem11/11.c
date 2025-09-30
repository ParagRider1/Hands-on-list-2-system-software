#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa_ignore, sa_default;

    // 1. Setup to ignore SIGINT
    sa_ignore.sa_handler = SIG_IGN; // Ignore signal
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    sigaction(SIGINT, &sa_ignore, NULL);
    printf("SIGINT is now ignored. Press Ctrl+C (will be ignored) for 5 seconds.\n");

    // Wait for 5 seconds while SIGINT is ignored
    for(int i = 5; i > 0; i--) {
        printf("%d...\n", i);
        sleep(1);
    }

    // 2. Reset SIGINT to default action
    sa_default.sa_handler = SIG_DFL; // Default action
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;

    sigaction(SIGINT, &sa_default, NULL);
    printf("SIGINT reset to default action. Press Ctrl+C to terminate the program.\n");

    // Infinite loop to test default SIGINT behavior
    while(1) {
        printf("Running... Press Ctrl+C to exit.\n");
        sleep(2);
    }

    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem11$ gcc 11.c -o 11 ;./11
SIGINT is now ignored. Press Ctrl+C (will be ignored) for 5 seconds.
5...
4...
3...
2...
1...
SIGINT reset to default action. Press Ctrl+C to terminate the program.
Running... Press Ctrl+C to exit.
Running... Press Ctrl+C to exit.
Running... Press Ctrl+C to exit.
^C
*/
