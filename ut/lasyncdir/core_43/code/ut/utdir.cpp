#include <sys/types.h>
#include <dirent.h>

#include "strutils.h"
#include "miscutils.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include <iostream>
using namespace std;

int main()
{
    DIR *pdir = opendir("plugins");

    vector<string> shellscripts;
    vector<string> pythonscripts;
    string script;

    dirent* pent = NULL;
    while(NULL != (pent = readdir(pdir)))
    {
        switch(pent->d_type)
        {
            //case  DT_BLK:
            //    cout << "block" << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

            //case DT_CHR :
            //    cout << "char" << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

            //case DT_DIR :
            //    cout << "dir" << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

            //case DT_FIFO:
            //    cout << "fifo" << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

            //case DT_LNK :
            //    cout << "link" << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

            case DT_REG :
                script = pent->d_name;

        void initscripts();
                if(strutils::endswith(script, ".sh"))
                {
                    shellscripts.push_back(script);
                }
                if(strutils::endswith(script, ".py"))
                {
                    pythonscripts.push_back(script);
                }
                break;

            //case DT_SOCK:
            //    cout << "socket"  << endl;
            //    cout << "name: " << pent->d_name<< endl;
            //    break;

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
