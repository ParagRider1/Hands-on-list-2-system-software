/*
============================================================================
Name : 22.c
Author : Parag Piprewar
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO

Date: 1st October 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *fifo_name = "myfifo";
    int fd;
    char buf[1024];

    // Create FIFO if not exists
    if (mkfifo(fifo_name, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Opening FIFO for reading...\n");
    fd = open(fifo_name, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_set readfds;
    struct timeval timeout;

    // Set timeout = 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    printf("Waiting for data on FIFO (10 sec timeout)...\n");

    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (ret == 0) {
        printf("Timeout! No data written into FIFO within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            int n = read(fd, buf, sizeof(buf) - 1);
            if (n > 0) {
                buf[n] = '\0';
                printf("Data received: %s\n", buf);
            } else {
                printf("No data read (FIFO closed by writer).\n");
            }
        }
    }

    close(fd);
    return 0;
}


/*
output


parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem22$ gcc 22.c -o 22 ;./22

Opening FIFO for reading...
Waiting for data on FIFO (10 sec timeout)...
No data read (FIFO closed by writer).


//terminal 1
$ ./22
Opening FIFO for reading...
Waiting for data on FIFO (10 sec timeout)...

//terminal 2
$ echo "Hello FIFO, i am from terminal 2" > myfifo


//terminal 1
Data received: Hello FIFO, i am from terminal 2


*/
