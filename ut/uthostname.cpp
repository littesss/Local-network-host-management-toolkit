/*************************************************************************
	> File Name: uthostname.cpp
	> Created Time: Mon 11 Sep 2017 00:09:13 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <unistd.h>

int main()
{
    char namebuff[126];
    int ret = gethostname(namebuff, 126);
    cout << "hostname:"<< namebuff << endl;   
    return ret;
}
