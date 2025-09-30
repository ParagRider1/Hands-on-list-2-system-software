/*
============================================================================
Name : msgq_send27.c
Author : Parag Piprewar
Description :Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag

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


//terminal 1 (to run receiver)
  
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem27$ gcc msgq_recv27.c -o msgq_recv2
7 ; ./msgq_recv27
Message Queue opened. Queue ID: 3

(a) Waiting for message (blocking mode)...


//terminal 2 (to run sender)
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem27$ gcc msgq_send27.c -o msgq_send27; ./msgq_send27
Message Queue created (or opened).
Queue ID: 3
Message sent: Hello, this is a test message!


//terminal 1 (receiver terminal after sender sends message)

Message received (blocking): Hello, this is a test message!

(b) Trying non-blocking receive...
No message in queue (non-blocking mode).


*/