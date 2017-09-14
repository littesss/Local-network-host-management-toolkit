/*************************************************************************
	> File Name: utfopen.cpp
	> Created Time: Sun 27 Aug 2017 17:23:23 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <stdio.h>

int main()
{
    FILE * fp = NULL; 
    fp = fopen("/etc/exports", "r");

    char  line[1024];
    int count =  0; 
    while(NULL != fgets(line, 1024, fp))
    {
        cout << "line " << ++count << ":" << line ;//fgets()  STOP after a newline/EOF 
    }
    /*
    size_t  nread;
    char buff[10240];
    nread = fread(buff,1 , 10240, fp);// 读的每个数据项1个大小，读10240个

    cout << buff;
     */
    fclose(fp);
    
    return 0;
}
