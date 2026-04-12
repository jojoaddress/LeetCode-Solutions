/*
* 2023.11.03
* 最长连续序列
* 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
* 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
* 
* 很简单的哈希表应用
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size()<1)
        {
            return 0;
        }

         unordered_map<int,int> hashmap;
         sort(nums.begin(),nums.end());
         for(int i=1;i<nums.size();i++)
         {
            auto it = hashmap.find(nums[i]);
            if(it == hashmap.end() && nums[i]==(nums[i-1]+1))
            {
                hashmap[nums[i]]=hashmap[nums[i-1]]+1;
            }
         }

         auto it = hashmap.begin();
         int resMax = 0;
         for(;it!=hashmap.end();it++)
         {
            if(it->second>resMax)
            {
                resMax = it->second;
            }
         }
         return resMax+1;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {0,0,1,1,2,3};
    cout<<s->longestConsecutive(nums)<<endl;
    return 0;
}