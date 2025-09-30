/*
============================================================================
Name : 34a.c
Author : Parag Piprewar
Description :Write a program to create a concurrent server.
a. use fork
b. use pthread_create

Date: 1st October 2025
============================================================================
*/


//using fork

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    int n;

    n = read(client_sock, buffer, BUFFER_SIZE);
    buffer[n] = '\0';
    printf("Message from client: %s\n", buffer);

    char *response = "Message received by server";
    write(client_sock, response, strlen(response));

    close(client_sock);
    printf("Client connection closed.\n");
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) { perror("socket"); exit(EXIT_FAILURE); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind"); exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) { perror("listen"); exit(EXIT_FAILURE); }
    printf("Concurrent server using fork() listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (client_sock < 0) { perror("accept"); continue; }

        pid_t pid = fork();
        if (pid == 0) {
            close(server_fd); // child doesn't need listener
            handle_client(client_sock);
            exit(0);
        } else if (pid > 0) {
            close(client_sock); // parent closes connected socket
        } else {
            perror("fork");
        }
    }

    close(server_fd);
    return 0;
}



/*

output:

//terminal 1
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem34$ gcc 34a.c -o 34a ; ./34a
Concurrent server using fork() listening on port 8080...


//terminal 2
parag-piprewar@parag-piprewar-HP-Pavilion-x360-Convertible-14-dw1xxx:/media/parag-piprewar/CODING ; DSA ; IIITB/classwork 1st sem/SS/handsonlist2/problem34$ ./34a
bind: Address already in use


*/
