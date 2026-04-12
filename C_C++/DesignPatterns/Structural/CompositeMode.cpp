
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

// 组合中的抽象基类
class Component
{
public:
    Component() {}
    virtual ~Component() {}
    virtual void Operation() = 0;
    virtual void Add(Component *pChild){};
    virtual void Remove(Component *pChild){};
};

class Leaf : public Component
{
public:
    Leaf(string str) { _str = str; }
    virtual ~Leaf() {}
    virtual void Operation()
    {
        cout << "Operation by leaf : " << _str << endl;
    }

private:
    string _str;
};

class Composite : public Component
{
public:
    Composite() {}
    virtual ~Composite()
    {
        std::list<Component *>::iterator iter1, iter2, temp;
        for (iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end();
             iter1 != iter2;)
        {
            temp = iter1;
            ++iter1;
            delete (*temp);
        }
    }

    virtual void Operation()
    {
        cout << "Operation by Composite\n";
        auto iter = m_ListOfComponent.begin();
        while (iter != m_ListOfComponent.end())
        {
            (*iter)->Operation();
            iter++;
        }

    }

    virtual void Add(Component *pChild)
    {
        m_ListOfComponent.push_back(pChild);
    }

    virtual void Remove(Component *pChild)
    {
        list<Component *>::iterator iter;
        iter = find(m_ListOfComponent.begin(), m_ListOfComponent.end(), pChild);
        if (m_ListOfComponent.end() != iter)
        {
            m_ListOfComponent.erase(iter);
        }
    }

private:
    list<Component *> m_ListOfComponent;
};

int main()
{
    Leaf *pLeaf1 = new Leaf("1");
    Leaf *pLeaf2 = new Leaf("2");
    Composite *composite1 = new Composite;
    composite1->Add(pLeaf1);
    composite1->Add(pLeaf2);

    Leaf *pLeaf3 = new Leaf("3");
    Composite *composite2 = new Composite;
    composite2->Add(pLeaf3);
    composite2->Operation();
    return 0;
}