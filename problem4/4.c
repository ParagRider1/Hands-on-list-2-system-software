/*
============================================================================
Name : 4.c
Author : Parag Piprewar
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 30th September 2025
============================================================================
*/



// measure_getppid_timetaken
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <x86intrin.h>   // for __rdtsc()

int main() {
    uint64_t start, end;
    pid_t ppid;
    int i;

    // Read starting TSC value
    start = __rdtsc();

    // Call getppid() 100 times
    for (i = 0; i < 100; i++) {
        ppid = getppid();
    }

    // Read ending TSC value
    end = __rdtsc();

    // Calculate difference
    uint64_t cycles = end - start;

    printf("Parent PID = %d\n", ppid);
    printf("Total cycles for 100 getppid() calls = %lu\n", cycles);
    printf("Average cycles per call = %lu\n", cycles / 100);

    return 0;
}


//output
/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem4$ gcc 4.c -o 4 ; ./4
Parent PID = 10812
Total cycles for 100 getppid() calls = 68221
Average cycles per call = 682
*/