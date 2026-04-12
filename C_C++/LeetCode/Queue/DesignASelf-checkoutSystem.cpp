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

class Checkout
{
public:
    Checkout()
    {
    }

    int get_max()
    {
        if (dq.empty())
            return -1;
        return *max_element(dq.begin(), dq.end());
    }

    void add(int value)
    {
        dq.push_back(value);
    }

    int remove()
    {
        if (dq.empty())
            return -1;
        int num = dq.front();
        dq.pop_front();
        return num;
    }

private:
    deque<int> dq;
};

int main()
{
    Checkout checkout;
    checkout.add(5);
    checkout.add(10);
    cout << "Max: " << checkout.get_max() << endl; // Output: Max: 10
    cout << "Removed: " << checkout.remove() << endl; // Output: Removed: 5
    cout << "Max after removal: " << checkout.get_max() << endl; // Output: Max after removal: 10
    return 0;
}