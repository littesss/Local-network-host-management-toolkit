/*************************************************************************
  > File Name: utdaemon.cpp
  > Created Time: Thu 07 Sep 2017 09:04:49 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> //dup2()
#include <fcntl.h> 
#include <unistd.h>

#include <sys/time.h>    //getrlimit()
#include <sys/resource.h>

int main()
{
    rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    cout << "cur:" << limit.rlim_cur << endl;
    cout << "max:" << limit.rlim_max << endl;
    
    //第一步：close() 从3开始
    for(int i=3; i<limit.rlim_cur; ++i)
    {
        close(i);
    }
    //第五步 fork（）
    int ret = fork();
    if(fork < 0)
    {
        perror("fork");
        exit(1);
    }
    if(!ret)
    {
        setsid();
        ret = fork();
        if(ret < 0)
        {
            perror("fork");
            exit(1);
        }
        if(ret)
        {
            exit(0);
        }
        int fd = open("/dev/null",O_RDWR);
        for(int i=0; i<=2; ++i)
        {
            dup2(fd,i);
        }
        while(1)
        {
            //do your work...
            sleep(1);
        }
    }
    exit(0);
    return 0;
}
