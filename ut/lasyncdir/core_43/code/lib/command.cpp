#include <stdlib.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#include "command.h"
#include "nfsutils.h"
#include "fsutils.h"
#include "strutils.h"
#include "miscutils.h"
#include "netutils.h"
#include "configparser.h"

static string LAMPT(".lampt");
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
    char buff[1024];
    ret = fsutils::abspath(LAMPT.c_str(), buff);
    if(!ret)
    {
        return -1;
    }

    string mppath(buff);

    ret = nfsutils::ismounted(host, sharedir, mppath);
    cout << "here!!!!" << endl;
    cout << "ret ismounted: " << ret << endl;

    if(!ret)
    {
        ret = nfsutils::mountnfs(host, sharedir, mppath);
        cout << "ret mount: " << ret << endl;

        if(ret)
        {
            cerr << "nfs mount error" << endl;
            return -1;
        }
    }

    string cmd("cp ");
    string src, dest, opts;
    src = mppath + "/. " ;
    string syncdir;
    ret = gparser->getvalue("syncdir", syncdir);
    ret = fsutils::abspath(syncdir.c_str(), buff);

    cout << "abspath: " << ret << endl;
    if(!ret)
    {
        nfsutils::umount(mppath);
        return -1;
    }
    dest = buff; 
    opts = " -r  --preserve=mode ";
    cmd += src + dest + opts;
    cout << "cmd: " << cmd << endl;
    ret = system(cmd.c_str());
    nfsutils::umount(mppath, 1);

    return miscutils::getexitcode(ret);
}

SyncCommand::~SyncCommand()
{
}

SyncCommand* SyncCommand::createcmd(string host, string sharedir)
{
    SyncCommand* toret = new SyncCommand(host, sharedir);
    return toret;
}

PkgCommand::PkgCommand(string ipkgfile, string rpkgfile)
{
    this->ipkg = ipkgfile;
    this->rpkg = rpkgfile;
}

