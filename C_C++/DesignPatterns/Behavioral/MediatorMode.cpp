/*
 * �н���ģʽ
 * ��ģʽ����Ȥ�ĵط����ڣ����κ�һ��ͨѶ��������Ϣʱ��ͨ���н�Mediator������ͨѶ�����ܽ��յ���Ϣ
 * ��һ���н�Mediaor��Է����߱����������Σ��Է�ֹ������Ҳ�ܽ�����Ϣ
 * ֵ��һ����ǣ�ͨѶ������н�Mediator������ʹ�õģ���ȥ�����ġ��н顣����һ��۲���ģʽ���۲��߱�����������Subject�кܴ�����
 */
#include <iostream>
#include <list>
using namespace std;

class AbstractColleague;
class AbstractMediator
{
public:
    virtual void send(string message, AbstractColleague *colleague) = 0;
    virtual void add(AbstractColleague *colleague) = 0;
};

class AbstractColleague
{
public:
    AbstractMediator *getMediator()
    {
        return _mediator;
    }

    void setMediator(AbstractMediator *const mediator)
    {
        _mediator = mediator;
        _mediator->add(this);
    }

    AbstractColleague(){}
    AbstractColleague(AbstractMediator *mediator)
    {
        _mediator = mediator;
        _mediator->add(this);
    }

    virtual void notify(string message) = 0;

private:
    AbstractMediator *_mediator;
};

class ConcreteColleagueA : public AbstractColleague
{
public:
    ConcreteColleagueA(AbstractMediator *mediator) : AbstractColleague(mediator)
    {
    }

    void send(string message)
    {
        getMediator()->send(message, this);
    }

    void notify(string message)
    {
        cout << "A receive:" << message << endl;
    }
};

class ConcreteColleagueB : public AbstractColleague
{
public:
    ConcreteColleagueB(AbstractMediator *mediator) : AbstractColleague(mediator)
    {
    }

    void send(string message)
    {
        getMediator()->send(message, this);
    }

    void notify(string message)
    {
        cout << "B receive:" << message << endl;
    }
};

class ConcreteColleagueC : public AbstractColleague
{
public:
    ConcreteColleagueC(){}
    ConcreteColleagueC(AbstractMediator *mediator) : AbstractColleague(mediator)
    {
    }

    void send(string message)
    {
        getMediator()->send(message, this);
    }

    void notify(string message)
    {
        cout << "C receive:" << message << endl;
    }
};

class ConcreteMediator : public AbstractMediator
{
public:
    void add(AbstractColleague *colleague)
    {
        colleagues.push_back(colleague);
    }

    void send(string message, AbstractColleague *colleague)
    {
        list<AbstractColleague *>::iterator it = colleagues.begin();
        for (; it != colleagues.end(); it++)
        {
            if (*it != colleague)
                (*it)->notify(message);
        }
    }

private:
    list<AbstractColleague *> colleagues;
};

int main()
{
    AbstractMediator *mediator = new ConcreteMediator();
    ConcreteColleagueA *colleagueA = new ConcreteColleagueA(mediator);
    ConcreteColleagueB *colleagueB = new ConcreteColleagueB(mediator);
    ConcreteColleagueC *colleagueC = new ConcreteColleagueC();
    colleagueC->setMediator(mediator);

    colleagueA->send("this is A");

    cout << "_____" << endl;

    colleagueC->send("this is B");

    cout << "______" << endl;

    colleagueB->send("C is not B!");
    return 0;
}