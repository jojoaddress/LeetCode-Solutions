#include <iostream>
#include <string.h>
using namespace std;

/* 可以看做两个建造者（厂商）生产产品（电脑），用相同的步骤，却能得出不同性能的电脑
    而监督者可以不关心形成产品的步骤，直接根据厂商决定产品*/

class Computer
{

public:
    void setCPU(string val)
    {
        _CPU = val;
    }

    void setGPU(string val)
    {
        _GPU = val;
    }

    void setMainBoard(string val)
    {
        _MainBoard = val;
    }

    void getComputer()
    {
        cout << _CPU << " " << _GPU << " " << _MainBoard << endl;
    }

private:
    string _CPU;
    string _GPU;
    string _MainBoard;
};

class AbstractBuilder
{
public:
    virtual void addCPU() = 0;
    virtual void addGPU() = 0;
    virtual void addMainBoard() = 0;

    Computer getComputer()
    {
        return _computer;
    }

protected:
    Computer _computer;
};

class LenovoBuilder : public AbstractBuilder
{

public:
    virtual void addCPU()
    {
        _computer.setCPU("L CPU");
    }

    virtual void addGPU()
    {
        _computer.setGPU("L GPU");
    }

    virtual void addMainBoard()
    {
        _computer.setMainBoard("L MainBoard");
    }
};

class HuaWeiBuilder : public AbstractBuilder
{

public:
    virtual void addCPU()
    {
        _computer.setCPU("H CPU");
    }

    virtual void addGPU()
    {
        _computer.setGPU("H GPU");
    }

    virtual void addMainBoard()
    {
        _computer.setMainBoard("H MainBoard");
    }
};

class Director
{
public:
    Director(AbstractBuilder *builder)
    {
        _builder = builder;
    }

    ~Director()
    {
        if (_builder != nullptr)
        {
            delete _builder;
        }
    }

    void setBuilder(AbstractBuilder *builder)
    {
        _builder = builder;
    }

    Computer construct()
    {
        _builder->addCPU();
        _builder->addGPU();
        _builder->addMainBoard();
        return _builder->getComputer();
    }

private:
    AbstractBuilder *_builder;
};

int main()
{
    AbstractBuilder *builder01 = new LenovoBuilder();
    Director *director = new Director(builder01);
    Computer computer01 = director->construct();
    computer01.getComputer();

    AbstractBuilder *builder02 = new HuaWeiBuilder();
    director->setBuilder(builder02);
    Computer computer02 = director->construct();
    computer02.getComputer();
}
