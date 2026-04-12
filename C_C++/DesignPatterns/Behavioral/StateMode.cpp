/*
 * 简单地说，状态模式就是状态机设计。其主要用于同一个请求，不同条件下执行不同的功能，作用等同于if...else。
 *
 */

#include <iostream>
#include <list>
using namespace std;

class LiftMachine;
class LiftUpState;
class LiftIdleState;
class LiftDownState;

class AbstractLiftState
{
public:
    virtual void changedState(LiftMachine *machine) = 0;
    virtual void showState() = 0;
};

class LiftMachine
{
public:
    LiftMachine(AbstractLiftState *state) : _state(state){};

    void setGoalFloor(int floor)
    {
        _goalFloor = floor;
    }

    int getGoalFloor() const
    {
        return _goalFloor;
    }

    void setCurrentFloor(int floor)
    {
        _currentFloor = floor;
    }

    int getCurrentFloor()
    {
        return _currentFloor;
    }

    void changedState(AbstractLiftState *state)
    {
        delete _state;
        _state = state;
    }

    void run()
    {
        bool jud = _goalFloor > _currentFloor;
        if (jud)
        {
            for (int i = _currentFloor; i <= _goalFloor; i++)
            {
                setCurrentFloor(i);
                _state->changedState(this);
            }
        }
    }

private:
    int _currentFloor = 1;
    int _goalFloor = 1;
    AbstractLiftState *_state;
};

class LiftUpState : public AbstractLiftState
{
public:
    LiftUpState()
    {
        showState();
    };

    void changedState(LiftMachine *machine)
    {
        if (machine->getGoalFloor() == machine->getCurrentFloor())
        {
            // machine->changedState(new LiftIdleState());
        }
        else if (machine->getGoalFloor() > machine->getCurrentFloor())
        {
            machine->changedState(new LiftUpState());
        }
    }

    void showState()
    {
        cout << "Up!" << endl;
    }
};


class LiftDownState : public AbstractLiftState
{
public:
    LiftDownState() { showState(); };

    void changedState(LiftMachine *machine)
    {
    }

    void showState()
    {
        cout << "Down!" << endl;
    }
};

class LiftIdleState : public AbstractLiftState
{
public:
    LiftIdleState() { showState(); };

    void changedState(LiftMachine *machine)
    {
        if (machine->getGoalFloor() == machine->getCurrentFloor())
        {
            showState();
        }
        else if (machine->getGoalFloor() > machine->getCurrentFloor())
        {
            machine->changedState(new LiftUpState());
        }
        else if (machine->getGoalFloor() < machine->getCurrentFloor())
        {
            machine->changedState(new LiftDownState());
        }
    }

    void showState()
    {
        cout << "Stop!" << endl;
    }
};

int main()
{
    AbstractLiftState *idleState = new LiftIdleState();
    LiftMachine *lift = new LiftMachine(idleState);
    lift->setGoalFloor(3);
    lift->run();
    return 0;
}