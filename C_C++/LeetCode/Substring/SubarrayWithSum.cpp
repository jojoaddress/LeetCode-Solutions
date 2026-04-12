#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_set<int> window;
        int left = 0, right = 0;
        int res = 0;
        int tmpRes = 0;
        if (nums.size() == 1)
        {
            return nums[0] == k ? true : false;
        }
        while (right < nums.size())
        {
            tmpRes += nums[right];
            right++;

            while (tmpRes <= k)
            {
                if (tmpRes == k)
                {
                    res++;
                }
                tmpRes -= nums[left];
                left++;
            }
        }
        return res;
    }
};

class Solution_2
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_set<int> window;
        int left = 0, right = 0;
        int res = 0;
        int tmpRes = 0;
        if (nums.size() == 1)
        {
            return nums[0] == k ? true : false;
        }
        while (right < nums.size())
        {
            tmpRes += nums[right];
            right++;

            if (tmpRes == k)
            {
                res++;
            }
            if (right == nums.size())
            {
                tmpRes = 0;
                left++;
                right = left;
            }
        }
        return res;
    }
};

class Solution_plus
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        unordered_map<int, int> map;
        map[0] = 1;
        int count = 0;
        int presum = 0;
        for (int x : nums)
        {
            presum += x;
            auto it = map.find(presum - k);
            if (it != map.end())
            {
                count += map.at(presum - k);
            }
            map[presum]++;
        }
        return count;
    }
};

int main()
{
    Solution_plus *s1 = new Solution_plus();
    vector<int> str = {1, 1, 1};
    s1->subarraySum(str, 2);
    return 0;
}