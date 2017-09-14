/*************************************************************************
  > File Name: utregex.cpp
  > Created Time: Mon 04 Sep 2017 09:46:51 PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

#include <sys/types.h>
#include <regex.h>



int main()
{   //第0步：读lasync.conf文本文件
    ifstream fin("lasync.conf");

    vector<string>  lines;
    string line;
    while(!fin.eof())
    {
        getline(fin,line);
        lines.push_back(line);
    }
    copy(lines.begin(), lines.end(), ostream_iterator<string>(cout, "\n"));
    
    //第1步：构造模式匹配的正则表达式
    string pattern("[ \t]*([a-zA-Z0-9]+)[ \t]*=[ \t]*\"([a-zA-Z0-9 /]*)\"[ \t]*");
   
   
    //第2步：编译正则表达式，以pattern模式匹配，放在结构体regex_t 中
    //int regcomp(regex_t *preg, const char *pattern, int cflags);
    int ret;
    regex_t regex;
    ret = regcomp(&regex, pattern.c_str(), REG_EXTENDED);//REG_EXTENDED  正则表达式扩展集
    //迭代 文本文件安行读取
    for(vector<string>::iterator it = lines.begin();
            it != lines.end(); ++it)
    {
        //第3步： 匹配正则表达式
        //int regexec(const regex_t *preg, const char *string, size_t nmatch,regmatch_t pmatch[], int eflags);
        //(先编译好的正则表达式； 目标文本字符串；结构体数组个数；结构体数组，存放文本字符串的位置；0)

        regmatch_t pmatch[3];//结构体数组，用来存放分组位置
        ret = regexec(&regex, it->c_str(), 3,pmatch, 0);
        if(ret) // 未匹配到
        {
        //第4步：匹配出错信息放到errorbuff中去
        //size_t regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size);
            char buff[1024];
            regerror(ret, &regex, buff, 1024);
            continue; //下一行
        }

/********** debug信息*************   
cout << pmatch[0].rm_so << endl;//0
cout << pmatch[0].rm_eo << endl;//19
cout << pmatch[1].rm_so << endl;//0
cout << pmatch[1].rm_eo << endl;//9
cout << pmatch[2].rm_so << endl;//13
cout << pmatch[2].rm_eo << endl;//18
cout << "*it        :" << *it << endl;  //对象 输出运算符重载
cout << "(*it).c_str:" << (*it).c_str() << endl; //对象调方法，string目标文本串  
cout << "it->c_str():" << it->c_str() << endl;//迭代器指向string类，转换成指向字符串类型
***********************************/
       
       
        //第5步：匹配到的，构造对象
        //构造对象： （字符串指针，长度） ，就可以取出该字符串
        string key(it->c_str() + pmatch[1].rm_so, pmatch[1].rm_eo
                -pmatch[1].rm_so);
        string value(it->c_str() + pmatch[2].rm_so, pmatch[2].rm_eo
                -pmatch[2].rm_so);

        cout << "key:" << key << endl;
        cout << "value:" << value << endl;
    }
    

    //第6步：释放对象
    //释放regex_t类型的结构体，以便重新编译其他正则表达式
    //void regfree(regex_t *preg);
    regfree(&regex);
    return 0;
}
