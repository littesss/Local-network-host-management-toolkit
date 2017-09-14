/*************************************************************************
	> File Name: ../lib/configparse.h
	> Created Time: Tue 05 Sep 2017 01:37:31 PDT
 ************************************************************************/
#ifndef __CONFIGPARSE_H
#define __CONFIGPARSE_H

#include <string>
#include <map>
#include "singletontemplate.h"
//singletont为了取代全局变量
class configparse: public  LASingletonTemplateBase<configparse> 
{
    public:
        configparse();//配置文件
        int getvalue(string& key, string& value);
        int getvalue(const char* key, string& value);
        bool haskey(string& key);//判断是否有key
        int initkvmap(string conf);
        void dump();

    private:
        map<string, string> kvmap;
};
static configparse* gpparse = configparse::get_instance_ptr(); //
#endif
