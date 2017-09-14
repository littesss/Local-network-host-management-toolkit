/*************************************************************************
  > File Name: command.h
  > Created Time: Thu 31 Aug 2017 08:20:18 PDT
 ************************************************************************/
#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include <deque>
#include <vector>
using namespace std;

class Command
{
    public:
        virtual int execute() = 0;
        virtual ~Command() {} 

};

class SyncCommand: public Command
{
    public:
        SyncCommand(string host, string sharedir);
        virtual int execute();
        virtual ~SyncCommand();
        static SyncCommand* createcmd(string host, string sharedir);

    private://主机名 分享目录
        string host;
        string sharedir;
};

class PkgCommand: public Command
{
    public:
        PkgCommand(string ipkgfile, string rpkgfile);//安装和移除包 
        virtual int execute();
        virtual ~PkgCommand();
        static PkgCommand* createcmd(string ipkgfile = "syncdir/.ipkgs",
                string rpkgfile = "syncdir/.rpkgs");//设计模式 工厂模式

    private:
        string ipkgfile;
        string rpkgfile;
};

class UpdateCommand: public Command
{
    public:
        UpdateCommand(string upkgfile);
        virtual int execute();
        virtual ~UpdateCommand(){}
        static UpdateCommand* createcmd(string upkgfile = "syncdir/.upkgs");
        
    private:
        string upkgfile;

};

class ScriptCommand: public Command
{
    public:
        ScriptCommand(string Scriptdir);
        virtual int execute();
        virtual ~ScriptCommand(){}
        static ScriptCommand* createcmd(string Scriptdir = "plugins");
    private:
        string plugindir;
        vector<string> shellscripts;
        vector<string> pythonscripts;
        void initscripts();
};

struct sockaddr_in; //perraddr
class CommandExecuter
{
    public:
    //提取主机发过来的Messages
    static void extractmsg(char* recvbuff, int bufflen, sockaddr_in& peeraddr, string& myname);
    
    static void* executecmd(void* args);
    static int runningflag;
    
    private:
    static deque<Command*> commands;
    static pthread_mutex_t lock;//互斥锁
    static pthread_cond_t  cond;//条件变量

};

#endif
