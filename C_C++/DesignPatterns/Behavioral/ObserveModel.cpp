/*
* 观察这模式，又名订阅者模式
* 程序中有一个发布者，两个订阅者，订阅者A和订阅者B
* 发布者通过addObserver（）会选择性添加能接受消息的订阅者。发布者发布消息后，订阅者会执行动作
* PS：此外，当发布者较多时，可以让订阅者选择某发布者来获取消息（一个或多个）
*/

#include <iostream>
#include <list>
using namespace std;

class AbstractObserver
{
public:
    virtual void update(string str) = 0;
};

class ObserverA : public AbstractObserver
{
public:
    ObserverA(){};
    void update(string str)
    {
        cout<<"observerA say ： Hello"<<str<<endl;
    }
};

class ObserverB : public AbstractObserver
{
public:
    ObserverB(){};
    void update(string str)
    {
        cout<<"ObserverB  say ： Hi"<<str<<endl;
    }
};


class AbstractSubject
{
public:
    virtual void addObserver(AbstractObserver *ob) = 0;
    virtual void deleteObserver(AbstractObserver *ob) = 0;
    virtual void notify(string str) = 0;

};

class ConcreteSubject : public AbstractSubject
{
public:
    ConcreteSubject(){};

    void addObserver(AbstractObserver *ob)
    {
        obervers.push_back(ob);
    }
    void deleteObserver(AbstractObserver *ob)
    {
        obervers.remove(ob);
    }
    void notify(string str)
    {
        list<AbstractObserver *>::iterator it = obervers.begin();
        for(;it != obervers.end();it++)
        {
            (*it)->update(str);
        }
    }

private:
    list<AbstractObserver *> obervers;
};

int main()
{
    AbstractObserver *obverseA = new ObserverA();
    AbstractObserver *observerB = new ObserverB();
    AbstractSubject *subject = new ConcreteSubject();
    subject->addObserver(obverseA);
    subject->addObserver(observerB);
    subject->notify(",SB");

    return 0;
}