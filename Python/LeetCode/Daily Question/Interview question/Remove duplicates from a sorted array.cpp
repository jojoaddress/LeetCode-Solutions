#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int i = 0;
        unordered_set<int> cnt;
        for (auto num : nums)
        {
            if (cnt.count(num))
                continue;
            cnt.insert(num);
            nums[i++] = num;
        }
        return cnt.size();
    }
};