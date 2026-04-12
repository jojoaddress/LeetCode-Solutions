/*
 *为一个蛋糕添加装饰。蛋糕店刚生产出来的蛋糕是最原始的，只是一个蛋糕原型，
 *我们需要再这个蛋糕上加上奶油，加上巧克力，加上水果，写上字等等，将原始蛋糕作为一个Cake类，我们给这个Cake类的对象作装饰，
 *为了不破坏开放-封闭原则，也为了更好的拓展，我们不能直接在Cake这个类里修改，而通过装饰器来给这个蛋糕做装饰
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Cake
{
public:
    virtual void showCake() = 0;
    string cakeName;
};

class ConcreteCake : public Cake
{
public:
    void setName(string str)
    {
        this->cakeName = str;
    }
    void showCake()
    {
        cout << this->cakeName << endl;
    }
};

class Decorator : public Cake
{
public:
    virtual void showCake() = 0;

protected:
    Cake *_cake;
};

class MilkDecorator : public Decorator
{
public:
    MilkDecorator(Cake *cake)
    {
        this->_cake = cake;
    }
    void showCake()
    {
        cout << _cake->cakeName + "+Milk" << endl;
    }
};

class CholateDecorator : public Decorator
{
public:
    CholateDecorator(Cake *cake)
    {
        this->_cake = cake;
    }
    void showCake()
    {
        cout << _cake->cakeName + "+Cholate" << endl;
    }
};

int main()
{
    auto cake = new ConcreteCake();
    cake->setName("su");

    auto milkDecorator = new MilkDecorator(cake);
    milkDecorator->showCake();

    auto cholateDecorator = new CholateDecorator(cake);
    cholateDecorator->showCake();
}