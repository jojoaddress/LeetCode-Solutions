/* 2024.1.8
 *
 * 寻找重复数
 * 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
 * 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
 * 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
 * 
 * 此题第一种解法不满足O(1) 的额外空间，但是却很容易想到并解决要求。解法而用了类似二分法的思想。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        unordered_set<int> hash;
        for(int i = 0; i< nums.size();i++)
        {
            if(hash.find(nums[i])!=hash.end())
            {
                return nums[i];
            }
            hash.insert(nums[i]);
        }
        return nums[0];
    }
};

class Solution_plus
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int left = 0;
        int right = nums.size() - 1;
        int ans = -1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            int cnt = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                cnt += nums[i] <= mid;
            }
            if (mid >= cnt)
            {
                left = mid+1;
            }
            else
            {
                right = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};

int main()
{
    Solution *s1 = new Solution();
    vector<int> str = {1, 1};
    s1->findDuplicate(str);
    return 0;
}