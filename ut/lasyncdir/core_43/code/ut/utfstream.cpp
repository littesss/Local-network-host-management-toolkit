#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>


#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream fin("/etc/exports");
    int counter = 1;
    string line;
    while(!fin.eof())
    {
        getline(fin, line);
        cout << "line "<< counter << ":" << line <<endl;
        counter++;
    }

    fin.close();

    cout << "==========\nend" << endl;
    return 0;
}
