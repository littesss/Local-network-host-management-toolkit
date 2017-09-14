/*************************************************************************
  > File Name: utopen.cpp
  > Created Time: Sun 27 Aug 2017 16:34:13 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fb;
    fb = open("/etc/exports",O_RDONLY);
    char buff[10240];

    int nread = read(fb, buff,10240);
    cout << buff ;

    close(fb);
    cout << "===========parse=============" << endl;
    char * saveptr; // pointer to char *
    char *token;
    token = strtok_r(buff, "\n", &saveptr);// char **
    if(token == NULL)
    {
        cout << "buff NULL!!!" << endl;
        return 0;
    }
    cout << "line 1 :" << token << endl;
    int count = 1;
    
    while(NULL != (token = strtok_r(NULL, "\n", &saveptr)))
    {

        cout << "line " << ++count << ":" << token << endl;
    }

    return 0;
}
