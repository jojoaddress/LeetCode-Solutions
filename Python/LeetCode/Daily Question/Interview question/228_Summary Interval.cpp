#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> res;
        int i = 0;
        int n = nums.size();
        while (i < n)
        {
            int low = i;
            while (i < n - 1 && nums[i + 1] == nums[i] + 1)
                i++;
            int high = i;
            string temp;
            temp.append(to_string(nums[low]));
            if (nums[low] < nums[high])
            {
                temp.append("->");
                temp.append(to_string(nums[high]));
            }
            res.push_back(move(temp));
            i++;
        }
        return res;
    }
};