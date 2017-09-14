/*************************************************************************
  > File Name: utabspath.cpp
  > Created Time: Thu 31 Aug 2017 14:50:38 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fsutils.h"

int main()
{
    char buff[256];
    int ret = fsutils::abspath("./.lampt", buff);
    if(!ret)
    {
        perror("ret");
        exit(1);
    }

    cout << "absPath:" << buff << endl
        <<"strlen:" << ret << endl;
    return 0;
}
