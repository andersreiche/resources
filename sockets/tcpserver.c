/*
 ============================================================================
 Name        : tcpserver.c
 Author      : Anders Reiche
 Version     : 1.0
 Copyright   : Open Source
 Description : TCP Server
 ============================================================================
 */

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
void inverter(void);
char client_message[2000];


int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;


    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    bind(socket_desc,(struct sockaddr *)&server , sizeof(server));

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //Accept
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ) {
    	inverter();
        write(client_sock , client_message , strlen(client_message));
    }
    puts("Client disconnected");
    return 0;
}

void inverter(void) {
				int c = 0;
				while (client_message[c] != '\0') {
					if (client_message[c] >= 'A' && client_message[c] <= 'Z') {
						client_message[c] += 32;
						c++;
					} else if (client_message[c] >= 'a' && client_message[c] <= 'z') {
						client_message[c] -= 32;
						c++;
					} else {
						c++;
					}
				}
		fflush(stdout);
		return;
}
