/*************************************************************************
	> File Name: logutils.h
	> Created Time: Wed 06 Sep 2017 01:37:47 PDT
 ************************************************************************/
#ifndef _LOGUTILS_H
#define _LOGUTILS_H

#include <ostream>

#include "singletontemplate.h"

class logutils: public  LASingletonTemplateBase<logutils>
{
    public:
        //构造函数，单例模式 继承单例模板
        logutils(){}; 
        int log(int priority, const char *format, ...);
        int infolog(const char* format, ...);
        int errlog(const char* format, ...);
        int warnlog(const char* format, ...);
        int debuglog(const char* format, ...);

        logutils& operator<<(const char* str);//输出运算符<<重载
        logutils& operator<<(const string str);
        logutils& operator<<(int lhs);

        typedef ostream& (*EOLTYPE)(ostream&); //endl('\n')
        logutils& operator<<(EOLTYPE eol)
        {
            return *this;
        }
};

static logutils& glogger = logutils::get_instance_ref();
#endif
