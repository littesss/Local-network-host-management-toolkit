/*************************************************************************
	> File Name: fsutils.cpp
	> Created Time: Fri 01 Sep 2017 15:55:14 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "fsutils.h"

int fsutils::abspath(const char* input, char* output)
{
    if(!input)
    {
        cerr << "input fail " << endl;
        return 0;
    }
    realpath(input, output);
    int len = strlen(output);
    return len;
}

