#include <iostream>
#include <stdlib.h>
using namespace std;
void atexit1()
{
    cout <<  "in 1" << endl;
}

void atexit2()
{
    cout <<  "in 2" << endl;
}

int main()
{
    atexit(atexit1);
    atexit(atexit2);

    cout << "before end" << endl;

    return -1;
}
