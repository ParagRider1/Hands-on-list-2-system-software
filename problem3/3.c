// set_resource_limit
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    struct rlimit limit;

    // Get current limits for max number of open files
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("Before change:\n");
    printf("Soft = %ld | Hard = %ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);

    // Set new soft limit (reduce it to 512 files)
    limit.rlim_cur = 512;

    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("setrlimit");
        exit(1);
    }

    // Verify change
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("After change:\n");
    printf("Soft = %ld | Hard = %ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);

    return 0;
}

//output
/*parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem3$ gcc 3.c -o 3 ; ./3
Before change:
Soft = 1048576 | Hard = 1048576
After change:
Soft = 512 | Hard = 1048576
*/