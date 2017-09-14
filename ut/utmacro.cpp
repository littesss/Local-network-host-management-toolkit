/*************************************************************************
  > File Name: utmacro.cpp
  > Created Time: Sat 02 Sep 2017 06:54:12 PM PDT
 ************************************************************************/
#include <iostream>
using namespace std;

int main()
{

#ifdef RHEL
    cout << "REHL" << endl;
#endif

#ifdef UBUNTU
    cout << "UBUNTU" << endl;
#endif

    return 0;
}
