/*************************************************************************
	> File Name: signalhandle.cpp
	> Created Time: Wed 30 Aug 2017 10:06:40 PDT
 ************************************************************************/
#include <iostream>
using namespace std;
#include <signal.h>


void signalhandle1(int signo)
{
    while(1){}
    cout << "signo :" << signo << endl;
}
int main()
{
    cout << "this is  signal test :SIGHUP/SIGINT " << endl;
    signal(SIGHUP,signalhandle1);
    signal(SIGINT,signalhandle1);
    while(1){};
    return 0;
}
