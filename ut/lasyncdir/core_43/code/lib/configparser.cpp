#include <sys/types.h>
#include <regex.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

#include "configparser.h"

configparser::configparser()
{
}

int configparser::getvalue(char* key, string& value)
{
    string strkey(key);
    return getvalue(strkey, value);
}

int configparser::getvalue(string& key, string& value)
{
    map<string, string>::iterator it = kvmap.find(key); 
    if( it == kvmap.end())
    {
        return 0;
    }

    value = it->second;
    return 1 ;
    
}

bool configparser::haskey(string& key)
{
    map<string, string>::iterator it = kvmap.find(key); 
    if( it == kvmap.end())
    {
        return 0;
    }
    return 1;
}

int configparser::initkvmap(string conf)
{
    ifstream fin(conf.c_str());

    vector<string> lines;
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        lines.push_back(line);
    }

    string pattern("[ \t]*([a-zA-Z0-9]+)[ \t]*=[ \t]*\"([a-zA-Z0-9 /]*)\"[ \t]*");
    int ret;
    regex_t regex;

    ret = regcomp(&regex, pattern.c_str(), REG_EXTENDED);

    regmatch_t pmatch[3];

    for(vector<string>::iterator it = lines.begin();
            it != lines.end(); ++it)
    {
        ret = regexec(&regex, it->c_str(), 3, pmatch, 0);

        if(ret)
        {
            char buff[1024];
            regerror(ret, &regex, buff, 1024);
            //cout << buff << endl;
            continue;
        }
        //cout << "matched" << endl;
        //cout << pmatch[1].rm_so << ": 1 start"<< endl;
        //cout << pmatch[1].rm_eo << ": 1 end"<< endl;
        //
        string key(it->c_str() + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
        string value(it->c_str() + pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
        kvmap[key] = value;
        //cout << "key: " << key << endl;
        //cout << "value: " << value << endl;
    }

    regfree(&regex);
}

void configparser::dump()
{
    for(map<string, string>::iterator it = kvmap.begin();
            it != kvmap.end(); ++it)

    {
        cout << "key:" << it->first << endl
            << "value:" << it->second << endl;
    }
}

