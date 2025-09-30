/*
============================================================================
Name : 29.c
Author : Parag Piprewar
Description : Write a program to remove the message queue.

Date: 1st October 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// Message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 1. Generate key
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 2. Create message queue (or get existing)
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Message queue created. ID: %d\n", msgid);

    // 3. Send a message
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello! This is a test message.");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", message.msg_text);

    printf("Check queue info using: ipcs -q\n");

    // 4. Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl - IPC_RMID");
        exit(EXIT_FAILURE);
    }
    printf("Message queue removed successfully!\n");

    return 0;
}

/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem29$ gcc 29.c -o 29 ; ./29
Message queue created. ID: 5
Message sent: Hello! This is a test message.
Check queue info using: ipcs -q
Message queue removed successfully!


parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41060aca 0          parag-pipr 666        0            0           
0x42060acb 1          parag-pipr 666        0            0           
0x43060acc 2          parag-pipr 666        100          1           
0x43060acd 3          parag-pipr 666        0            0           
0x43060ace 4          parag-pipr 777        0            0           


//no msqid 5 as it is removed


*/