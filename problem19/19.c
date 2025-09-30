/*
============================================================================
Name : 19.c
Author : Parag Piprewar
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function

Date: 1st October 2025
============================================================================
*/


a. Using mknod command


# Syntax: mknod <filename> p

mknod myfifo1 p
ls -l myfifo1

o/p:
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem19$ ls -l myfifo1

prw-rw-r-- 1 parag-piprewar parag-piprewar 0 Oct  1 01:10 myfifo1



---------------------------------------------------------------------------------------


b. Using mkfifo command


# Syntax: mkfifo <filename>

mkfifo myfifo2
ls -l myfifo2

o/p:
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem19$ ls -l myfifo2

prw-rw-r-- 1 parag-piprewar parag-piprewar 0 Oct  1 01:11 myfifo2


--------------------------------------------------------------------------------------------

c. Using strace command to find out, which command (mknod or mkfifo) is better.


# For mknod
strace mknod myfifo3 p

# For mkfifo
strace mkfifo myfifo4

mknod → internally calls mknod system call.

mkfifo → internally calls mkfifo system call, which may internally use mknod with proper FIFO flags.


-----------------------------------------------------------------------------



d. Using mknod system call


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    if (mknod("myfifo5", S_IFIFO | 0666, 0) == -1) {
        perror("mknod failed");
        exit(1);
    }
    printf("FIFO 'myfifo5' created using mknod system call.\n");
    return 0;
}

o/p:
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem19$ gcc 19.c -o 19 ;./19
FIFO 'myfifo5' created using mknod system call.


--------------------------------------------------------------------------------------


e. Using mkfifo library function in c


#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    if (mkfifo("myfifo6", 0666) == -1) {
        perror("mkfifo failed");
        exit(1);
    }
    printf("FIFO 'myfifo6' created using mkfifo library function.\n");
    return 0;
}


o/p:

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem19$ gcc 19.c -o 19 ;./19

FIFO 'myfifo6' created using mkfifo library function.


------------------------------------------------------------------------