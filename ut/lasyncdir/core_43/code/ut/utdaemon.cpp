#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/resource.h>

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
int main()
{
    rlimit limit;

    getrlimit(RLIMIT_NOFILE, &limit);
    cout << "cur: " << limit.rlim_cur << endl;
    cout << "max: " << limit.rlim_max << endl;

    for(int i = 3; i < limit.rlim_cur ; ++i)
    {
        close(i);
    }

    int ret = fork();

    if(ret < 0)
    {
        perror("fork:");
        exit(1);
    }

    if(!ret)
    {
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
        while(1)
        {
            //do your work...
            sleep(1);
        }
    }
    exit(0);

    return 0;
}
