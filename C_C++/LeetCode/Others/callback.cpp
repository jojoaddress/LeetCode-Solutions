#include <iostream>
#include <functional>
using namespace std;

using callback = std::function<void(int &)>;
callback _cb;
void setNewMessageCallback(callback cb)
{
    _cb = cb;
}

void test(int a)
{
    int i = a;
}
int main()
{
    setNewMessageCallback([=](int &callback)
                          { cout << callback << endl; });
    int a = 3;
    _cb(a);
    _cb(a);
}