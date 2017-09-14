/*************************************************************************
	> File Name: utfstream.cpp
	> Created Time: Sun 27 Aug 2017 18:50:07 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

/*
int main()
{
    ifstream fin("/etc/exports");
    
    int count = 1;
    string line;

    while(!fin.eof())
    {
        getline(fin, line);
        cout << "line" << count++ << ":" << line << endl ;
    }

    fin.close();
    return 0;
}
*/

int main()
{
    ifstream fin;
    fin.open("/etc/exports");
    if(!fin)
    {
        cout << "fail" << endl;
        return 0;
    }

    char buff[1024];
    fin.read(buff, 1024);
    cout << buff ;

    cout << "===============parse============" <<  endl;
    
    char * saveptr;
    char * token;
    token = strtok_r(buff, "\n", &saveptr);
    if(token == NULL)
    {
        cout << "file is NULL!!" << endl;
        return 0;
    }
    cout << "line 1:" << token << endl;

    int count = 1;
    while(NULL != (token = strtok_r(NULL, "\n", &saveptr))) 
    {
        cout << "line" << ++count << ":" << token << endl;
    }

    //fin.getline()
    return 0;
}
