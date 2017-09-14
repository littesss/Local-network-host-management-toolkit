#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nfsutils.h"
#include "strutils.h"
#include "miscutils.h"

#ifdef RHEL
static string svc = "nfs.service";
#endif
#ifdef UBUNTU
static string svc = "nfs-kernel-server.service";
#endif

int nfsutils::nfsstart()
{
    string cmd("systemctl start " + svc + "  >/dev/null 2>&1");
    int ret = system(cmd.c_str());
    return miscutils::getexitcode(ret);
}


int nfsutils::nfsstop()
{
    string cmd("systemctl stop " + svc + "  >/dev/null 2>&1");
    int ret = system(cmd.c_str());
    return miscutils::getexitcode(ret);
}

int nfsutils::nfsstatus()
{
    string cmd("systemctl status " + svc + " >/dev/null 2>&1");
    int ret = system(cmd.c_str());
    return miscutils::getexitcode(ret);
}

bool nfsutils::isexported(string sharedir)
{
    cout <<  "isexported " << endl;
    string cmd("exportfs |grep -w '" + sharedir +"'");
    int ret = system(cmd.c_str());
     
    int exitcode = miscutils::getexitcode(ret);
    return !exitcode;
}

int nfsutils::confignfs(string sharedir, string nfsopts)
{
    string filename("/etc/exports"); 
    ifstream fin(filename.c_str());
    
    vector<string> lines;
    string line;

    while(!fin.eof())
    {
       getline(fin, line);
       lines.push_back(line);
    }
    fin.close();

    for(vector<string>::iterator it = lines.begin();
            it != lines.end(); ++it)
    {
        if(strutils::startswith(*it, sharedir + " ")
                || strutils::startswith(*it, sharedir + "\t"))
        {
            cout << " in config nfs return" << endl;
            return 0;
        }
    }

    string nfsline(sharedir + " " + nfsopts);
    lines.push_back(nfsline);


    ofstream fout(filename.c_str());
    copy(lines.begin(), lines.end(), ostream_iterator<string>(fout, "\n"));
    fout.close();

    return 0;

    //open()
    //write()
    //close()
    /*
       1. manupulate the "/etc/exports" with linux system calls
       a. open
       b. close
       c. read
       d. write

       2. manupulate the "/etc/exports" with c FILE related apis
       a. fopen 
       b. fwrite
       c. fread
       d. fclose

       3. manupulate the "/etc/exports" with c++ ifstream/ofstream apis
       a. ifstream
       b. ofstream
       c. operator "<<"
       d. operator ">>"

       string utils 
       1. int startswith(string lhs, string rhs);
       2. int endswith(string lhs, string rhs);
       intstr="a,bc,cc,ddd,eff", separator=","
       {"a", "bc", "cc", "dd", "eff"}
       3. vector<string> split(string inputstr, string separator)
       4. int join(vector<string> strvec, string separator)

*/

}

//client side 
int nfsutils::mountnfs(string nfsloc, string sharedir, 
        string mpt, string mountopts)
{
    string cmd("mount ");

    cout << "here" << endl;

    cmd += mountopts + nfsloc + ":" + sharedir + " " + mpt; 

    cout << "mount cmd: " << cmd << endl;

    int ret = system(cmd.c_str());

    return miscutils::getexitcode(ret);

}

bool nfsutils::ismounted(string nfsloc, string sharedir, string mpt)
{
    return 0;
    string cmd("mount |grep ");
    cmd += "'" + nfsloc + ":" + sharedir + "'";

    int ret = system(cmd.c_str());
    int exitcode = miscutils::getexitcode(ret);

    if(exitcode != 0)
    {
        return false;
    }

    FILE* output = popen(cmd.c_str(), "r" );
    char buff[512];
    memset(buff, 0, 512);

    int nread = fread(buff, sizeof(char), 512, output);
    fclose(output);

    cout << buff << endl;

    string content(buff); 
    string mountstr = nfsloc+":"+sharedir + " on " + mpt;

    ret = strutils::startswith(content, mountstr);

    return ret;
}

int nfsutils::umount(string mpt, int isforce)
{
    string cmd("umount");
    if(isforce)
    {
        cmd += " -f ";
    }
    cmd += mpt;
    int ret = system(cmd.c_str());
    return miscutils::getexitcode(ret);
}
