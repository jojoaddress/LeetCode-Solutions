/*
* 观察者模式，又名订阅者模式
* 程序中有一个发布者，两个订阅者，订阅者A和订阅者B
* 发布者通过addObserver（）会选择性添加能接受消息的订阅者。发布者发布消息后，订阅者会执行动作
* PS：此外，当发布者较多时，可以让订阅者选择某发布者来获取消息（一个或多个）
*/

#include <iostream>
#include <list>
using namespace std;

class AbstractObserver;
class AbstractSubject
{
public:
    virtual void addObserver(AbstractObserver *ob) = 0;
    virtual void deleteObserver(AbstractObserver *ob) = 0;
    virtual void notify(string str) = 0;

};

class AbstractObserver
{
public:
    AbstractObserver(){};
    AbstractObserver(AbstractSubject *subject)
    {
        _subject = subject;
        _subject->addObserver(this);
    }
    virtual void update(string str) = 0;

private:
    AbstractSubject *_subject;
};

class ObserverA : public AbstractObserver
{
public:
    ObserverA(){};
    void update(string str)
    {
        cout<<"observerA read ："<<str<<endl;
    }
};

class ObserverB : public AbstractObserver
{
public:
    ObserverB(){};
    void update(string str)
    {
        cout<<"ObserverB  read ： "<<str<<endl;
    }
};

class ObserverC : public AbstractObserver
{
public:
    ObserverC(){};
    ObserverC(AbstractSubject *subject):AbstractObserver(subject)
    {

    };
    void update(string str)
    {
        cout<<"ObserverC  read ： "<<str<<endl;
    }
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


class ConcreteSubjectB : public AbstractSubject
{
public:
    ConcreteSubjectB(){};

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
    AbstractObserver *observseA = new ObserverA();
    AbstractObserver *observerB = new ObserverB();
    AbstractSubject *subject = new ConcreteSubject();
    subject->addObserver(observseA);
    subject->addObserver(observerB);
    subject->notify("SB");

    AbstractSubject *sujectB = new ConcreteSubjectB();
    AbstractObserver *observerC = new ObserverC(sujectB);
    sujectB->addObserver(observseA);
    sujectB->notify("C?");

    return 0;
}