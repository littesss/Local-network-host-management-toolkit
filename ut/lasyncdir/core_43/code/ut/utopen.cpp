#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>


#include <iostream>

using namespace std;

int main()
{
    int fd = open("/etc/exports", O_RDONLY);
    
    char buf[10240];
    int nread = read(fd, buf, 10240);
    close(fd);

    cout << buf << endl;

    cout << "parsing " << endl;
    
    char* saveptr;
    char* token = strtok_r(buf, "\n", &saveptr);
    cout << "line 1:" << token << endl;

    int counter = 1;
    while(NULL != (token = strtok_r(NULL, "\n", &saveptr)))
    {
        counter++;
        cout << "line "<< counter << ":" << token <<endl;
    }

    cout << "==========\nend" << endl;
    return 0;
}
