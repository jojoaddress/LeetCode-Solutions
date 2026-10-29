#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;
        for (const auto &interval:intervals)
        {
            if(res.empty()||res.back()[1]<interval[0])
                res.push_back(interval);
            else
                res.back()[1] = max(res.back()[1], interval[1]);
        }
        return res;
    }
};