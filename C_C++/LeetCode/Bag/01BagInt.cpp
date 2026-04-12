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

class Solution
{
    public:
    int knapsack01(vector<int> &weights, vector<int> &values, int capacity)
    {
        int n = weights.size();
        vector<int> dp(capacity + 1, 0);
        for (int i = 0; i < n;i++)
        {
            for (int j = capacity; j >= weights[i];j--)
            {
                dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
            }
        }
        return dp[capacity];
    }
};

int main()
{
    Solution solution;
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int capacity;
    cin >> capacity;
    int maxValue = solution.knapsack01(weights, values, capacity);
    cout << maxValue << endl;
    return 0;
}