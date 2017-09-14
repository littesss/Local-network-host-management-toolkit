/*************************************************************************
	> File Name: utlog.cpp
	> Created Time: Tue 05 Sep 2017 23:56:18 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <syslog.h> //syslog()

#include "logutils.h"
int main()
{
    syslog(LOG_ERR, "this is a test: %d\n", 100000);
    syslog(LOG_INFO, "this is a test: %d\n", 100001);
    syslog(LOG_DEBUG, "this is a test: %d\n", 100002);
    syslog(LOG_PID, "this is a test: %d\n", 100002);

    logutils::get_instance_ptr()->errlog("this is a test");
    logutils::get_instance_ptr()->infolog("this is a test");
    
    logutils& loggerref = logutils::get_instance_ref();

    loggerref << "this is a ref test";
    loggerref << "this is a ref test" << endl;
    
    return 0;
}
