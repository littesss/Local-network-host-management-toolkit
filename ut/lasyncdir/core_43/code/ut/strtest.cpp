#include <iostream>
#include <string>
using namespace std;

int main()
{
    string aaa("123456");
    string b(aaa.c_str(), 3);
    cout << b << endl;
    return 0;
}
