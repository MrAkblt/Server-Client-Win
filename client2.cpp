#include<stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;
WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char *message , server_reply[2000];
int recv_size;
vector<int> numbers;
 //Winsock Library
void createsocket(){
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server.sin_addr = *(in_addr *) gethostbyname("www.google.com")->h_addr_list[0];
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
}

void connecthost(){
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return ;
    }

    puts("Connected");
}

void sendhost(){
    Sleep(3000);
    while(true){
        if(!numbers.empty()){
            char *pchar;
            itoa(numbers.front(),pchar,10);
            //string str=to_string(numbers.front());

            if( send(s , pchar , strlen(message) , 0) < 0)
            {
                puts("Send failed");
                return ;
            }
            puts("Data Send\n");
            numbers.erase(numbers.begin());
            Sleep(300);
        }
    }
}
void startcounter(){
    int i=0;
    while(true){
        numbers.push_back(i);
        Sleep(1000);
        i++;
    }
}

void replyfromhost(){
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");
    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);
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
    //Connect to remote server
    connecthost();
    //Send some data
    thread t1(startcounter);
    thread t2(sendhost);
    //Receive a reply from the server
    replyfromhost();

    WSACleanup();
    return 0;
}

