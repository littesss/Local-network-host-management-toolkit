#include <iostream>
using namespace std;

int main()
{
#ifdef RHEL
    cout<< "RHEL" <<endl;
#endif

#ifdef UBUNTU 
    cout<< "UBUNTU" <<endl;
#endif

    return 0;
}
