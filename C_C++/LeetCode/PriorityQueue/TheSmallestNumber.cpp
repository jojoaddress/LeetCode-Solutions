#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class SmallestInfiniteSet
{
public:
    SmallestInfiniteSet()
    {
    }

    int popSmallest()
    {
        if (s.empty())
        {
            int num = thres;
            ++thres;
            return num;
        }
        int num = *s.begin();
        s.erase(s.begin());
        return num;
    }

    void addBack(int num)
    {
        if (num < thres)
        {
            s.insert(num);
        }
    }

private:
    set<int> s;
    int thres = 1;
};