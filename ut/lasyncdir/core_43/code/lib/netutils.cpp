#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>
#include <iostream>
using namespace std;

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "netutils.h"
#include "configparser.h"

int netutils::getnicbrdaddr(string& ifname, string& brdaddr)
{
    ifreq req;
    strcpy(req.ifr_name, ifname.c_str());

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = ioctl(sockfd, SIOCGIFBRDADDR, &req);
    if(ret)
    {
        return ret;
    }

    sockaddr_in baddr = *((sockaddr_in*)(&req.ifr_broadaddr));
    char* broadcast = inet_ntoa(baddr.sin_addr);
    brdaddr = broadcast;
    return 0;
}

int netutils::initsocket()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    int broadcast = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,  
            &broadcast, sizeof(broadcast));
    return sockfd;
}

void netutils::initdest(sockaddr_in& dest)
{
    string interface, port;
    int ret = gparser->getvalue("interface", interface);
    ret += gparser->getvalue("port", port);

    cout << "interface:" << interface << endl;
    cout << "port:" << port << endl;

    if(!ret)
    {
        cerr << "cannot find interface or port number" << endl;
        exit(1);
    }

    string brdaddr;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(atoi(port.c_str()));
    netutils::getnicbrdaddr(interface, brdaddr);
    dest.sin_addr.s_addr = inet_addr(brdaddr.c_str());
}


char* netutils::buildmsg(int argc, char** argv, int& bufflen)
{
    string machines;
    int opt;

    int cmd = 0;
    int a = 0;
    while ((opt = getopt(argc, argv, "fpum:")) != -1) {
        switch (opt) {
            case 'f':
                cout << "f is set " << endl;
                a = 1;
                cmd = cmd | a;
                break;
            case 'p':
                cout << "p is set " << endl;
                a = 1;
                a = a << 1;
                cmd = cmd | a;

                break;
            case 'u':
                cout << "u is set " <<endl;
                a = 1;
                a = a << 2;
                cmd = cmd | a;
                break;
            case 'm':
                machines = optarg;
                cout << machines << endl;
                break;
            default: /* '?' */
                cerr << "error" <<endl;
                return NULL;
        }
    }

    cout << "cmd: " << cmd << endl;
    string sharedir;

    int ret = gparser->getvalue("sharedir", sharedir);
    if(!ret)
    {
        cout << "cannot get sharedir" << endl;
    }
    cout << "sharedir: " << sharedir << endl;

    bufflen = sizeof(Message) + sharedir.length() + machines.length();
    char* pbuff = (char*)malloc(bufflen + 1);
    if(pbuff == NULL)
    {
        cerr << "cannot alloc memory" << endl;
        return NULL;
    }

    memset(pbuff, 0, bufflen);

    pbuff[bufflen] = '\0';

    Message* pmsg = (Message*)pbuff;
    pmsg->cmd = cmd;
    pmsg->sdlen = sharedir.length();
    
    memcpy(pmsg->tag, sharedir.c_str(), sharedir.length()); 
    memcpy(pmsg->tag + sharedir.length(), machines.c_str(), machines.length());

    return pbuff;
}

