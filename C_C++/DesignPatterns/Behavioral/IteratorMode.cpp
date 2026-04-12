/*
 * 实现代码来源：https://blog.csdn.net/lovely_yoshino/article/details/123429647
 */
using namespace std;

// 迭代基类
template<class Item>

class Iterator
{
public:
    Iterator() {};
    virtual ~Iterator() {};

    virtual void first() = 0;
    virtual void next() = 0;
    virtual Item *curItem() = 0;
    virtual bool isDone() = 0;
};

// 迭代具体类
template<class Item>

class ConcreteIterator : public Iterator <Item>
{
public:
    ConcreteIterator(Aggregate<Item> *a) :aggr(a), cur(0) {};
    virtual ~ConcreteIterator() {};

    virtual void first();
    virtual void next();
    virtual Item *curItem();
    virtual bool isDone();
private:
    Aggregate<Item> *aggr;
    int cur;
};

template<class Item>
void ConcreteIterator<Item>::first()
{
    cur = 0;
}

template<class Item>
void ConcreteIterator<Item>::next()
{
    if (cur < aggr->getSize())
        cur++;
}

template<class Item>
Item *ConcreteIterator<Item>::curItem()
{
    if (cur < aggr->getSize())
    {
        return &(*aggr)[cur];
    }
    else
    {
        return NULL;
    }
}

template<class Item>
bool ConcreteIterator<Item>::isDone()
{
    return cur >= aggr->getSize();
}

// 容器基类
template<class Item>
class Aggregate{
public:
    Aggregate() {};
    virtual ~Aggregate() {};

    virtual void pushData(Item item) = 0;
    virtual Iterator<Item>* createIterator() = 0;
    virtual Item& operator[](int index) = 0;
    virtual int getSize() = 0;
};              
// 容器具体类

template <class Item>
class ConcreteAggregate : public Aggregate<Item>
{
public:
    ConcreteAggregate() {};
    virtual ~ConcreteAggregate() {};

    virtual void pushData(Item item);
    virtual Iterator<Item>* createIterator();
    virtual Item& operator[](int index);
    virtual int getSize();
private:
    vector<Item> data;
};

template <class Item>
void ConcreteAggregate<Item>::pushData(Item item)
{
    data.push_back(item);
}

template <class Item>
Iterator<Item>* ConcreteAggregate<Item>::createIterator()
{
    return new ConcreteIterator<Item>(this);
}

template <class Item>
Item& ConcreteAggregate<Item>::operator[](int index)
{
    return data[index];
}

template <class Item>
int ConcreteAggregate<Item>::getSize()
{
    return data.size();
}

/** main 函数
int main(int argc, char *argv[])
{

    Aggregate<int> * aggr = new ConcreteAggregate<int>();
    aggr->pushData(3);
    aggr->pushData(2);
    aggr->pushData(1);
    Iterator<int> * it = aggr->createIterator();

    for (it->first(); !it->isDone(); it->next())
    {
        std::cout << *it->curItem() << std::endl;
    }
    delete it;
    delete aggr;
}
**/
                                                                                                                                       
