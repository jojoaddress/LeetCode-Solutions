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

// 一维数组a的区间+1操作，等价于更新差分数组d中2个位置的差分值。
// 其中d[i]表示把a中下标≥i的数都加上d[i]。
class Solution
{
public:
    bool carPooling(vector<vector<int>> &trips, int capacity)
    {
        int n = trips.size();
        map<int, int> d;
        for (int i = 0; i < n; i++)
        {
            int num = trips[i][0];
            int from = trips[i][1];
            int to = trips[i][2];
            d[from] += num;
            d[to] -= num;
        }
        int s = 0;
        for (auto [_, x] : d)
        {
            s += x;
            if(s>capacity)
                return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> trips = {{2, 1, 5}, {3, 3, 7}};
    int capacity = 5;
    bool ans = sol.carPooling(trips, capacity);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}