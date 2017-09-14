#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    int i = 0;
    while(1)
    {
        sleep(1);
        cout << "counter: " << i++ << endl;
    }
    return 0;
}
