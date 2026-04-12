#include <iostream>
using namespace std;

class Product
{
public:
    virtual void show() = 0;
};

class ConcreteP1 : public Product
{
public:
    void show()
    {
        cout << "P1" << endl;
    }
};

class ConcreteP2 : public Product
{
public:
    void show()
    {
        cout << "P2" << endl;
    }
};
class Factory
{
public:
    virtual Product *createP1() = 0;
    virtual Product *createP2() = 0;
};

class ConcreteFactory : public Factory
{
public:
    Product *createP1()
    {
        return new ConcreteP1;
    }
     Product *createP2()
    {
        return new ConcreteP2;
    }
};

int main()
{
    Factory *factory = new ConcreteFactory();
    auto p1 = factory->createP1();
    p1->show();
    return 0;
}