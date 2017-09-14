/*************************************************************************
  > File Name: broadaddr.cpp
  > Created Time: Wed 30 Aug 2017 13:41:01 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include "netutils.h"

int main()
{
    string ifname("ens33");
    string brdaddr;
    netutils::getnicbrdaddr(ifname, brdaddr);
    
    cout << "netutils::getnicbrdaddr(ifname, brdaddr)" << endl;
    cout << brdaddr << endl; 
    return 0;
}

