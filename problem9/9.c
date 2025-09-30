#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Press Ctrl+C. The signal will be ignored for 5 seconds.\n");

    // 1. Ignore SIGINT
    signal(SIGINT, SIG_IGN);

    // Wait for 5 seconds while ignoring SIGINT
    for(int i = 5; i > 0; i--) {
        printf("%d...\n", i);
        sleep(1);
    }

    printf("Resetting SIGINT to default action.\n");

    // 2. Reset SIGINT to default
    signal(SIGINT, SIG_DFL);

    printf("Now pressing Ctrl+C will terminate the program.\n");

    // Infinite loop to test default SIGINT action
    while(1) {
        printf("Running... Press Ctrl+C to exit.\n");
        sleep(2);
    }

    return 0;
}


//output

/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem9$ gcc 9.c -o 9 ; ./9
Press Ctrl+C. The signal will be ignored for 5 seconds.
5...
4...
3...
2...
1...
Resetting SIGINT to default action.
Now pressing Ctrl+C will terminate the program.
Running... Press Ctrl+C to exit.
Running... Press Ctrl+C to exit.
Running... Press Ctrl+C to exit.
Running... Press Ctrl+C to exit.
^C
*/