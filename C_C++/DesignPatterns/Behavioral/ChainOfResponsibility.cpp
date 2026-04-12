#include <iostream>
#include <vector>
using namespace std;

class Handler
{
public:
    void SetNext(Handler *handler)
    {
        _successor = handler;
    };
    virtual void Request(int days) = 0;

protected:
    Handler *_successor;
};
class Boss : public Handler
{
public:
    void Request(int days)
    {
        if (days <= 7)
        {
            cout << "The Boss agreed" << endl;
        }
        else
        {
            cout << "Nok" << endl;
        }
    }
};
class Manager : public Handler
{
public:
    void Request(int days)
    {
        if (days <= 3)
        {
            cout << "The Manager agreed" << endl;
        }
        else
        {
            _successor->Request(days);
        }
    }
};
class Director : public Handler
{
public:
    void Request(int days)
    {
        if (days <= 1)
        {
            cout << "The Director agreed" << endl;
        }
        else
        {
            _successor->Request(days);
        }
    }
};

int main()
{
    auto director = new Director();
    auto manager = new Manager();
    auto boss = new Boss();
    manager->SetNext(boss);
    director->SetNext(manager);

    director->Request(1);
    director->Request(3);
    director->Request(7);
}