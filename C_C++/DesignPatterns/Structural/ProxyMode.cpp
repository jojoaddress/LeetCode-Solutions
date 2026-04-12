/*
 * 现在有一个操作系统，只需要调用run（）就可以启动操作系统，
 * 但是进入操作系统之前必须要进行账户名和密码的认证。认证成功后这个代理才会让你进入操作系统，其中认证的这个过程就是一个代理。
 */

#include <iostream>
#include <string>
using namespace std;

class AbstractCommonInterface
{
public:
    virtual void run() = 0;
};

class WindowsSystem : public AbstractCommonInterface
{
public:
    void run()
    {
        cout << "windowsSystem is running..." << endl;
    }
};

class WindowsSystemProxy : public AbstractCommonInterface
{
public:
    WindowsSystemProxy(string userName, string password)
    {
        _userName = userName;
        _password = password;
        _windowsSystem = new WindowsSystem();
    }

    bool CheckSafty()
    {
        if(_userName == "admin" && _password == "123")
        {
            return true;
        }
        return false;
    }
    void run()
    {
        if(CheckSafty())
        {
            cout<<"Security verification passed"<<endl;
            _windowsSystem->run();
        }
        else
        {
            cout<<"Validation failed"<<endl;
        }
    }

private:
    string _userName;
    string _password;
    WindowsSystem *_windowsSystem;
};

int main()
{
    WindowsSystemProxy *poxy = new WindowsSystemProxy("admin","123");
    poxy->run();
}