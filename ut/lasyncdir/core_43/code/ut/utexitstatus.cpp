#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int sleepinterval = 10;
    if(argc > 1 )
    {
        sleepinterval = atoi(argv[1]);
        if(sleepinterval < 0)
        {
            perror("atoi");
            exit(1);
        }
    }

    int ret = fork();
    if(!ret)
    {
        sleep(sleepinterval);
        exit(3);
    }
    int status = 0;

    wait(&status);

    cout << status << endl;

    if (WIFEXITED(status)) {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("killed by signal %d\n", WTERMSIG(status));
    }

    return 0;
}
