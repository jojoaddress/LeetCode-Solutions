#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isPartition(string s)
    {
        int i = 0;
        int j = s.size()-1;
        while (i <= j)
        {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> path;
        auto dfs = [&](auto &&self, int start) -> void
        {
            if (start == s.size())
            {
                res.push_back(path);
                return;
            }
            for (int i = start; i < s.size(); i++)
            {
                auto temp = s.substr(start, i - start + 1);
                if (isPartition(temp))
                {
                    path.push_back(temp);
                    self(self, i + 1);
                    path.pop_back();
                }
            }
        };
        dfs(dfs, 0);
        return res;
    }
};