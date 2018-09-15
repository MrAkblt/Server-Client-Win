/*
    Live Server on port 8888
*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
WSADATA wsa;
SOCKET s , new_socket;
struct sockaddr_in server , client;
int c;
char *message;

void createsocket(){
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
}
void bindsocket(){
     if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    puts("Bind done");
}
void waitconnection(){
    listen(s , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    //accept baglantý gelene kadar o satýrda bekletir.
    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        puts("Connection accepted");

        //Reply to the client
        message = "Hello Client , Welcome\n";
        send(new_socket , message , strlen(message) , 0);
    }
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }
}

int main(int argc , char *argv[])
{
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    createsocket();
    //Bind
    bindsocket();
    //Listen to incoming connections
    waitconnection();


    closesocket(s);
    WSACleanup();

    return 0;
}
