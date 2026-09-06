#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int mCost = -prices[0];
        for (int i = 1; i < prices.size();i++)
        {
            mCost = max(mCost, res-prices[i]);
            res = max(res, mCost + prices[i]);
        }
        return res;
    }
};