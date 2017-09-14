#include <iostream>
using namespace std;

#include "strutils.h"

int main()
{
    int ret = 0;
    ret = strutils::startswith("this is a test", "this");
    cout << "test startswith" << ret << endl;

    ret = strutils::endswith("this is a test", "test");
    cout << "test endswith" << ret << endl;


    string input("a,b,c,dddd,e,f");
    string sep(",");
    vector<string> out;
    ret = strutils::split(input, sep, out);
    cout << "test split" << endl;

    string joinedstr;
    ret = strutils::join(out, sep, joinedstr);
    cout << "test join" << endl;

    return 0;
}
