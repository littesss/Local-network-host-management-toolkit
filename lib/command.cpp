/*************************************************************************
  > File Name: command.cpp
  > Created Time: Thu 31 Aug 2017 10:31:14 PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <pthread.h>
#include <deque>
using namespace std;

#include <dirent.h> // readdir
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <stdlib.h>
#include <string.h>

#include "nfsutils.h"
#include "command.h"
#include "fsutils.h"
#include "miscutils.h"
#include "strutils.h"
#include "netutils.h"
#include "configparse.h"
#include "logutils.h"

static string LAMPT("./.lampt");//当前目录下建立隐藏目录，提供挂载点
static string IPKGFILE(".ipkgs");
static string RPKGFILE(".rpkgs");
static string UPKGFILE(".upkgs");

SyncCommand::SyncCommand(string host, string sharedir)
{
    this->host = host;
    this->sharedir = sharedir;
}

int SyncCommand::execute()
{
    int ret = 0;
    char buff[521];
    ret = fsutils::abspath(LAMPT.c_str(),buff);//取出绝对路径
    if(!ret)
    {
        return -1;
    }

    
    string mppath(buff);

    ret = nfsutils::ismounted(host, sharedir, mppath);//先检查是否mount
    glogger << "ret ismount :" << ret <<endl;
    if(!ret)    
    {   // 没有mount 先mount
        ret = nfsutils::mountnfs(host, sharedir, mppath);
        glogger << "ret mountd:" << ret << endl;
        if(ret)//没有mount上的话 return -1
        {
            glogger << "mount error" << endl;
            return -1;
        }
    }

    //  copy 文件挂载目录下所有文件到 当前目录syncdir目录下，带权限的
    string cmd("cp ");
    string src, dest, opts;
    src = mppath +"/. ";//包括隐藏目录
    
    string syncdir;
    gpparse->getvalue("syncdir",syncdir);
    ret =  fsutils::abspath(syncdir.c_str(), buff);
    if(!ret)
    {
        nfsutils::umount(mppath); 
        return -1;
    }
    dest = buff;
    opts = " -rf --preserve=mode"; // cp 文件属性不改变，拥有者改变,-rf递归，强力包括目录
    cmd += src  + dest + opts;
    glogger << "cmd:" << cmd << endl;
    ret = system(cmd.c_str());
   
    // umount 必须umount 否则下次 mount 不上 
    ret = nfsutils::umount(mppath,1);
    if(ret)
    {
        glogger << "umount fail" << endl;
        return -1;
    }
    return miscutils::getexitcode(ret); // 获取退出代码
}

SyncCommand::~SyncCommand()
{
}

SyncCommand* SyncCommand::createcmd(string host, string sharedir)
{
    SyncCommand* toret = new SyncCommand(host, sharedir);
    if(!toret)
    {
        return NULL;
    }

    return toret;
}

///////////////// pkg command /////////////////////
PkgCommand::PkgCommand(string ipkgfile, string rpkgfile) 
{
    this->ipkgfile = ipkgfile;
    this->rpkgfile = rpkgfile;
}
int PkgCommand::execute()
{
    glogger << "here????????" << endl;
    string syncdir;
    gpparse->getvalue("syncdir",syncdir);
    string ipkgpath(syncdir + "/" + IPKGFILE);//ipkgpath安装包路径
    string rpkgpath(syncdir +"/" + RPKGFILE);
    glogger<< "ipkgpath:" << ipkgpath << endl; 
    glogger<< "rpkgpath:" << rpkgpath << endl; 
    //read文件
    ifstream ipfile(ipkgpath.c_str());
    ifstream rpfile(rpkgpath.c_str());

    vector<string> ipkgs;//安装包放在vector中
    vector<string> rpkgs;//

    glogger << "-p 222222222222" << endl;
    string line;
    while(!ipfile.eof())
    {
        getline(ipfile, line);
        ipkgs.push_back(line);

    }

    while(!rpfile.eof())
    {
        getline(rpfile, line);
        rpkgs.push_back(line);

    }

    copy(ipkgs.begin(), ipkgs.end(), ostream_iterator<string> (cout, " "));
    glogger << endl;
    copy(rpkgs.begin(), rpkgs.end(), ostream_iterator<string> (cout, " "));
    glogger << endl;

    int ret = 0;
    string ipkgstr;
    string rpkgstr;

    strutils::join(ipkgs, " ", ipkgstr);    
    strutils::join(rpkgs, " ", rpkgstr);    

    glogger << "ipkgstr:" << ipkgstr << endl;
    glogger << "rpkgstr:" << rpkgstr << endl;

    string cmd; 
    //.ipkgs 文件中的需要install的包
    if(!ipkgs.empty())
    {
#ifdef REHL
        cmd = "yum -y install " + ipkgstr;
#endif

#ifdef UBUNTU
        cmd = "sudo apt-get -y --force-yes install " + ipkgstr;
#endif 
    }
    glogger << "install cmd:" << cmd << endl;
    if(!cmd.empty())
    {
        cmd += ";";
    }
    glogger<< "============ install   down remove===========" << endl;
    //.rpkgs 文件中的需要remove的包
    if(!rpkgs.empty())
    {
#ifdef REHL
        cmd += "yum -y remove " + rpkgstr;
#endif

#ifdef UBUNTU
        cmd += "sudo apt-get -y purge " + rpkgstr;
#endif 
    }

    glogger<< "============ ===========" << endl;

    ret = system(cmd.c_str());

    return miscutils::getexitcode(ret);
}

PkgCommand::~PkgCommand()
{
}

//设计模式 工厂模式
PkgCommand* PkgCommand::createcmd(string pkgfile, string rpkgfile )
{
    PkgCommand* toret = new PkgCommand(IPKGFILE, RPKGFILE);
    return toret;
}

/////////////////////UpdateCommand
UpdateCommand::UpdateCommand(string upkgfile)
{
    this->upkgfile = upkgfile;
}
int UpdateCommand::execute()
{
    glogger << "----------here--------------";
    string syncdir;
    gpparse->getvalue("syncdir",syncdir);
    string upkgpath(syncdir +"/" + UPKGFILE);//ipkgpath安装包路径
    
    //read文件
    ifstream upfile(upkgpath.c_str());

    vector<string> upkgs;//安装包放在vector中

    string line;
    while(!upfile.eof())
    {
        getline(upfile, line);
        upkgs.push_back(line);
    }
   
    copy(upkgs.begin(), upkgs.end(), ostream_iterator<string> (cout, " "));
    glogger << endl;

    int ret = 0;
    string upkgstr;

    strutils::join(upkgs, " ", upkgstr);    

    glogger << "upkgstr:" << upkgstr << endl;

    string cmd;

#ifdef REHL
    cmd = "yum -y update " + upkgstr;
#endif

#ifdef UBUNTU
        cmd = "sudo apt-get -y --force-yes upgrade " + upkgstr;
#endif 

    ret = system(cmd.c_str());
    glogger << "pkgcmd ret:" << ret << endl;

    return miscutils::getexitcode(ret);
}

UpdateCommand* UpdateCommand::createcmd(string upkgfile)
{
    UpdateCommand* toret = new UpdateCommand(upkgfile);
    return toret;
}

/////////////////////
void ScriptCommand::initscripts()
{ 
    DIR* pdir = opendir("plugins");
    dirent * prddir = NULL;

  //  vector<string> shellscripts; //shell 放到shell向量去
  //  vector<string> pythonscripts;//Python 放到Python向量去
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
        }                
    }

    glogger << "shell:";
    copy(shellscripts.begin(),shellscripts.end(),ostream_iterator<string> (cout, " "));
    glogger << endl;
    
    glogger << "python:";
    copy(pythonscripts.begin(),pythonscripts.end(),ostream_iterator<string> (cout, " "));
    glogger << endl;

}

ScriptCommand::ScriptCommand(string Scriptdir)
{
    this->plugindir = Scriptdir;     
}

int ScriptCommand::execute()
{
    initscripts();//公有方法调私有方法初始化scripts

    for(vector<string>::iterator it = shellscripts.begin();
            it != shellscripts.end(); ++it)
    {
        string cmd("cd plugins;sh ");
        cmd += *it;
        int ret = system(cmd.c_str());
        int rcode = miscutils::getexitcode(ret);//退出代码异常，打出信息
        if(rcode)
        {
            cerr << "scripts:  " << *it << "  gets error" 
                << " exitcode:"  <<  rcode << endl;
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
                << " exitcode:"  <<  rcode << endl;
        }
    }

    return 0;
}

ScriptCommand* ScriptCommand::createcmd(string Scriptdir)
{
    ScriptCommand* toret = new ScriptCommand(Scriptdir);
    return toret;
}
pthread_mutex_t CommandExecuter::lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  CommandExecuter::cond = PTHREAD_COND_INITIALIZER;
int CommandExecuter::runningflag = 1;
deque<Command*> CommandExecuter::commands = deque<Command*>();
///////解析命令
void CommandExecuter::extractmsg(char* recvbuff, int bufflen, sockaddr_in& peeraddr, string& myname)
{
    string serveraddr(inet_ntoa(peeraddr.sin_addr));
    glogger << "serveraddr" << serveraddr << endl;
   
    Message* pmsg = (Message*)recvbuff;
    cout << "pmsg->cmd:" << pmsg->cmd << endl;
    cout << "pmsg->sharedirlen:" << pmsg->sharedirlen << endl;
    cout << "pmsg->tag:" << pmsg->tag + pmsg->sharedirlen << endl;

    char buff[256];

    buff[pmsg->sharedirlen] = '\0';
    memcpy(buff, pmsg->tag, pmsg->sharedirlen);//不会拷贝‘\0’
    string sharedir(buff);
    strcpy(buff, pmsg->tag + pmsg->sharedirlen);
    string mstr(buff);


    glogger << "share dir:" << sharedir << endl;
    glogger << "machines:" << mstr << endl;

    if(!mstr.empty())
    {
        vector<string> machines;
        strutils::split(mstr,",",machines);
        glogger << "machines:" << endl;

        if(!strutils::inlist(machines, myname))
        {
           return;
        }

    }

    deque<Command*> tempqueue;
    Command* pcmd = NULL;
    int cmd = pmsg->cmd;
    int setbit = 1;
    
    //文件同步 -f
    if(cmd & setbit) //与操作置0
    {
        pcmd = SyncCommand::createcmd(serveraddr, sharedir);
        tempqueue.push_back(pcmd);
    }
    setbit = setbit << 1;
   //软件包安装，卸载 -p
    if(cmd & setbit)
    {
cout << "-p???????????" << endl;
        pcmd = PkgCommand::createcmd();//有默认值
        tempqueue.push_back(pcmd);
    }
    setbit = setbit << 1;

   //软件包更新
    if(cmd & setbit) //-u
    {
        pcmd = UpdateCommand::createcmd();
        tempqueue.push_back(pcmd);
    }
    //setbit = setbit << 1;

    //脚本排序 ，执行
    string plugindir;
    int ret = gpparse->getvalue("plugindir",plugindir);
    glogger << "plugindir:" << plugindir << endl;
    pcmd = ScriptCommand::createcmd(plugindir);
    tempqueue.push_back(pcmd);

    pthread_mutex_lock(&lock);
    copy(tempqueue.begin(),tempqueue.end(), back_inserter(commands));
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

}

void* CommandExecuter::executecmd(void * args)
{
    while(runningflag)
    {
        if(commands.empty())//双检锁
        {
            pthread_mutex_lock(&lock);
            if(commands.empty())
            {
                pthread_cond_wait(&cond, &lock);
                pthread_mutex_unlock(&lock);
            }
            else
            {
                pthread_mutex_unlock(&lock);
                continue;
            }
        }

        else
        {
            while(!commands.empty())
            {
                Command* pcmd = commands[0];

                pthread_mutex_lock(&lock);
                commands.pop_front();//加锁
                pthread_mutex_unlock(&lock);

                pcmd->execute();            
                delete pcmd;
                pcmd = NULL;
            }
        }
    }
    pthread_exit(0);
}

