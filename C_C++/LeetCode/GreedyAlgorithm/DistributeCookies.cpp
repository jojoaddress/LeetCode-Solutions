#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0;
        for (auto x : s)
        {
            if(i<g.size()&&g[i]<=x)
                i++;
        }
        return i;
    }
};

int main()
{
    Solution sol;
    vector<int> g = {1, 2, 3};
    vector<int> s = {1, 1};
    cout << sol.findContentChildren(g, s) << endl;
    return 0;
}