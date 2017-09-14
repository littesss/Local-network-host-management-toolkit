/*************************************************************************
	> File Name: utcommand.cpp
	> Created Time: Thu 31 Aug 2017 13:54:26 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fsutils.h"
#include "command.h"

int main()
{
    char buff[256];
    int ret = fsutils::abspath("./.lampt", buff);
    if(!ret)
    {
        perror("ret");
        exit(1);
    }
    cout << "absPath:" << buff << endl
        <<"strlen:" << ret << endl;

    string host("172.20.10.9");
    string sharedir("/NfsShare");
    Command* pcmd = SyncCommand::createcmd(host, sharedir);//多态 父类指针指子类
    ret = pcmd->execute(); 
    delete pcmd;
    pcmd = NULL;

 
    pcmd = PkgCommand::createcmd();  // 多态 包安装升级同步

    cout << "=====PkgCommand=====" << endl;
    ret = pcmd->execute();
    cout << "=====PkgCommand end=====" << endl;
    delete pcmd;
    pcmd = NULL;
/*
    pcmd = UpdateCommand::createcmd();  // 多态  包更新同步
    cout << "======UpdateCommand=======" << endl;
    ret = pcmd->execute();
    cout << "======UpdateCommand end====" << endl;
    delete pcmd;
    pcmd = NULL;


    pcmd = ScriptCommand::createcmd("plugins");  // 多态 脚本文件排序执行同步

    cout << "======ScriptCommand=======" << endl;
    ret = pcmd->execute();
    cout << "======ScriptCommand end====" << endl;
    delete pcmd;
    pcmd = NULL;

*/


    return 0;
}
