/*
 * 以下是一个简化的多平台应用程序示例，使用桥接模式处理不同的操作系统实现
 */

#include <iostream>
#include <vector>
using namespace std;

class OSAbstract
{
public:
    virtual void createElement() = 0;
    virtual void createUI() = 0;
};

class WindowsOS : public OSAbstract
{
public:
    void createElement()
    {
        cout << "windows element" << endl;
    }

    void createUI()
    {
        cout << "windows UI" << endl;
    }
};

class LinuxOS : public OSAbstract
{
public:
    void createElement()
    {
        cout << "linux element" << endl;
    }

    void createUI()
    {
        cout << "linux UI" << endl;
    }
};

class CrossPlatAppAbstract
{
public:
    virtual void createElement() = 0;
    virtual void createUI() = 0;
};

class CrossPlatApp : public CrossPlatAppAbstract
{
public:
    void setOS(OSAbstract *os)
    {
        _os = os;
    }
    void createElement()
    {
        _os->createElement();
    }
    void createUI()
    {
        _os->createUI();
    }

private:
    OSAbstract *_os;
};

int main()
{
    auto osApp = new CrossPlatApp();
    osApp->setOS(new WindowsOS());
    osApp->createElement();
    osApp->createUI();
}
