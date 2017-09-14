#include <iostream>
using namespace std;

#include "netutils.h"


int main()
{
    string ifname("enp0s3");
    string brdaddr;
    netutils::getnicbrdaddr(ifname, brdaddr);
    cout << " netutils::getnicbrdaddr(ifname, brdaddr) " <<
        brdaddr << endl;
    return 0;
}
