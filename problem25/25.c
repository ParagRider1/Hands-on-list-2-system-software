/*
============================================================================
Name : 25.c
Author : Parag Piprewar
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate key
    key = ftok(".", 'B');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or get message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get message queue info
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Information:\n");

    // a. Access permission
    printf("Access Permissions: %o\n", buf.msg_perm.mode);

    // b. UID, GID
    printf("UID: %d, GID: %d\n", buf.msg_perm.uid, buf.msg_perm.gid);

    // c. Last message sent & received times
    printf("Last msgsnd time: %s", (buf.msg_stime ? ctime(&buf.msg_stime) : "Not sent yet\n"));
    printf("Last msgrcv time: %s", (buf.msg_rtime ? ctime(&buf.msg_rtime) : "Not received yet\n"));

    // d. Last change time
    printf("Last change time: %s", ctime(&buf.msg_ctime));

    // e. Size of queue
    printf("Current number of bytes in queue: %lu\n", buf.__msg_cbytes);

    // f. Number of messages in queue
    printf("Number of messages in queue: %lu\n", buf.msg_qnum);

    // g. Max bytes allowed
    printf("Max number of bytes allowed: %lu\n", buf.msg_qbytes);

    // h. PID of last msgsnd & msgrcv
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem25$ gcc 25.c -o 25 ; ./25
Message Queue Information:
Access Permissions: 666
UID: 1000, GID: 1000
Last msgsnd time: Not sent yet
Last msgrcv time: Not received yet
Last change time: Wed Oct  1 02:04:07 2025
Current number of bytes in queue: 0
Number of messages in queue: 0
Max number of bytes allowed: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0

*/