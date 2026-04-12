/*
 * 适配器模式 ： 手机 - 电源适配器
 */

#include <iostream>
#include <vector>
using namespace std;

class PowerAdaptee
{
public:
    void specificRequest()
    {
        cout << "power supply..." << endl;
    }
};

class ChargerAbstract
{
public:
    virtual void request() = 0;
};
class ChargerAdapter : public ChargerAbstract
{
public:
    void setAdapter(PowerAdaptee *adapter)
    {
        _adapter = adapter;
    }
    void request()
    {
        cout << "changed power supply..." << endl;
        _adapter->specificRequest();
    }

private:
    PowerAdaptee *_adapter;
};

class PhoneClient
{
public:
    void setAdapter(ChargerAbstract *charger)
    {
        _charger = charger;
    }
    void run()
    {
        _charger->request();
    }

private:
    ChargerAbstract *_charger;
};

int main()
{
    auto phone = new PhoneClient();
    auto charger = new ChargerAdapter();
    charger->setAdapter(new PowerAdaptee());
    phone->setAdapter(charger);
    phone->run();
}