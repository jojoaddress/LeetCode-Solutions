#include <bits/stdc++.h>
using std::cout;
using std::endl;
using std::string;

class AbstarctProtoType
{
public:
    virtual AbstarctProtoType *clone() = 0;
    virtual ~AbstarctProtoType() = default;
    virtual void show() = 0;
};

class ConcreteProtoType : public AbstarctProtoType
{

public:
    ConcreteProtoType(string title, string context) : AbstarctProtoType(), title(title), context(context)
    {
        std::cout << "AbstractProtoType:" << this << endl;
        cout << "title:" << &title << endl;
        cout << "context:" << &context << endl;
    };
    ConcreteProtoType(const ConcreteProtoType &obj)
    {
        this->title = obj.title;
        this->context = obj.context;

        std::cout << "AbstractProtoType:" << this << endl;
        cout << "title:" << &title << endl;
        cout << "context:" << &context << endl;
    }

    ~ConcreteProtoType()
    {
    }

    AbstarctProtoType *clone() override
    {
        return new ConcreteProtoType(*this);
    }

    void show() override
    {
        cout << "title:" << title << endl;
        cout << "context:" << context << endl;
    }

public:
    string title;
    string context;
};

int main()
{
    AbstarctProtoType *A1 = new ConcreteProtoType("1", "a");
    A1->show();

    cout << "__________" << endl;

    //采用原型模型写法
    AbstarctProtoType *A2 = A1->clone();
     A2->show();

     cout << "__________" << endl;

    //不使用原型模式的写法
    AbstarctProtoType *A3(new ConcreteProtoType(*dynamic_cast<ConcreteProtoType *>(A1)));
    A3->show();
     
}