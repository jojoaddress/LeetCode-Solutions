/*
* 2023.12.06
* 三数之和
* 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
* 请你返回所有和为 0 且不重复的三元组。
* 注意：答案中不可以包含重复的三元组。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int begin = 0;
        int end = 0;
        vector<vector<int>> res;

        sort(nums.begin(),nums.end());
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i]>0) return res;
            if(i>0 && nums[i] == nums[i-1]) continue;

            begin=i+1;
            end = nums.size() - 1;
            
            while(begin<end)
            {
                if(nums[i]+nums[begin]+nums[end]==0)
                {
                    vector<int> tmpRes;
                    tmpRes.push_back(nums[i]);
                    tmpRes.push_back(nums[begin]);
                    tmpRes.push_back(nums[end]);
                    res.push_back(tmpRes);
                    while(begin<end && nums[begin] == nums[begin+1]) begin++;
                    while(begin<end && nums[end] == nums[end-1]) end--;
                    begin++;
                    end--;
                }
                else if(nums[i]+nums[begin]+nums[end]>0)
                {
                    end--;
                }
                else
                {
                    begin++;
                }
            }

        }
        return res;

    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {1,2,-2,-1};
    s->threeSum(nums);
    return 0;
}
