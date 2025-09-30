#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function
void* thread_function(void* arg) {
    pthread_t tid = pthread_self(); // Get thread ID
    printf("Thread %d has ID: %lu\n", *((int*)arg), (unsigned long)tid);
    return NULL;
}

int main() {
    pthread_t threads[3]; // Array to store thread IDs
    int thread_nums[3];
    int i;

    // Create 3 threads
    for(i = 0; i < 3; i++) {
        thread_nums[i] = i + 1;
        if(pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]) != 0) {
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
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem7$ gcc 7.c -o 7 ; ./7
Thread 1 has ID: 129319462500032
Thread 2 has ID: 129319454107328
Thread 3 has ID: 129319445714624
All threads have finished execution.
*/
