#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class RecentCounter
{
public:
    RecentCounter()
    {
    }

    int ping(int t)
    {
        list.push(t);
        while(list.front()<t-3000)
            list.pop();
        return list.size();
    }

private:
    queue<int> list;
};

int main()
{
    RecentCounter recentCounter;
    cout << recentCounter.ping(1) << endl;     // requests = [1], range is [-2999,1], return 1
    cout << recentCounter.ping(100) << endl;   // requests = [1, 100], range is [-2900,100], return 2
    cout << recentCounter.ping(3001) << endl;  // requests = [1, 100, 3001], range is [1,3001], return 3
    cout << recentCounter.ping(3002) << endl;  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3
    return 0;
}