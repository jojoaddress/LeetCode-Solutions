#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        long long  res = 0;
        unordered_map<double, long long> cnt;
        for (int i = 0; i < n;i++)
        {
            double scale = rectangles[i][0] * 1.0 / rectangles[i][1];
            auto it = cnt.find(scale);
            if(it!=cnt.end())
            {
                res += cnt[scale];
            }
            cnt[scale]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> rectangles = {{4,8},{3,6},{10,20},{15,30}};
    long long res = sol.interchangeableRectangles(rectangles);
    cout << res << endl; // Output: 6
    return 0;
}