/*************************************************************************
	> File Name: utsingelton.cpp
	> Created Time: Tue 05 Sep 2017 05:02:51 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <stdio.h>

class singleton
{
    public:
        static singleton* create()
        {
            if(instance == NULL)
            {
                instance = new singleton();
            }
            return instance;
        }
        ~singleton()
        {
            if(instance != NULL)
            {
                delete instance;
                instance = NULL;
            }
        }
    private:
        singleton(){} //构造函数设置为私有
        static singleton* instance;//指向类的指针静态
};

singleton* singleton::instance = NULL;

int main()
{
    singleton* p = singleton::create();
    singleton* p1 = singleton::create();
    singleton* p2 = singleton::create();

    cout << p << endl;
    cout << p1 << endl;
    cout << p1 << endl;

    cout << "test singleton" << endl;
    return 0;
}
