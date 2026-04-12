#include <iostream>
#include <vector>
using namespace std;

class Receiver
{
public:
    void DoCommandA()
    {
        cout << "Excute cmd A!"<<endl;
    }
    void DoCommandB()
    {
        cout << "Excute cmd B!"<<endl;
    }
};

class Command
{
public:
    virtual void Excute() = 0;
};

class CommandA : public Command
{
public:
    CommandA(Receiver *rec)
    {
        this->receiver = rec;
    }
    void Excute()
    {
        receiver->DoCommandA();
    }
private:
    Receiver *receiver;
};

class CommandB : public Command
{
public:
    CommandB(Receiver *rec)
    {
        this->receiver = rec;
    }
    void Excute()
    {
        receiver->DoCommandB();
    }
private:
    Receiver *receiver;
};

class Invoke
{
public:
    void Add(Command *cmd)
    {
        cmds.push_back(cmd);
    }

    void Remove(Command *cmd)
    {
        // cmds.erase(find(cmds.begin(),cmds.end(),cmd));
        // cmds.erase(remove(cmds.begin(), cmds.end(), cmd), cmds.end());
        auto it = cmds.begin();
        while(it != cmds.end())
        {
            if(*it == cmd)
            {
                cmds.erase(it);
                break;
            }
            ++it;
        }

    }

    void Notify()
    {
        auto it = cmds.begin();
        for(;it != cmds.end(); it++)
        {
            (*it)->Excute();
        }
    }
private:
    vector<Command*> cmds;
};



int main()
{
    Receiver *rec = new Receiver();
    auto cmdA = new CommandA(rec);
    auto cmdB = new CommandB(rec);
    Invoke *invoke = new Invoke();
    invoke->Add(cmdA);
    invoke->Add(cmdB);
    invoke->Remove(cmdB);
    invoke->Notify();
    return 0;
}