/*
 ============================================================================
 Name        : tcpclient.c
 Author      : Anders Reiche
 Version     : 1.0
 Copyright   : Open Source
 Description : TCP Client
 ============================================================================
 */
#include<stdio.h>
#include<string.h>    		//strlen
#include<sys/socket.h>    	//socket
#include<arpa/inet.h> 		//inet_addr
int close();

int main(int argc , char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[1000];
    sock = socket(AF_INET , SOCK_STREAM , 0); 		//Create socket
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to the server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    //Stay on the server
    puts("Chat with the server, '#' on the start of a new line to quit");
    while(1) {
        printf("Client: ");
        scanf("%s" , message);
        if(message[0] == '#') {
        	close(sock);
        	puts("Goodbye!");
        	return 0;
        }
        send(sock , message , strlen(message) , 0); //Send a message
        recv(sock , server_reply , 2000 , 0);		//Recieve reply from server
        printf("\nServer: %s\n", server_reply);
    }
    return 0;
}
