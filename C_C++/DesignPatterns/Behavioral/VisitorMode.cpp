/*
 * 在最初的访问者模式类图没有管理类的角色，
 * 这里为了方便客户端使用接口，才增加此类。实际场景中，只要运用到访问者模式思想即可，没有必要参照其实现方式生搬硬套。
 */

#include <iostream>
#include <vector>
using namespace std;
class PartSoundCard;
class PartGpu;

class VisitorBase
{
public:
    virtual void VisitSoundCard(PartSoundCard *psc) = 0;
    virtual void VisitGpu(PartGpu *pg) = 0;
};

class ComputePartBase
{
public:
    virtual void Accept(VisitorBase *vb) = 0;
};

class PartSoundCard : public ComputePartBase
{
public:
    void Accept(VisitorBase *vb)
    {
        if (vb)
        {
            vb->VisitSoundCard(this);
        }
        else
        {
            cout << "visitor is NUll" << endl;
        }
    }
    string CheckFuncton()
    {
        return "check soundCard CheckFuncton";
    }
    string CheckDriver()
    {
        return "check soundCard Dirver";
    }
};

class PartGpu : public ComputePartBase
{
public:
    void Accept(VisitorBase *vb)
    {
        if (vb)
        {
            vb->VisitGpu(this);
        }
        else
        {
            cout << "visitor is NUll" << endl;
        }
    }
    string CheckFuncton()
    {
        return "check gpu CheckFuncton";
    }
    string CheckDriver()
    {
        return "check gpu Dirver";
    }
};



class VisitorDriver : public VisitorBase
{
public:
    void VisitSoundCard(PartSoundCard *psc)
    {
        cout << psc->CheckDriver() << endl;
    }
    void VisitGpu(PartGpu *pg)
    {
        cout << pg->CheckDriver() << endl;
    }
};

class VisitorFunction : public VisitorBase
{
public:
    void VisitSoundCard(PartSoundCard *psc)
    {
        cout << psc->CheckFuncton() << endl;
    }
    void VisitGpu(PartGpu *pg)
    {
        cout << pg->CheckFuncton() << endl;
    }
};

class SafeMgr
{
public:
    typedef enum
    {
        ITEM_DRIVER,
        ITEM_FUNCTION,
        ITEM_ALL,
    } CheckItem;

    void AddPartArry(ComputePartBase *part)
    {
        parts.push_back(part);
    }

    void Accept(VisitorBase *vb)
    {
        auto it = parts.begin();
        while (it != parts.end())
        {
            (*it)->Accept(vb);
            it++;
        }
    }

    void CheckComputeItem(CheckItem item)
    {
        switch (item)
        {
        case ITEM_DRIVER:
            Accept(&_vDriver);
            break;

        case ITEM_FUNCTION:
            Accept(&_vFunction);
            break;

        case ITEM_ALL:
            Accept(&_vDriver);
            Accept(&_vFunction);
            break;

        default:
            cout << "NULL" << endl;
            break;
        }
    }

private:
    vector<ComputePartBase *> parts;
    VisitorDriver _vDriver;
    VisitorFunction _vFunction;
};

int main()
{
    SafeMgr mgr;
    mgr.AddPartArry(new PartGpu());
    // mgr.AddPartArry(new PartSoundCard());
    mgr.CheckComputeItem(SafeMgr::CheckItem::ITEM_ALL);

    cout<< "--------------------------"<<endl;

    auto gpu = new PartGpu();
    gpu->Accept(new VisitorDriver());
    gpu->Accept(new VisitorFunction());

    return 0;
}