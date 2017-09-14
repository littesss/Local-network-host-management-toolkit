/*************************************************************************
	> File Name: utatexit.cpp
	> Created Time: Mon 28 Aug 2017 08:40:34 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <stdlib.h>

void fun1()
{
    cout << "this is fun1" << endl;
}

void fun2()
{
    cout << "this is fun2" << endl;
}
int main()
{
    atexit(fun1);
    atexit(fun2);
    cout << "===end===" << endl;
    return 0;
}
