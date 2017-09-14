#include <iostream>
#include <stdio.h>
using namespace std;


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
            if(instance!= NULL)
            {
                delete instance;
                instance = NULL;
            }
        }

    private:
        singleton() {};
        static singleton* instance;
};

singleton* singleton::instance = NULL;

int main()
{
    singleton* p = singleton::create();
    singleton* p1 = singleton::create();
    singleton* p2 = singleton::create();
    printf("p: %x\np1: %x\np2: %x\n", p, p1, p2);

    return 0;
}
