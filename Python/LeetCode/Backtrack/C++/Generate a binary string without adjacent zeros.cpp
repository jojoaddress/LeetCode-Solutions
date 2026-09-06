#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> validStrings(int n)
    {
        string path = "";
        vector<string> res;
        auto dfs = [&](this auto &&dfs, int start) -> void
        {
            if (start == n)
            {
                res.push_back(path);
                return;
            }
            if (path.empty() || path.back() == '1')
            {
                path.push_back('0');
                dfs(start + 1);
                path.pop_back();
            }

            path.push_back('1');
            dfs(start + 1);
            path.pop_back();
        };
        dfs(0);
        return res;
    }
};