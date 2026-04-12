#include <algorithm>
#include <iostream>
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
    //前缀和也可以用两个数组来结合使用。
    long long maxProfit(vector<int> &prices, vector<int> &strategy, int k)
    {
        int n = prices.size();
        vector<long long> s(n + 1);
        vector<long long> c(n+1);
        for (int i = 1; i <= n; i++)
        {
            c[i] = c[i - 1] + prices[i - 1] * strategy[i - 1];
            s[i] = s[i - 1] + prices[i - 1];
        }
        int k_2 = k / 2;
        long long maxProfit = c[n];
        for (int i = k; i <= n; i++)
        {
            maxProfit = max(maxProfit, c[i - k] + c[n] - c[i] + s[i] - s[i - k_2]);
        }
        return maxProfit;
    }
};

int main()
{
    Solution sol;
    vector<int> prices = {4,2,8};
    vector<int> strategy = {-1,0,1};
    int k = 2;
    cout << sol.maxProfit(prices, strategy, k) << endl; // Output: 6
    return 0;
}