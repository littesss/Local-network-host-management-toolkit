#include <syslog.h>

#include <stdio.h>
#include <stdarg.h>

#include <iostream>
using namespace std;

#include "logutils.h"

static int size = 4096;

logutils& logutils::operator<<(char* str)
{
    syslog(LOG_INFO, "%s", str); 
    closelog();
    return *this;
}

int logutils::log(int priority, const char *fmt, ...)
{
    char p[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    syslog(priority, "%s", p); 
    closelog();

    return 0;
}

int logutils::infolog(const char *fmt, ...)
{
    char p[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    syslog(LOG_INFO, "%s", p); 
    closelog();

    return 0;
}

int logutils::errlog(const char *fmt, ...)
{
    char p[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    syslog(LOG_ERR, "%s", p); 
    closelog();

    return 0;
}

int logutils::warnlog(const char *fmt, ...)
{
    char p[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    syslog(LOG_WARNING, "%s", p); 
    closelog();

    return 0;
}

int logutils::debuglog(const char *fmt, ...)
{
    char p[size];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    syslog(LOG_DEBUG, "%s", p); 
    closelog();

    return 0;
}
