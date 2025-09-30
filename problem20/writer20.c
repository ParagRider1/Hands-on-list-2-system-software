/*
============================================================================
Name : writer20.c
Author : Parag Piprewar
Description : Write two programs so that both can communicate by FIFO -Use one way communication.

Date: 1st October 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char *fifo = "myfifo";
    char message[] = "Hello from Writer (Parent) using FIFO!";

    // Open FIFO for writing
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    // Write message
    write(fd, message, strlen(message)+1);
    printf("Writer: Sent message -> %s\n", message);

    close(fd);
    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem20$ gcc writer20.c -o writer
gcc reader20.c -o reader

//reader terminal
  ./reader


//writer terminal
  ./writer
Writer: Sent message -> Hello from Writer (Parent) using FIFO!


//reader terminal
Reader: Received message -> Hello from Writer (Parent) using FIFO!


*/