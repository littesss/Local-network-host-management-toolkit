#include <iostream>
using namespace std;

#include "nfsutils.h"

int main()
{
    int ret = 0;

    ret = nfsutils::nfsstart();
    cout << "start nfs: " << ret << endl;

    ret = nfsutils::nfsstatus();
    cout << "status nfs: " << ret << endl;

    ret = nfsutils::nfsstop();
    cout << "stop nfs: " << ret << endl;

    ret = nfsutils::nfsstatus();
    cout << "status nfs: " << ret << endl;

    return 0;
}
