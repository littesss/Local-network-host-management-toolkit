#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#include <signal.h>

#include <iostream>
using namespace std;

const int MAX_BUFFER_SIZE = 1024;
const int PORT = 8888;
int sockSer = 0;

void sighandler(int signo)
{
    cout << "sig number: " << signo << endl;
    close(sockSer);
}

struct Message 
{
    int cmd;
    char tag[0];
};


int main()
{

    //signal(SIGHUP, sighandler);
    //signal(SIGINT, sighandler);

    sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
    {
        perror("socket");
    }

    struct sockaddr_in addrSer,addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(PORT);
    addrSer.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(struct sockaddr);

    int res = bind(sockSer, (struct sockaddr*)&addrSer, len);

    if(res == -1)                                        
    {                                                    
        perror("bind");                                  
    }                                                    

    char sendbuf[MAX_BUFFER_SIZE];
    char recvbuf[MAX_BUFFER_SIZE];
    cout << "test" << endl;

    while(1)
    {
        recvfrom(sockSer, recvbuf, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&addrCli, &len);

        cout << "received" << endl;

        Message* pmsg = (Message*)recvbuf;
        cout << "cmd:" << pmsg->cmd << endl;
        cout << "machines:" << pmsg->tag << endl;



    }

    close(sockSer);
    return 0;
}
