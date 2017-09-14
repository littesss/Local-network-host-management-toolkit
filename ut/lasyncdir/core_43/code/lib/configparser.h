#ifndef __CONFIGPARSER__
#define __CONFIGPARSER__

#include <string>
#include <map>
#include "singletontemplate.h"
using namespace std;

class configparser: public LASingletonTemplateBase<configparser>
{
    public:
        configparser();
        int getvalue(string& key, string& value);
        int getvalue(char* key, string& value);
        bool haskey(string& key);
        int initkvmap(string conf);
        void dump();

    private:
        map<string, string> kvmap;
};

static configparser* gparser = configparser::get_instance_ptr();

#endif
