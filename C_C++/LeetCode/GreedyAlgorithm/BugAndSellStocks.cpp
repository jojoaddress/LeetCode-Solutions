/*
* 2023.12.07
*
* 买股票的最佳时机
* 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
* 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
* 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
* 
* 这题plus解法利用了贪心算法，简而言之就是数组开始递减的时候会找最小值，只有开始递增的时候计算差值。换句话说，买股票时每天都在想着今天是不是历史低点。
* 【9,3,12,1,2,3】最大值是9而不是2的原因：是因为“他”在买时还会计算最大利润，尽管在1时是最低点，但利润却没有获得最大。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;
        for(int i=0;i<prices.size()-1;i++)
        {
            int tmpMax = 0;
            for(int j=i+1;j<prices.size();j++)
            {
                if(prices[j]>prices[i])
                {
                    if(prices[j]>tmpMax)
                    {
                        tmpMax = prices[j];
                    }
                }
            }
            if((tmpMax-prices[i])>max)
            {
                max = tmpMax-prices[i];
            }
            
        }
        return max;
    }
};

class Solution_plus {
public:
    int maxProfit(vector<int>& prices) {
        int profitMax = 0;
        int historyMin = 9999999;
        for(int i=0;i<prices.size();i++)
        {
            if(prices[i]<historyMin)
            {
                historyMin = prices[i];
            }
            else if((prices[i]-historyMin)>profitMax)
            {
                profitMax = prices[i]-historyMin;
            }
        }
        return profitMax;
    }
};

int main()
{
    Solution_plus *s = new Solution_plus();
    vector<int> nums = {7,1,5,3,6,4};
    cout<<s->maxProfit(nums);
    return 0;
}