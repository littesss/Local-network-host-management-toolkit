/*************************************************************************
	> File Name: /home/lsh/Desktop/project_sync/lib/strutils.cpp
	> Created Time: Thu 31 Aug 2017 00:59:19 PDT
 ************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

#include <string.h>

#include "strutils.h"

bool strutils::startswith(string lhs, string rhs)//判断rhs是否是lsh的头部
{
    if(lhs.size()==0 && rhs.size()==0 && rhs.size()>=lhs.size())
    {
        return false;
    }
    int i = 0;
    while(lhs[i]!='\0' && rhs[i]==lhs[i] && rhs[i]!='\0')
    {
        ++i;
    }

    if(rhs[i] != '\0')
    {
        return false;
    }
    return true;
}

bool strutils::endswith(string lhs, string rhs)//判断rhs是否是lsh的末尾
{
    if(lhs.size()==0 && rhs.size()==0 && lhs.size()<rhs.size())
    {
        return false;
    }
    
    int i = 0;
    int j = lhs.size() - rhs.size();
    while(lhs[j]!='\0' && rhs[i]!='\0' && lhs[j]==rhs[i])
    {
        ++i;
        ++j;
    }
    if(rhs[i] != '\0')
    {
        return false;
    }
    return true;
}

/*
intstr="a,bc,cc,ddd,eff", separator=","
{"a", "bc", "cc", "dd", "eff"}
*/
//把inputstr 用“，”分割开，并且存放到vector向量里去
int strutils::split(string inputstr, string separator,
        vector<string>& ret) 
{
    if(inputstr.size()==0 && separator.size()==0)
    {
        return -1;
    }
    char* token;
    string temp;
    char*str = (char*)inputstr.data();//?????????
    token = strtok(str,separator.c_str());
    temp = token;
    ret.push_back(temp);
    while(token)
    {
        token = strtok(NULL, separator.c_str());
        if(token)
        {
            temp = token;
            ret.push_back(temp);
        }
    }

    return 0;
}
//把vector向量里面的数据，拼接成string，放到ret中去
int strutils::join(vector<string> strvec, string separator, 
        string& ret)
{
    if(strvec.size() == 0)
    {
        return -1;
    }
    int i=0;
    string temp;
    for(i; i<strvec.size(); ++i)
    {
        temp = strvec[i];
        ret += temp;
        ret += separator;
    }

    return 0; 
}

bool strutils::inlist(vector<string>& strlist, string& key)
{
    if(strlist.empty())
    {
        return 0;
    }
    for(vector<string>::iterator it = strlist.begin();
            it != strlist.end(); ++it)
    {
        if(key == (*it))
        {
            return 1;
        }
    }
    return 0;
}
