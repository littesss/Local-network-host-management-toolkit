#ifndef __NETUTILS__
#define __NETUTILS__

struct Message 
{
    int cmd;
    int sdlen;
    char tag[0];
};

struct sockaddr_in;

#include <string>
using namespace std;

class netutils
{
    public:
        static void initdest(sockaddr_in& dest);
        static int initsocket();
        static int getnicbrdaddr(string& ifname, string& brdaddr);
        static char* buildmsg(int argc, char** argv, int& bufflen);
};

#endif
