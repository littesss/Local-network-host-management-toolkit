/*************************************************************************
	> File Name: netutils.h
	> Created Time: Wed 30 Aug 2017 15:18:04 PDT
 ************************************************************************/
#ifndef _NETUTILS_H
#define _NETUTILS_H

//柔性数组，存放变长command
struct Message
{
    int cmd;
    int sharedirlen;
    char tag[0];
};
struct sockaddr_in;

#include <string>
using namespace std;

class netutils
{
    public:
        static int getnicbrdaddr(string& ifname, string& brdaddr);
        static int initsocket();
        static void initdest(sockaddr_in & dest);
        static char* buildmsg(int argc, char** argv, int& bufflen);

};

#endif
