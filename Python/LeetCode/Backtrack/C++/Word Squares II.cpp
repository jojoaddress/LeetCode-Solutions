#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm> 
using namespace std;

class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        std::sort(words.begin(), words.end());
        int path[4];
        vector<bool> on_path(words.size());
        vector<vector<string>> res;

        auto dfs = [&](this auto &&dfs, int start) -> void {
            if(start==4)
            {
                auto top = words[path[0]];
                auto left = words[path[1]];
                auto right = words[path[2]];
                auto bottom = words[path[3]];
                if(top[0] == left[0]&&top[3] == right[0]&&bottom[0] == left[3]&&bottom[3] == right[3])
                    res.push_back({top, left, right, bottom});
                return;
            }

            for (int i = 0; i < words.size();i++)
            {
                if(!on_path[i])
                {
                    on_path[i] = true;
                    path[start] = i;
                    dfs(start + 1);
                    on_path[i] = false;
                }
            }
        };
        dfs(0);
        return res;
    }
};