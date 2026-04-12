#include <iostream>
#include <list>
using namespace std;

class War;
class State
{
public:
    virtual void currentState(War *war) = 0;
};

class War
{
public:
    War(State *state):_state(state),_day(0){}

    void setDays(int day)
    {
        _day = day;
    }
    int getDays()
    {
        return _day;
    }

    void setState(State *state)
    {
        delete _state;
        _state = state;
    }
    void getState()
    {
        _state->currentState(this);
    }

private:
    int _day=0;
    State *_state;
};

class LastWarState : public State
{
public:
    void lastWar(War *war)
    {
        if (war->getDays()<30)
        {
            cout<<"It`s lastWar!"<<endl;
        }
        else
        {
            cout<<"War is end!"<<endl;
        }
    }
    void currentState(War *war)
    {
        lastWar(war);
    }
};

class MiddleWarState : public State
{
public:
    void middleWar(War *war)
    {
        if (war->getDays()<20)
        {
            cout<<"It`s middleWar!"<<endl;
        }
        else
        {
            war->setState(new LastWarState());
            war->getState();
        }
    }
    void currentState(War *war)
    {
        middleWar(war);
    }

};

class EarlyWarState : public State
{
public:
    void earlyWar(War *war)
    {
        if (war->getDays()<10)
        {
            cout<<"It`s earlyWar!"<<endl;
        }
        else
        {
            war->setState(new MiddleWarState());
            war->getState();
        }
    }
    void currentState(War *war)
    {
        earlyWar(war);
    }
};

int main()
{
    War *war = new War(new EarlyWarState());
    for(int i=1;i<35;i++)
    {
        war->setDays(i);
        war->getState();
    }
    return 0;
}