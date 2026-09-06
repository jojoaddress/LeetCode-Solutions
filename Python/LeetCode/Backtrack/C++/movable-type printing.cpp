#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    int numTilePossibilities(string tiles)
    {
        sort(tiles.begin(), tiles.end());
        string path = "";
        vector<bool> dp(tiles.size(), false);
        int res = 0;
        auto dfs = [&](this auto &&dfs, int start) -> void
        {
            if (!path.empty())
                res++;
            if (path.size() == tiles.size())
                return;
            unordered_set<char> uset;
            for (int i = 0; i < tiles.size(); i++)
            {
                if (dp[i])
                    continue;
                if (uset.count(tiles[i]))
                    continue;
                uset.insert(tiles[i]);
                dp[i] = true;
                path.push_back(tiles[i]);
                dfs(i + 1);
                path.pop_back();
                dp[i] = false;
            }
        };
        dfs(0);
        return res;
    }
};