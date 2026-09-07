#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool uniformArray(vector<int> &nums1)
    {
        int minNum[2] = {INT_MAX, INT_MAX};
        for (auto num : nums1)
        {
            minNum[num & 1] = min(num, minNum[num & 1]);
        }
        return minNum[1] == INT_MAX || minNum[0] > minNum[1];
    }
};