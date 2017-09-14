/*************************************************************************
	> File Name: ../ut/utconfigparse.cpp
	> Created Time: Tue 05 Sep 2017 02:04:26 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include "configparse.h"
int main()
{
    //configparse parse("lasync.conf");
    //parse.dump();
    configparse* pparse = configparse::get_instance_ptr();
    pparse->initkvmap("../conf/lasync.conf");
    pparse->dump();

    cout << "====configparse  end======" << endl;
    
    string key, value;
    key = "port";

    int ret;
    ret = pparse->getvalue(key, value);
    cout << "port:" << value << endl;    
    return 0;
}
