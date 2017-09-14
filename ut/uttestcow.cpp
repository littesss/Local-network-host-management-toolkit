/*************************************************************************
	> File Name: testcow.cpp
	> Created Time: Mon 28 Aug 2017 09:43:17 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <string>

int main()
{
    string a("AAA");
    string b(a);
    cout << &a << endl;
    cout << &b << endl;
    
    b = "BBB";
    cout << &a << endl;
    cout << &b << endl;
    return 0;
}
