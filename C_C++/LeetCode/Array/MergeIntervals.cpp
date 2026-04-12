/* 2024.01.02
 *
 * 合并区间
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
 * 请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 * 
 * 以下是标准题解
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;

        for (int i = 0; i < intervals.size(); i++)
        {
            int right = intervals[i].at(1);
            int left = intervals[i].at(0);
            if (!res.size() || res.back()[1] < left )
            { 
                res.push_back({left,right});
            }
            else
            {
                res.back()[1] = max(res.back()[1],right);
            }
             
        }
        return res;
    }
};

int main()
{
    Solution *s1 = new Solution();
    vector<vector<int>> str = {{1,4},{5,6}};
    s1->merge(str);
    return 0;
}