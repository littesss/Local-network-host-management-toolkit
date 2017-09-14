#include <cassert>

#ifndef __LASINGLETON_HEADER__
#define __LASINGLETON_HEADER__

template<typename T>
class LASingletonTemplateBase 
{
    private:
        static T* sm_instance;
    protected:
        LASingletonTemplateBase()
        {
            assert(sm_instance == 0);
            sm_instance = static_cast<T*>(this);
        }
        virtual ~LASingletonTemplateBase()
        {
            assert(sm_instance != 0);
            sm_instance = 0;
        }

    public:
        static T* get_instance_ptr()
        {
            if(sm_instance == 0)
            {
                sm_instance = new T();
            }
            return sm_instance;
        }

        static T& get_instance_ref()
        {
            if(sm_instance == 0)
            {
                sm_instance = new T();
            }
            return *sm_instance;
        }

        static void remove_instance()
        {
            assert(sm_instance);
            if(sm_instance)
            {
                delete sm_instance;
            }
            assert(sm_instance == 0);
        }
};

template<typename T>
T* LASingletonTemplateBase<T>::sm_instance = 0;
#endif
