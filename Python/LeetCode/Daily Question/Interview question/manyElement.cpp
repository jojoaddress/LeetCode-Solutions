#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int ans = 0;
        int hp = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hp == 0)
            {
                ans = nums[i];
                hp = 1;
            }
            else
            {
                hp += nums[i] == ans ? 1 : -1;
            }
        }
        return ans;
    }
};