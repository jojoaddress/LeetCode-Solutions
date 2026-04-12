/*
* 较为简单的解耦行为模式
* 值得注意的是，此类设计比继承要好得多。因为在面向对象的设计中的有一条很重要的原则就是：优先使用对象组合，而非类继承。
*/


#include <iostream>
#include <list>
using namespace std;

class AbstractWeapon
{
public:
    virtual void Danger() = 0;
};

class Knife : public AbstractWeapon
{
public:
    void Danger()
    {
        cout << "Kinfe: 5 Danger" << endl;
    }
};

class Gun : public AbstractWeapon
{
public:
    void Danger()
    {
        cout << "Gun: 10 Danger" << endl;
    }
};

class User
{
public:
    void setWeapon(AbstractWeapon *weapon)
    {
        _weapon = weapon;
    }

    void getWeaponDanger()
    {
        _weapon->Danger();
    }

private:
    AbstractWeapon *_weapon;
};

int main()
{
    AbstractWeapon *knife = new Knife();
    AbstractWeapon *gun = new Gun();
    User *user = new User();

    user->setWeapon(knife);
    user->getWeaponDanger();
    return 0;
}