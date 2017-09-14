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
#include <pthread.h>


#include "netutils.h"
#include "command.h"
#include "configparse.h"
#include "logutils.h"
#include "miscutils.h"

#define MAX_BUFFER_SIZE   255

void sighandler(int signo)
{
    CommandExecuter::runningflag = 0;
}

int main(int argc, char** argv)
{
        
    string port;
    char namebuff[64];
    string myname;
    pthread_t tid;
    char recvbuf[1024];
    int sockfd;
    socklen_t len;
    sockaddr_in myaddr;
    sockaddr_in peeraddr;
    int ret;

    miscutils::initdaemon(argc,argv);
    
    gethostname(namebuff,64);
    
    gpparse->initkvmap("conf/lasync.conf");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        goto ERROR;
    }

    ret = gpparse->getvalue("port",port);
    if(!ret)
    {
        glogger << "cannot get server listen port" << endl;
        goto ERROR; 
    }

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(port.c_str()));
    myaddr.sin_addr.s_addr = INADDR_ANY;//任何人都可以连接

    len = sizeof(struct sockaddr);
    ret = bind(sockfd, (struct sockaddr*)&myaddr, len);
    if(ret == -1)
    {
        perror("bind");
        goto ERROR;
    }
   
    ret = pthread_create(&tid, NULL, CommandExecuter::executecmd, NULL);
    if(ret)
    {
        glogger << "cannot create thread" << endl;
        goto ERROR;
    }
    if(ret)
    {
        glogger << "connot create thread" << endl;
        goto ERROR;
    }

    while(1)
    {
        int msglen = recvfrom(sockfd, recvbuf, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&peeraddr, &len);
        CommandExecuter::extractmsg((char*)recvbuf, msglen, peeraddr, myname);
        
        
        
        
        
  /*      
        cout << "recved" << endl;

        Message* pmsg = (Message*)recvbuf;
        cout << "pmsg->cmd:" << pmsg->cmd << endl;
        cout << "pmsg->sharedirlen:" << pmsg->sharedirlen << endl;
        cout << "pmsg->tag:" << pmsg->tag + pmsg->sharedirlen << endl;
        
        char buff[256];

        buff[pmsg->sharedirlen] = '\0';
        memcpy(buff, pmsg->tag, pmsg->sharedirlen);//不会拷贝‘\0’

        string sharedir(buff);
        strcpy(buff, pmsg->tag + pmsg->sharedirlen);
        string mstr(buff);

        cout << "share dir:" << sharedir << endl;
        cout << "machines:" << mstr << endl;
        //分割主机名
        vector<string> machines;
        strutils::split(mstr,",",machines);
        if(!strutils::inlist(myname,machines))
        {
            continue;
        }

        string serveraddr(inet_ntoa(peeraddr.sin_addr));
        cout << "serveraddr" << serveraddr << endl;
        
        deque<Command*> tempqueue = extractmsg((char*)pmsg, msglen, serveraddr, sharedir);
        
        pthread_mutex_lock(&lock);
        copy(tempqueue.begin(),tempqueue.end(), back_inserter(commands));
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
*/
/*      while(!commands.empty())
        {
            Command* pcmd = commands[0];
            commands.pop_front();
            pcmd->execute();  //加锁
            delete pcmd;
            pcmd = NULL;
        }
*/

/*   for(deque<Command*>::iterator it = commands.begin();
                it  != commands.end(); ++it)
        {
            (*it)->execute();//修改容器，迭代器必须修改
        }
*/

    }
    return 0;
ERROR:
    close(sockfd);
    exit(1);
}
    
