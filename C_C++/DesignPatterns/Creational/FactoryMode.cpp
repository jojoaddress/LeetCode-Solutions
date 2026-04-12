#include <iostream>
using namespace std;

/*可以想象成
    A：苹果 A1：中国苹果 A2：日本苹果
    B：香蕉 B1：中国香蕉 B2：日本香蕉
    抽象工厂模式，可以通过简单的创建对象 筛选出苹果-中国*/

//A product
class AbstractProductA
{
public:
    virtual void showName() = 0;
};

class ProductA1 : public AbstractProductA
{
public:
    virtual void showName()
    {
        cout<<"A1"<<endl;
    }
};

class ProductA2 : public AbstractProductA
{
public:
    virtual void showName()
    {
        cout<<"A2"<<endl;
    }
};

//B product
class AbstractProductB
{
public:
    virtual void showName() = 0;
};

class ProductB1 : public AbstractProductB
{
public:
    virtual void showName()
    {
        cout<<"B1"<<endl;
    }
};

class ProductB2 : public AbstractProductB
{
public:
    virtual void showName()
    {
        cout<<"B2"<<endl;
    }
};

//
class AbstractFactory
{
public:
    virtual AbstractProductA *createProductA() = 0;
    virtual AbstractProductB *createProductB() = 0;
};

class ConcreteFactoryOne : public AbstractFactory
{
     virtual AbstractProductA *createProductA()
     {
        return new ProductA1;
     }

     virtual AbstractProductB *createProductB()
     {
        return new ProductB1;
     }
};

class ConcreteFactoryTwo : public AbstractFactory
{
     virtual AbstractProductA *createProductA()
     {
        return new ProductA2;
     }

     virtual AbstractProductB *createProductB()
     {
        return new ProductB2;
     }
};

int main()
{
    AbstractFactory *factory = new ConcreteFactoryOne;
    AbstractProductA *product = factory->createProductA();
    product->showName();
    return 0;
    
}