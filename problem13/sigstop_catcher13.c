// sigstop_catcher13.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigstop(int sig) {
    printf("Caught SIGSTOP!\n");
}

int main() {
    // Attempt to catch SIGSTOP
    signal(SIGSTOP, handle_sigstop);

    printf("Process PID: %d\n", getpid());
    printf("Waiting... Try sending SIGSTOP from another program.\n");

    while(1) {
        sleep(1);
        printf("Running...\n");
    }

    return 0;
}

//output

/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem13$ gcc sigstop_catcher13.c -o sigstop_catcher
gcc sigstop_sender13.c -o sigstop_sender


//sigstop_catcher.c
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem13$ ./sigstop_catcher
Process PID: 20241
Waiting... Try sending SIGSTOP from another program.
Running...
Running...
Running...
Running...
Running...

//sigstop_sender13.c
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem13$ ./sigstop_sender 20241

Sending SIGSTOP to PID 20241
Signal sent.


//sigstop_catcher13.c

Running...

[1]+  Stopped                 ./sigstop_catcher

*/
