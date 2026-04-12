#include <algorithm>
#include <bitset>
#include <cmath>
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
    long long pickGifts_(vector<int> &gifts, int k)
    {
        priority_queue<int> pq;
        for (auto &g : gifts)
        {
            pq.push(g);
        }
        for (int i = 0; i < k; i++)
        {
            long long num = pq.top();
            pq.pop();
            num = sqrt(num);
            pq.push(num);
        }
        long long res = 0;
        while (!pq.empty())
        {
            res += pq.top();
            pq.pop();
        }
        return res;
    }
    long long pickGifts(vector<int> &gifts, int k)
    {
        make_heap(gifts.begin(), gifts.end());
        while (k-- && gifts[0] > 1)
        {
            pop_heap(gifts.begin(), gifts.end());
            gifts.back() = sqrt(gifts.back());
            push_heap(gifts.begin(), gifts.end());
        }
        return accumulate(gifts.begin(), gifts.end(), 0LL);
    }
};

int main()
{
    Solution sol;
    vector<int> gifts = {25, 64, 9, 4, 100};
    int k = 4;
    long long result = sol.pickGifts(gifts, k);
    cout << result << endl; // Output the result
    return 0;
}