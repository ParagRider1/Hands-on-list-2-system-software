/*
============================================================================
Name : 26.c
Author : Parag Piprewar
Description : Write a program to send messages to the message queue. Check $ipcs -q

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate unique key
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue created (or opened).\nQueue ID: %d\n", msgid);

    // Prepare message
    message.msg_type = 1; // Must be > 0
    strcpy(message.msg_text, "Hello, this is a test message!");

    // Send message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message.msg_text);
    printf("Now run: ipcs -q to check the queue.\n");

    return 0;
}



/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem26$ gcc 26.c -o 26 ; ./26
Message Queue created (or opened).
Queue ID: 2
Message sent: Hello, this is a test message!
Now run: ipcs -q to check the queue.

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41060aca 0          parag-pipr 666        0            0           
0x42060acb 1          parag-pipr 666        0            0           
0x43060acc 2          parag-pipr 666        100          1           




*/