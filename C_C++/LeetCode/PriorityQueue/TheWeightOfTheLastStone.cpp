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

class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> pq;
        for (auto &st : stones)
            pq.push(st);

        while (pq.size() > 1)
        {
            int first = pq.top(); // 最重的石头
            pq.pop();
            int second = pq.top(); // 第二重的石头
            pq.pop();

            if (first != second)
            {
                pq.push(first - second); // 碰撞后剩下的石头重量
            }
        }

        return pq.empty() ? 0 : pq.top();
    }
};

int main()
{
    Solution sol;
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << sol.lastStoneWeight(stones) << endl;
    return 0;
}