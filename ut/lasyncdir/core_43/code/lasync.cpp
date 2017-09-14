#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
using namespace std;

#include "netutils.h"
#include "nfsutils.h"
#include "configparser.h"

int main(int argc, char** argv)
{
    int sockfd, bufflen, ret;
    char* msg;
    string sharedir;

    gparser->initkvmap("conf/lasync.conf");

    msg = netutils::buildmsg(argc, argv, bufflen);
    if(!msg)
    {
        cerr << "can not build messages" << endl;
        goto ERROR;
    }
    
    //export share dir via nfs
    ret = gparser->getvalue("sharedir", sharedir);
    if(!nfsutils::isexported(sharedir))
    {
        ret = nfsutils::confignfs(sharedir);
        ret = nfsutils::nfsstop();
        ret += nfsutils::nfsstart();
        if(ret)
        {
            cerr << "cannot config nfs:" << sharedir << " ret:" << ret << endl;
            exit(1);
        }
    }

    Message* pmsg;
    pmsg = (Message*)msg;
    cout << "buffer:" <<  pmsg->cmd << endl;
    cout << "buffer machine:" <<  pmsg->tag << endl;
    
    //init socket fd to send data
    sockfd = netutils::initsocket();

    //init dest for sockfd
    struct sockaddr_in dest;
    netutils::initdest(dest); 

    ret = sendto(sockfd, msg, bufflen + 1, 0, 
            (struct sockaddr*)&dest, sizeof(sockaddr_in));

    if(ret < 0)
    {
        perror("sendto");
        goto ERROR;
    }

    free(msg);
    close(sockfd);
    exit(0);

ERROR:
    close(sockfd);
    free(msg);
    exit(1);

}
