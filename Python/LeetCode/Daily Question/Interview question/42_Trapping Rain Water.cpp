#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> left(n+1,0);
        for (int i = 1; i <= n;i++)
        {
            left[i] = max(left[i - 1], height[i - 1]);
        }

        vector<int> right(n+1,0);
        for (int i = n - 2; i >= 0;i--)
        {
            right[i] = max(right[i + 1], height[i + 1]);
        }

        int res = 0;
        for (int i = 0; i < n;i++)
        {
            int maxh = min(left[i], right[i]);
            if(height[i]<maxh)
                res += maxh-height[i];
        }
        return res;
    }
};