/*
============================================================================
Name : 2.c
Author : Parag Piprewar
Description : Write a program to print the system resource limits. Use getrlimit system call
Date: 30th September 2025
============================================================================
*/



// resource_limits
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void print_limit(int resource, const char *name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%-15s : Soft = ", name);
        if (limit.rlim_cur == RLIM_INFINITY)
            printf("INF");
        else
            printf("%ld", (long)limit.rlim_cur);

        printf(" | Hard = ");
        if (limit.rlim_max == RLIM_INFINITY)
            printf("INF\n");
        else
            printf("%ld\n", (long)limit.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data seg size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
    print_limit(RLIMIT_RSS, "Max resident set");
    print_limit(RLIMIT_NOFILE, "Open files");
    print_limit(RLIMIT_AS, "Address space");
#ifdef RLIMIT_NPROC
    print_limit(RLIMIT_NPROC, "Processes");
#endif
#ifdef RLIMIT_MEMLOCK
    print_limit(RLIMIT_MEMLOCK, "Locked memory");
#endif
#ifdef RLIMIT_MSGQUEUE
    print_limit(RLIMIT_MSGQUEUE, "Msg queue size");
#endif
#ifdef RLIMIT_NICE
    print_limit(RLIMIT_NICE, "Max nice");
#endif
#ifdef RLIMIT_RTPRIO
    print_limit(RLIMIT_RTPRIO, "Realtime priority");
#endif
    return 0;
}


//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem2$ gcc 2.c -o 2 ; ./2
CPU time        : Soft = INF | Hard = INF
File size       : Soft = INF | Hard = INF
Data seg size   : Soft = INF | Hard = INF
Stack size      : Soft = 8388608 | Hard = INF
Core file size  : Soft = 0 | Hard = INF
Max resident set : Soft = INF | Hard = INF
Open files      : Soft = 1048576 | Hard = 1048576
Address space   : Soft = INF | Hard = INF
Processes       : Soft = 29710 | Hard = 29710
Locked memory   : Soft = 993824768 | Hard = 993824768
Msg queue size  : Soft = 819200 | Hard = 819200
Max nice        : Soft = 0 | Hard = 0
Realtime priority : Soft = 0 | Hard = 0
*/
