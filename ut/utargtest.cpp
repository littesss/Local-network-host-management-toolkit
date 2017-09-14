/*************************************************************************
  > File Name: argtest.cpp
  > Created Time: Mon 28 Aug 2017 14:47:12 PDT
 ************************************************************************/
#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>

#include <unistd.h>

int main(int argc,char *argv[])
{
    string machine;
    int opt;
    while((opt = getopt(argc, argv, "fupm:")) != -1)
    {
        //cout << opt <<endl;  返回值是int类型
        switch(opt)
        {
            case 'f':
                cout << "f is set" << endl;
                break;
            case 'u':
                cout << "u is set" << endl;
                break;
            case 'p':
                cout << "p is set" << endl;
                break;
            case 'm':
                cout << "m is set" << endl;
                machine = optarg;
                cout << machine << endl;
                break;
            default: /* '?' */
                cout << "Error!!!" << endl;
                exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
    return 0;
}
