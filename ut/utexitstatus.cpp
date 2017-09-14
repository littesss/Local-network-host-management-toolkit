/*************************************************************************
  > File Name: exitstatus.cpp
  > Created Time: Mon 28 Aug 2017 08:59:46 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

int main()
{
    int ret = fork();

    if(!ret)
    {
        sleep(30);
        exit(3);//子进程的退出代码
    }
    int status = 0;//为了记录子进程的退出状态；
    wait(&status);
    cout << status << endl;//4位 ，而子进程的退出代码保存在次低位，用宏WIFEXITED取出

    if (WIFEXITED(status)) {
                               printf("exited, status=%d\n", WEXITSTATUS(status));
                                                  
    } else if (WIFSIGNALED(status)) {
                               printf("killed by signal %d\n", WTERMSIG(status));
                                                  
    } else if (WIFSTOPPED(status)) {
                               printf("stopped by signal %d\n", WSTOPSIG(status));
                                                  
    } else if (WIFCONTINUED(status)) {
                               printf("continued\n");
                                                  
    }

    return 0;
}
