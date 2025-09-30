/*
============================================================================
Name : 21prog2.c
Author : Parag Piprewar
Description : Write two programs so that both can communicate by FIFO -Use two way communications.

Date: 1st October 2025
============================================================================
*/

// prog2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1, fd2;
    char str1[100], str2[100];

    // open FIFO1 for reading, FIFO2 for writing
    fd1 = open("fifo1", O_RDONLY);
    fd2 = open("fifo2", O_WRONLY);

    if (fd1 < 0 || fd2 < 0) {
        perror("open");
        exit(1);
    }

    while (1) {
        read(fd1, str1, sizeof(str1));
        printf("Process1 said: %s\n", str1);

        printf("Process2: Enter reply: ");
        fgets(str2, sizeof(str2), stdin);
        write(fd2, str2, strlen(str2) + 1);
    }

    close(fd1);
    close(fd2);
    return 0;
}



/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem21$ gcc 21prog1.c -o prog1
gcc 21prog2.c -o prog2


---------------------
//terminal 1 :prog1

$ ./prog1
Process1: Enter message: hello there i am prog1 , how r u
Process2 replied: i am perfect, u can chat with me, wow

Process1: Enter message: yeah, buddy, i am damn great in writing ss codes, hehe
Process2 replied: yeah, i know i know

Process1: Enter message: ^C




----------------------
//terminal 2  :prog2

$ ./prog2
Process1 said: hello there i am prog1 , how r u

Process2: Enter reply: i am perfect, u can chat with me, wow
Process1 said: yeah, buddy, i am damn great in writing ss codes, hehe

Process2: Enter reply: yeah, i know i know
Process1 said: yeah, buddy, i am damn great in writing ss codes, hehe

Process2: Enter reply: ^C


*/