int PkgCommand::execute()
{
    string syncdir;
    int ret = gparser->getvalue("syncdir", syncdir);
    string ipkgpath(syncdir + "/" + IPKGFILE);
    string rpkgpath(syncdir + "/" + RPKGFILE);

    ifstream ipfile(ipkgpath.c_str());
    ifstream rpfile(rpkgpath.c_str());

    vector<string> ipkgs; 
    vector<string> rpkgs; 

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
    
    copy(ipkgs.begin(), ipkgs.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    copy(rpkgs.begin(), rpkgs.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    
    ret = 0;
    string ipkgstr;
    string rpkgstr;
    
    strutils::join(ipkgs, " ", ipkgstr);
    strutils::join(rpkgs, " ", rpkgstr);

    cout << "ipkgstr:" << ipkgstr << endl;
    cout << "rpkgstr:" << rpkgstr << endl;
        
    string cmd;
    if(!ipkgs.empty())
    {
#ifdef RHEL
        cmd = "yum -y install " + ipkgstr;
#endif

#ifdef UBUNTU
        cmd = "apt-get -y --allow-unauthenticated --force-yes install " + ipkgstr;
#endif
    }

    if(!cmd.empty())
    {
        cmd += ";" ;
    }

    if(!rpkgs.empty())
    {
#ifdef RHEL
        cmd += "yum -y remove " + rpkgstr;
#endif

#ifdef UBUNTU
        cmd = "apt-get -y purge " + ipkgstr;
#endif

    }
    
    cout << "pkg cmd:" << cmd << endl;
    ret = system(cmd.c_str());

    cout << "pkgcmd ret:" << ret << endl;

    return miscutils::getexitcode(ret);
}

PkgCommand* PkgCommand::createcmd(string ipkgfile, string rpkgfile)
{
    PkgCommand * toret = new PkgCommand(IPKGFILE, RPKGFILE);
    return toret;
}

UpdateCommand::UpdateCommand(string upkgfile)
{
    this->upkgfile = upkgfile;

}

int UpdateCommand::execute()
{
    string syncdir;
    int ret = gparser->getvalue("syncdir", syncdir);
    string upkgpath(syncdir + "/" + UPKGFILE);

    ifstream upfile(upkgpath.c_str());

    vector<string> upkgs; 

    string line;
    while(!upfile.eof())
    {
        getline(upfile, line);
        upkgs.push_back(line);
    }

    copy(upkgs.begin(), upkgs.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    
    ret = 0;
    string upkgstr;
    
    strutils::join(upkgs, " ", upkgstr);

    cout << "upkgstr:" << upkgstr << endl;
        
    string cmd;
#ifdef RHEL
        cmd = "yum -y update " + upkgstr;
#endif

#ifdef UBUNTU
        cmd = "apt-get -y upgrade " + upkgstr;
#endif

    ret = system(cmd.c_str());

    return miscutils::getexitcode(ret);

    return 0;
}

UpdateCommand* UpdateCommand::createcmd(string upkgfile)
{
    UpdateCommand* toret = new UpdateCommand(upkgfile);
    return toret;
}

ScriptCommand::ScriptCommand(string scriptdir)
{
    this->plugindir = scriptdir;
}

void ScriptCommand::initscripts() 
{
    DIR *pdir = opendir(plugindir.c_str());

    string script;

    dirent* pent = NULL;
    while(NULL != (pent = readdir(pdir)))
    {
        switch(pent->d_type)
        {
            case DT_REG :
                script = pent->d_name;
                if(strutils::endswith(script, ".sh"))
                {
                    shellscripts.push_back(script);
                }
                if(strutils::endswith(script, ".py"))
                {
                    pythonscripts.push_back(script);
                }
                break;

            default:
                cerr << "unknow" << endl;
                break;
        }
    }
    sort(shellscripts.begin(), shellscripts.end());

    sort(pythonscripts.begin(), pythonscripts.end());

    cout << "shell: ";

    copy(shellscripts.begin(), shellscripts.end(),
            ostream_iterator<string>(cout, " "));
    cout<< endl; 

    cout << "python: ";
    copy(pythonscripts.begin(), pythonscripts.end(),
            ostream_iterator<string>(cout, " "));
    cout<< endl; 
}

int ScriptCommand::execute()
{
    initscripts();
    for(vector<string>::iterator it = shellscripts.begin();
            it != shellscripts.end(); ++it)
    {
        string cmd("cd plugins; sh ");
        cmd += *it;
        int ret = system( cmd.c_str());
        int rcode = miscutils::getexitcode(ret);
        if(rcode)
        {
            cerr << "script: " << *it << " gets error, "
                << "exitcode: " << rcode << endl;
        }
    }

    for(vector<string>::iterator it = pythonscripts.begin();
            it != pythonscripts.end(); ++it)
    {
        string cmd("cd plugins; python ");
        cmd += *it;
        int ret = system( cmd.c_str());
        int rcode = miscutils::getexitcode(ret);
        if(rcode)
        {
            cerr << "script: " << *it << " gets error, "
                << "exitcode: " << rcode << endl;
        }
    }
    return 0;
}

ScriptCommand* ScriptCommand::createcmd(string scriptdir)
{
    ScriptCommand* toret = new ScriptCommand(scriptdir);
    return toret;
}

deque<Command*> extractmsg(char* buff, int bufflen, string& serveraddr, string& sharedir)
{
    deque<Command*> commands;
    Message* pmsg = (Message*)buff;
    Command* pcmd = NULL;
    int cmd = pmsg->cmd;
    int temp = 1 ;
    if(cmd & temp)
    {
        pcmd = SyncCommand::createcmd(serveraddr, sharedir);
        commands.push_back(pcmd);
    }
    temp = temp << 1;
    
    if(cmd & temp)
    {
        pcmd = PkgCommand::createcmd();
        commands.push_back(pcmd);
    }

    temp = temp << 1;
    if(cmd & temp)
    {
        pcmd = UpdateCommand::createcmd();
        commands.push_back(pcmd);
    }

    string plugindir;
    int ret = gparser->getvalue("plugindir", plugindir);
    cout << "plugindir: " << plugindir << endl;
    pcmd = ScriptCommand::createcmd(plugindir);
    commands.push_back(pcmd);

    return commands;
}

