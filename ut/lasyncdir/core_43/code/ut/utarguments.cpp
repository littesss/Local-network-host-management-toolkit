#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>


#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    int flags, opt;
    int nsecs, tfnd;
    string machines;

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "fpum:")) != -1) {
        switch (opt) {
            case 'f':
                cout << "f is set " << endl;
                break;
            case 'p':
                cout << "p is set " << endl;
                break;
            case 'u':
                cout << "u is set " <<endl;
                break;
            case 'm':
                machines = optarg;
                cout << machines << endl;
                break;
            default: /* '?' */
                cerr << "error" <<endl;
                exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
