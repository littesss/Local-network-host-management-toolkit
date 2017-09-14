#include <iostream>
#include <string>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#include "command.h"
#include "fsutils.h"

int main()
{
    char buff[1024];
    int ret = fsutils::abspath(".lampt", buff);
    cout << "abspath:" << buff  << endl
        <<"ret: " << ret << endl;

    string host("192.168.51.211");
    string sharedir("/data");

    Command* pcmd = SyncCommand::createcmd(host, sharedir); 

    ret = pcmd->execute();
    delete pcmd;
    pcmd = NULL;


    pcmd = PkgCommand::createcmd();
    pcmd->execute();

    delete pcmd;

    return 0;
}
