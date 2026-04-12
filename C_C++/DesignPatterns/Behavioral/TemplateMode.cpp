//模板方法模式:在父类中定义一个方法的抽象，由它的子类来实现细节的处理，在子类实现详细的处理算法时并不会改变算法中的执行次序。
#include <iostream>
using namespace std;

//做饮料模板
class DrinkTemplate {
public:
    //煮水
    virtual void BoildWater() = 0;
    //冲泡
    virtual void Brew() = 0;
    //倒入杯中
    virtual void PourInCup() = 0;
    //加辅助材料
    virtual void AddSomething() = 0;

    //模板方法
    void Make() {
        BoildWater();
        Brew();
        PourInCup();
        AddSomething();
    }
};

//做咖啡：  实现做饮料模板
class Coffee :public DrinkTemplate {
    virtual void BoildWater() {
        cout << "煮山泉水" << endl;
    }
    virtual void Brew() {
        cout << "冲泡咖啡" << endl;
    }
    virtual void PourInCup() {
        cout << "咖啡倒入杯中" << endl;
    }
    virtual void AddSomething() {
        cout << "加糖，加牛奶" << endl;
    }
};

//做茶：  实现做饮料模板
class Tea :public DrinkTemplate {
    virtual void BoildWater() {
        cout << "煮自来水" << endl;
    }
    virtual void Brew() {
        cout << "冲泡铁观音" << endl;
    }
    virtual void PourInCup() {
        cout << "茶水倒入杯中" << endl;
    }
    virtual void AddSomething() {
        cout << "加糖,加大蒜" << endl;
    }
};

void test01() {
    Tea* tea = new Tea;
    tea->Make();

    Coffee* coffee = new Coffee;
    coffee->Make();
}

int main()
{
    test01();
}

