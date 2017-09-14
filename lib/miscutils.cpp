/*************************************************************************
  > File Name: miscutils.cpp
  > Created Time: Fri 01 Sep 2017 17:14:22 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "miscutils.h"
#include "logutils.h"

int miscutils::getexitcode(int status)
{
    if (WIFEXITED(status)) 
    {
        return  WEXITSTATUS(status);

    }
    else if (WIFSIGNALED(status)) 
    {
        return  WTERMSIG(status);
    }

    return 0;
}

void miscutils::initdaemon(int argc, char** argv)
{
    bool isdaemon;
    int opt;

    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            case 'd':
                glogger << "d is set " << endl;
                isdaemon = 1;
                break;
            default: /* '?' */
                cerr << "error" <<endl;
                break;
        }
    }

    if(!isdaemon)
    {
        return;
    }

    rlimit limit;

    getrlimit(RLIMIT_NOFILE, &limit);
    glogger << "cur: " << ((int)limit.rlim_cur) << endl;
    glogger << "max: " << ((int)limit.rlim_max) << endl;

    for(int i = 3; i < limit.rlim_cur ; ++i)
    {
        //close(i);
    }

    int ret = fork();

    if(ret < 0)
    {
        perror("fork:");
        exit(1);
    }

    if(ret)
    {
        //exit parent
        exit(0);
    }

    setsid();
    ret = fork();
    if(ret < 0)
    {
        perror("fork:");
        exit(1);
    }
    if(ret)
    {
        exit(0);
    }
    int fd = open("/dev/null", O_RDWR);
    for(int i = 0; i <= 2; ++i)
    {
        dup2(fd, i);
    }
    return ;
}
