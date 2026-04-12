/*
* 简而言之，备忘录模式分为三部分，备忘录、发送者、管理者。其中备忘录负责备份发送者的数据，管理者负责发送者的存储操作，以及发送者的备份操作。
*/
#include <iostream>
#include <vector>
using namespace std;

class Memento
{
public:
    Memento(string state) : _state(state){};
    string getState() const
    {
        return _state;
    }

private:
    string _state;
};

class Originator
{
public:
    Memento saveMemento()
    {
        return Memento(_state);
    }

    void restoreMemento(const Memento &memento)
    {
        _state = memento.getState();
    }

    void setState(string state)
    {
        _state = state;
    }

    string getState() const
    {
        return _state;
    }

private:
    string _state;    
};

class CareTaker
{
public:
    CareTaker(Originator *orig):_orig(orig){};

    void addMemento()
    {
        mementos.push_back(_orig->saveMemento());
    }

    void removeMemento(int index)
    {
        mementos.erase(mementos.begin()+(index-1));
    }

    void getMemento(int index)
    {
        return _orig->restoreMemento(mementos.at(index));
    }

    void setOriginatorState(string state)
    {
        _orig->setState(state);
    }

    string getOriginatorState() const
    {
        return _orig->getState();
    }


private:
    vector<Memento > mementos;
    Originator *_orig;
};

int main()
{
    Originator *orig = new Originator();
    CareTaker *taker = new CareTaker(orig);
    taker->setOriginatorState("V_1");
    taker->addMemento();
    taker->setOriginatorState("V_2");
    taker->addMemento();
    taker->setOriginatorState("V_3");
    taker->addMemento();

    //回到指定历史版本V_2
    taker->getMemento(1);
    cout<<taker->getOriginatorState()<<endl;

    //回到指定历史版本V_1
    taker->getMemento(0);
    cout<<taker->getOriginatorState()<<endl;

    return 0;
}