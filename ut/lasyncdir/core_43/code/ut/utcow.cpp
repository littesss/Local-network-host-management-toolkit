#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int main()
{
    string a("abc");
    string b(a);
    printf("a: %x\n", a.c_str());
    printf("b: %x\n", b.c_str());

    b = "aaaa";
    printf("a: %x\n", a.c_str());
    printf("b: %x\n", b.c_str());

    return 0;
}
