/*************************************************************************
	> File Name: socketServer.cpp
	> Created Time: Wed 30 Aug 2017 09:36:57 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVER_PORT 9999 

#define LISTEN_QUEUE_SIZE 5
#define MAX_BUFFER_SIZE   255

struct Message 
{
    int cmd;
    char tag[0];
};


int main()
{
    int sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
    {
        perror("socket");
    }

    struct sockaddr_in addrSer,addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(struct sockaddr);
    int res = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(res == -1)
    {
        perror("bind");
    }
    
    while(1)
    {
        char recvbuf[1024];
        char sendbuf[1024];
        recvfrom(sockSer, recvbuf, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&addrCli, &len);
        cout << "recved" << endl;

        Message* pmsg = (Message*)recvbuf;
        cout << pmsg->cmd << endl;
        cout << pmsg->tag << endl;
    }

    close(sockSer);
    return 0;
}
    
