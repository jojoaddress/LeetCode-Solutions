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
    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), [](auto &a, auto &b)
             { return a[1] < b[1]; });
        int res = 0;
        long long pre =  LLONG_MIN;
        for (auto &p : points)
        {
            if (p[0] > pre)
            {
                res++;
                pre = p[1];
            }
        }
        return res;
    }
};