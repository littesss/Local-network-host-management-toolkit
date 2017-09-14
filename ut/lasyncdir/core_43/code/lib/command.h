#ifndef __COMMMAND__
#define __COMMMAND__

#include <string>
#include <deque>
#include <vector>
using namespace std;

class Command
{
    public:
        virtual int execute() = 0;
        virtual ~Command() {};
};

class SyncCommand: public Command
{
    public:
        SyncCommand(string host, string sharedir); 
        virtual int execute();
        virtual ~SyncCommand();
        static SyncCommand* createcmd(string host, string sharedir);

    private:
        string host;
        string sharedir;
};

class PkgCommand: public Command
{
    public:
        PkgCommand(string ipkgfile, string rpkgfile);
        virtual int execute();
        virtual ~PkgCommand() {}
        static PkgCommand* createcmd(string ipkgfile = "syncdir/.ipkg", 
                string rpkgfile = "syncdir/.rpkg");
    private:
        string ipkg;
        string rpkg;
};

class UpdateCommand: public Command
{
    public:
        UpdateCommand(string upkgfile);
        virtual int execute();
        virtual ~UpdateCommand() {}
        static UpdateCommand* createcmd(string upkgfile = "syncdir/.upkgs");
    private:
        string upkgfile;
};

class ScriptCommand: public Command
{
    public:
        ScriptCommand(string scriptdir);
        virtual int execute();
        virtual ~ScriptCommand() {}
        static ScriptCommand* createcmd(string scriptdir = "plugins");
    private:
        string plugindir;
        vector<string> shellscripts;
        vector<string> pythonscripts;
        void initscripts();
};

deque<Command*> extractmsg(char* buff, int bufflen, string& serveraddr, string& sharedir);

#endif
