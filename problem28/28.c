/*
============================================================================
Name : 28.c
Author : Parag Piprewar
Description :Write a program to change the exiting message queue permission. (use msqid_ds structure)

Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate same key as used before
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue (must exist)
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get current info
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl - IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("Current permissions: %o\n", buf.msg_perm.mode);

    // Change permissions to 0777 (rwx for all)
    buf.msg_perm.mode = 0777;

    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("msgctl - IPC_SET");
        exit(EXIT_FAILURE);
    }

    printf("Permissions changed successfully!\n");

    // Verify
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl - verify");
        exit(EXIT_FAILURE);
    }
    printf("New permissions: %o\n", buf.msg_perm.mode);

    return 0;
}


/*
output

parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem28$ gcc 28.c -o 28 ; ./28
Current permissions: 666
Permissions changed successfully!
New permissions: 777

$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41060aca 0          parag-pipr 666        0            0           
0x42060acb 1          parag-pipr 666        0            0           
0x43060acc 2          parag-pipr 666        100          1           
0x43060acd 3          parag-pipr 666        0            0           
0x43060ace 4          parag-pipr 777        0            0       

*/
