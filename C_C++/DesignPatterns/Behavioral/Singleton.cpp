#include <iostream>
using namespace std;

//懒汉式   对象的创建在第一次调用getInstance函数时创建
//懒汉式是线程不安全的
class SingletonLazy
{
private:
    /* data */
public:
    static SingletonLazy *getInstance();
};

SingletonLazy *SingletonLazy::getInstance()
{   
    static SingletonLazy *instance =NULL;
    if(instance == NULL)
    {
        instance = new SingletonLazy;
    }
    return instance;
}
