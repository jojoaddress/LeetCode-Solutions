/**
 * 享元设计
 *
 * 目的: 通过共享多个对象之间的公共状态而不保存每个对象中的所有数据，以将更多的对象放入可用的RAM中
 * 参考链接：https://blog.csdn.net/luonong9586/article/details/127857477
 */
#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
using namespace std;

struct SharedState
{
    string _brand;
    string _size;
    SharedState(const string &brand, const string &size) : _brand(brand), _size(size) {}
    friend ostream &operator<<(ostream &os, const SharedState &sharedState)
    {
        return os << "brand:" << sharedState._brand << " "
                  << "size:" << sharedState._size << endl;
    }
};

struct UniqueState
{
    string _owner;
    UniqueState(const string &owner) : _owner(owner) {}
    friend ostream &operator<<(ostream &os, const UniqueState &UniqueState)
    {
        return os << "owner:" << UniqueState._owner << endl;
    }
};

/**
 * Flyweight存储属于多个实际业务实体的公共状态部分(也称为内在状态)。
 * 通过成员函数的参数接受状态的其余部分(外部状态，每个实体都是惟一的)。
 */
class Flyweight
{
public:
    Flyweight(const SharedState *sharedState) : _sharedState(new SharedState(*sharedState))
    {
    }
    SharedState *GetSharedState() const
    {
        return _sharedState;
    }
    void Operation(const UniqueState &uniqueState) const
    {
        cout << "Flyweight: SharedState is " << *_sharedState << ",unique is " << uniqueState << endl;
    }

private:
    SharedState *_sharedState;
};

class FlyweightFactory
{
public:
    FlyweightFactory(initializer_list<SharedState> sharedStates)
    {
        for (const SharedState &sharedState : sharedStates)
        {
            _flyweight.insert(make_pair<string, Flyweight>(getKey(sharedState), Flyweight(&sharedState)));
        }
    }

    /**
     * 返回具有给定状态的Flyweight或创建一个新Flyweight。
     */
    Flyweight GetFlyweight(const SharedState &sharedState)
    {
        string key = getKey(sharedState);
        if (_flyweight.find(key) == _flyweight.end())
        {
            cout << "create a flyweight..." << endl;
            _flyweight.insert(make_pair(key, Flyweight(&sharedState)));
        }
        else
        {
            cout << "flyweight existing.." << endl;
        }
        return _flyweight.at(key);
    }

    void ListFlyweight() const
    {
        size_t count = _flyweight.size();
        cout << "Factory has " << count << " flyweights" << endl;
        for (pair<string, Flyweight> pair : _flyweight)
        {
            cout << pair.first << endl;
        }
    }

    void AddFlyweight(string &owner, string &brand, string &size)
    {
        auto flyweight = this->GetFlyweight({brand, size});
        flyweight.Operation({owner});
    }

private:
    string getKey(const SharedState &sharedState) const
    {
        return sharedState._brand + " " + sharedState._size;
    }

private:
    unordered_map<string, Flyweight> _flyweight;
};

int main()
{
    auto factory = new FlyweightFactory({{"Lenovo", "12 inch"}, {"HP", "10 inch"}});
    factory->ListFlyweight();
    string str[3];
    str[0] = "wang";
    str[1] = "Lenovo";
    str[2] = "12 inch";
    factory->AddFlyweight(str[0], str[1], str[2]);
    str[0] = "Liu";
    str[1] = "Lenovo";
    str[2] = "12 inch";
    factory->AddFlyweight(str[0], str[1], str[2]);
    str[0] = "Liu";
    str[1] = "DELL";
    str[2] = "14 inch";
    factory->AddFlyweight(str[0], str[1], str[2]);
    factory->ListFlyweight();
}