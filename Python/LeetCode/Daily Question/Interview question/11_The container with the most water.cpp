#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int n = height.size();
        int i = 0, j = n - 1;
        int res = 0;
        while (i < j)
        {
            int temp = (j - i) * min(height[i], height[j]);
            res = max(res, temp);
            height[i] < height[j] ? i++ : j--;
        }
        return res;
    }
};