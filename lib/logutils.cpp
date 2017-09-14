/*************************************************************************
  > File Name: logutils.cpp
  > Created Time: Thu 07 Sep 2017 06:16:22 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <syslog.h>

#include <stdio.h>
#include <stdarg.h>// va_list

#include "logutils.h"

static int size = 4096;

//输出运算符重载
logutils& logutils::operator<<(const char* str)
{
    syslog(LOG_INFO, "%s", str);
    closelog();

    return *this;
}

logutils& logutils::operator<<(int lhs)
{
    syslog(LOG_INFO, "%d", lhs);
    closelog();

    return *this;
}

logutils& logutils::operator<<(const string str)
{
    syslog(LOG_INFO, "%s", str.c_str());
    closelog();

    return *this;
}

//priority
int logutils::log(int priority, const char *fmt, ...)//可变参不能复用
{
    //可变参
    char p[size]; // 4k大小
    va_list ap;//宏

    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);
    
    //syslog()
    syslog(priority, "%s", p);
    closelog();
    return 0;
}

//infolog()
int logutils::infolog(const char* fmt, ...)
{
    char p[size]; // 4k大小
    va_list ap;//宏

    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);
    
    //syslog()
    syslog(LOG_INFO, "%s", p);
    closelog();
    return 0;

}

//errlog()
int logutils::errlog(const char* fmt, ...)
{
    char p[size]; // 4k大小
    va_list ap;//宏

    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);
    
    //syslog()
    syslog(LOG_ERR, "%s", p);
    closelog();
    return 0;
}

//warnlog()
int logutils::warnlog(const char* fmt, ...)
{
    char p[size]; // 4k大小
    va_list ap;//宏

    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);
    
    //syslog()
    syslog(LOG_WARNING, "%s", p);
    closelog();
    return 0;
}

//debuglog()
int logutils::debuglog(const char* fmt, ...)
{
    char p[size]; // 4k大小
    va_list ap;//宏

    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);
    
    //syslog()
    syslog(LOG_DEBUG, "%s", p);
    closelog();
    return 0;
}
