/*************************************************************************
  > File Name: utreaddir.cpp
  > Created Time: Sun 03 Sep 2017 19:21:00 PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

#include <sys/types.h>
#include <dirent.h> // readdir

#include "strutils.h"
#include "miscutils.h"

int main()
{

    //    DIR* pdir = opendir("/dev");
    DIR* pdir = opendir("plugins");
    dirent * prddir = NULL;

    vector<string> shellscripts; //shell 放到shell向量去
    vector<string> pythonscripts;//Python 放到Python向量去
    string script;  //读取文件名

    while(NULL != (prddir = readdir(pdir)))
    {
        switch(prddir->d_type)
        {
            case DT_REG:  
                script = prddir->d_name;
                if(strutils::endswith(script,".sh"))
                {
                    shellscripts.push_back(script);
                }
                if(strutils::endswith(script,".py"))
                {
                    pythonscripts.push_back(script);
                }    
               //sort  脚本文件
               sort(shellscripts.begin(),shellscripts.end());   
               sort(pythonscripts.begin(),pythonscripts.end());  

                break; 

            default:
                cout << "Other dir:" << prddir->d_name << endl;

                /*
                   case DT_BLK:
                   cout<< "block" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break;   

                   case DT_CHR: 
                   cout << "char" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break;

                   case DT_DIR:
                   cout << "direction" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break;    

                   case DT_FIFO:
                   cout << "pipe" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break; 

                   case DT_LNK:  
                   cout << "link" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break; 

                   case DT_REG:  
                   cout << "regular" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break; 

                   case DT_SOCK:
                   cout << "socket" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break; 

                   case DT_UNKNOWN:
                   cout << "unknow" << endl;
                   cout << "name:" << prddir->d_name << endl;
                   break; 
                   */
        }
    }

    cout << "shell:";
    copy(shellscripts.begin(),shellscripts.end(),ostream_iterator<string> (cout, " "));
    cout << endl;
    
    cout << "python:";
    copy(pythonscripts.begin(),pythonscripts.end(),ostream_iterator<string> (cout, " "));
    cout << endl;

    for(vector<string>::iterator it = shellscripts.begin();
            it != shellscripts.end(); ++it)
    {
        string cmd("cd plugins;sh ");
        cmd += *it;
        int ret = system(cmd.c_str());
        int rcode = miscutils::getexitcode(ret);
        if(rcode)
        {
            cerr << "scripts:" << *it << "gets error" << endl;
        }
    }

    for(vector<string>::iterator it = pythonscripts.begin();
            it != pythonscripts.end(); ++it)
    {
        string cmd("cd plugins;python ");
        cmd += *it;
        int ret = system(cmd.c_str());
        int rcode = miscutils::getexitcode(ret);
        if(rcode)
        {
            cerr << "scripts:" << *it << "gets error" 
                << "exitcode:"  <<  rcode << endl;
        }
    }
    return 0;
}
