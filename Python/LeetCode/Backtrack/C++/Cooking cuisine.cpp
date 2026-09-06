#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

class Solution {
public:
    int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, 
                    vector<vector<int>>& attribute, int limit) {
        int res = -1;  // 改为 -1
        vector<int> cur(5, 0);
        auto dfs = [&](auto &&self, int start, int taste, int full) -> void {
            if (taste >= limit) {
                bool ok = true;
                for (int i = 0; i < 5; ++i) {
                    if (cur[i] > materials[i]) { ok = false; break; }
                }
                if (ok) res = max(res, full);
            }
            for (int i = start; i < attribute.size(); ++i) {
                bool possible = true;
                for (int j = 0; j < 5; ++j) {
                    if (cur[j] + cookbooks[i][j] > materials[j]) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) continue;
                for (int j = 0; j < 5; ++j) cur[j] += cookbooks[i][j];
                self(self, i + 1, taste + attribute[i][1], full + attribute[i][0]);
                for (int j = 0; j < 5; ++j) cur[j] -= cookbooks[i][j];
            }
        };
        dfs(dfs, 0, 0, 0);
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> materials = { 3,2,4,1,2 };
    vector<vector<int>> cookbooks = { {1,1,0,1,2},{0,1,1,0,0},{2,0,0,1,1} };
    vector<vector<int>> attribute = { {3,2},{0,5},{3,2} };
    int limit = 5;
    int res = s.perfectMenu(materials,cookbooks,attribute,limit);
    cout << res << endl;
    return 0;
}