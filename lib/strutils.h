/*************************************************************************
	> File Name: /home/lsh/Desktop/project_sync/lib/strutils.h
	> Created Time: Thu 31 Aug 2017 00:57:43 PDT
 ************************************************************************/
#ifndef __STRUTILS_H
#define __STRUTILS_H

#include <string>
#include <vector>
using namespace std;

class strutils
{
    public:
        static bool startswith(string lhs, string rhs);

        static bool endswith(string lhs, string rhs);

        /*
           intstr="a,bc,cc,ddd,eff", separator=","
           {"a", "bc", "cc", "dd", "eff"}
           */

        static int split(string inputstr, string separator, 
                vector<string>& ret);

        static int join(vector<string> strvec, string separator,
                string& ret);
        static bool inlist(vector<string>& strlist, string& key);

};

#endif
