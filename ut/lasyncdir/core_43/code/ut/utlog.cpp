#include <iostream>
#include <syslog.h>

using namespace std;

#include "logutils.h"

int main()
{
    syslog(LOG_ERR, "this is a test: %d\n", 100000);
    syslog(LOG_INFO, "this is a test: %d\n", 100001);
    syslog(LOG_DEBUG, "this is a test: %d\n", 1000002);
    closelog();

    logutils::get_instance_ptr()->errlog("this is an err test");
    logutils::get_instance_ptr()->infolog("this is an info test");
    
    logutils& loggerref = logutils::get_instance_ref();

    loggerref << "this is a ref test";
    loggerref << "this is a ref test" << endl;

    
    return 0;
}
