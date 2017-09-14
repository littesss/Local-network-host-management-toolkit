/*************************************************************************
	> File Name: solfarray.cpp
	> Created Time: Mon 28 Aug 2017 18:16:53 PDT
 ************************************************************************/
#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <string.h>

struct Message
{
    int cmd;
    char tag[0];//不占空间
};

int main()
{
    string machine ("test.....");

    int bufflen = sizeof(Message) + machine.length();
    char* pbuff = (char*) malloc(bufflen+1);//开辟一个char*类型的指针,因为柔性数组后面跟的是char ×

    memset(pbuff, 0, bufflen);//置位
    pbuff[bufflen] = '\0';

    Message * pmsg = (Message*)pbuff; //定义一个Message * 类型的指针，指向buff
    pmsg->cmd = 7;
    memcpy(pmsg->tag, machine.c_str(), bufflen);

    cout << "cmd :" << pmsg->cmd << endl;
    cout << "buff:" << pmsg->tag << endl;
    return 0;
}
