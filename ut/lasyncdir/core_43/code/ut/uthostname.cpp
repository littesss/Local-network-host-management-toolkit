#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    char buff[1024];
    gethostname(buff, 1024);
    cout << buff << endl;
    return 0;
}
