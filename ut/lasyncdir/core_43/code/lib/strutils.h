#ifndef __STRUTILS__
#define __STRUTILS__

#include <string.h>

#include <string>
#include <vector>
using namespace std;

class strutils
{
    public:
        static int startswith(string lhs, string rhs);

        static int endswith(string lhs, string rhs);

        /*
           intstr="a,bc,cc,ddd,eff", separator=","
           {"a", "bc", "cc", "dd", "eff"}
           */

        static int split(string inputstr, string separator, 
                vector<string>& ret);

        static int join(vector<string> strvec, string separator,
                string& ret);

};

#endif
