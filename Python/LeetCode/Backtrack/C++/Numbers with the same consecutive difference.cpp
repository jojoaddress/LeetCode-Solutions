#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> res;
        vector<int> path;
        auto dfs = [&](this auto &&dfs, int start) -> void {
            if(start==n&& path.size()==n)
            {
                int temp = 0;
                for (auto it: path)
                {
                    temp = it + temp * 10;
                }
                res.push_back(temp);
                return;
            }
            for (int i = 0; i < 10;i++)
            {
                if(path.empty() && i==0)
                    continue;
                if(!path.empty()&&abs(path.back()-i)!=k)
                    continue;
                path.push_back(i);
                dfs(start + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> res = s.numsSameConsecDiff(2, 1);
    for (auto i : res)
        cout << i << " ";
    return 0;
}