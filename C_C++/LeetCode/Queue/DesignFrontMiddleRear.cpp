#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class FrontMiddleBackQueue
{
public:
    FrontMiddleBackQueue()
    {
    }

    void pushFront(int val)
    {
        l.push_front(val);
    }

    void pushMiddle(int val)
    {
        int i = l.size() / 2;
        auto it = l.begin();
        advance(it, i);
        l.insert(it, val);
    }

    void pushBack(int val)
    {
        l.push_back(val);
    }

    int popFront()
    {
        if (l.empty())
            return -1;
        int num = l.front();
        l.pop_front();
        return num;
    }

    int popMiddle()
    {
        if (l.empty())
            return -1;
        int i = l.size() / 2 - (l.size() % 2 == 0 ? 1 : 0);
        auto it = l.begin();
        advance(it, i);
        int num = *it;
        l.erase(it);
        return num;
    }

    int popBack()
    {
        if (l.empty())
            return -1;
        int num = l.back();
        l.pop_back();
        return num;
    }

private:
    list<int> l;
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */

int main()
{
    FrontMiddleBackQueue queue;
    queue.pushFront(1);
    queue.pushBack(2);
    queue.pushMiddle(3);
    queue.pushMiddle(4);
    cout << queue.popFront() << endl;  // 1
    cout << queue.popMiddle() << endl; // 3
    cout << queue.popMiddle() << endl; // 4
    cout << queue.popBack() << endl;   // 2

    cout << queue.popMiddle() << endl; // -1 (queue is empty)
    return 0;
}