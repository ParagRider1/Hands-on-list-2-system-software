/*
============================================================================
Name : reader20.c
Author : Parag Piprewar
Description : Write two programs so that both can communicate by FIFO -Use one way communication.

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char *fifo = "myfifo";
    char buffer[100];

    // Open FIFO for reading
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    // Read message
    read(fd, buffer, sizeof(buffer));
    printf("Reader: Received message -> %s\n", buffer);

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