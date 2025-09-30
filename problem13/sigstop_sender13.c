// sigstop_sender13.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <PID to send SIGSTOP>\n", argv[0]);
        return 1;
    }

    pid_t target_pid = atoi(argv[1]);
    printf("Sending SIGSTOP to PID %d\n", target_pid);

    kill(target_pid, SIGSTOP);

    printf("Signal sent.\n");

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
