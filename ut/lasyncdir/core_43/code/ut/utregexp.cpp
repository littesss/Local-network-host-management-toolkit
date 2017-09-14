#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

#include <sys/types.h>
#include <regex.h>

#include "configparser.h"

int main()
{
    configparser* pparser = configparser::get_instance_ptr();

    pparser->initkvmap("lasync.conf");
    pparser->dump();
    
    cout << "new parser" << endl;
    configparser newparser;
    newparser.dump();
    cout << "dump" << endl;


    string key, value;
    key = "port";

    int ret;
    ret = pparser->getvalue(key, value);

    cout << "port:" << value << endl;
    return 0;
}
