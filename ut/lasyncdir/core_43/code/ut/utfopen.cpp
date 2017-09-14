#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>

#include <iostream>

using namespace std;

int main()
{
    FILE* fp = fopen("/etc/exports", "r");

    char line[1024];
    int counter = 1;
    while(NULL != fgets(line, 1024, fp))
    {
        cout << "line " << counter <<":"<< line ;
        counter++;
    }

    fclose(fp);
    cout << "==========\nend" << endl;
    return 0;
}
