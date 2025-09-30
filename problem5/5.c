/*
============================================================================
Name : 5.c
Author : Parag Piprewar
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.

Date: 30th September 2025
============================================================================
*/



// system_limits.c
#include <stdio.h>
#include <unistd.h>

int main() {
    long val;

    // a. Maximum length of arguments to exec family
    val = sysconf(_SC_ARG_MAX);
    printf("Max length of arguments to exec: %ld\n", val);

    // b. Maximum number of simultaneous processes per user id
    val = sysconf(_SC_CHILD_MAX);
    printf("Max simultaneous processes per user id: %ld\n", val);

    // c. Number of clock ticks (jiffy) per second
    val = sysconf(_SC_CLK_TCK);
    printf("Clock ticks (jiffy) per second: %ld\n", val);

    // d. Maximum number of open files
    val = sysconf(_SC_OPEN_MAX);
    printf("Max number of open files: %ld\n", val);

    // e. Size of a page
    val = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld bytes\n", val);

    // f. Total number of pages in physical memory
    val = sysconf(_SC_PHYS_PAGES);
    printf("Total number of pages in physical memory: %ld\n", val);

    // g. Number of currently available pages in physical memory
    val = sysconf(_SC_AVPHYS_PAGES);
    printf("Available pages in physical memory: %ld\n", val);

    return 0;
}

//output
/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem5$ gcc 5.c -o 5 ; ./5
Max length of arguments to exec: 2097152
Max simultaneous processes per user id: 29710
Clock ticks (jiffy) per second: 100
Max number of open files: 1048576
Page size: 4096 bytes
Total number of pages in physical memory: 1941067
Available pages in physical memory: 114855
*/

