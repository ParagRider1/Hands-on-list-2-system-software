/*
============================================================================
Name : 6.c
Author : Parag Piprewar
Description : Write a simple program to create three threads
Date: 30th September 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that will be executed by each thread
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    printf("Hello from Thread %d\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3]; // Array to hold thread IDs
    int thread_args[3];
    int i;

    // Create 3 threads
    for(i = 0; i < 3; i++) {
        thread_args[i] = i + 1; // Thread number
        if(pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for(i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
}


//output

/*
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem6$ gcc 6.c -o 6 ; ./6
Hello from Thread 1
Hello from Thread 3
Hello from Thread 2
All threads have finished execution.
*/
