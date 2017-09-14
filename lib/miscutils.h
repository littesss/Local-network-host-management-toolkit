/*************************************************************************
	> File Name: misc.h
	> Created Time: Fri 01 Sep 2017 17:09:06 PDT
 ************************************************************************/
#ifndef _MISC_H
#define _MISC_H

class miscutils
{
    public:
        static int getexitcode(int exitstatus);
        static void initdaemon(int argc, char** argv);
   
};

#endif
