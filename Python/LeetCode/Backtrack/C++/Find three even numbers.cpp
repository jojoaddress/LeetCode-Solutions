#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> res;
        vector<int> path;
        vector<bool> visited(digits.size(), false);
        auto dfs = [&](this auto &&dfs, int start) -> void {
            if(path.size()==3)
            {
                int temp = 0;
                for(int num:path)
                {
                    temp = temp * 10 + num;
                }
                if(temp%2==0&&temp)
                    res.push_back(temp);
                return;
            }
            unordered_set<int> uset;
            for (int i = 0; i < digits.size();i++)
            {
                if(uset.count(digits[i]))
                    continue;
                if(visited[i])
                    continue;
                if(path.empty()&&digits[i]==0)
                    continue;
                uset.insert(digits[i]);
                visited[i] = true;
                path.push_back(digits[i]);
                dfs(start + 1);
                path.pop_back();
                visited[i] = false;
            }
        };
        dfs(0);
        sort(res.begin(), res.end());
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> digits = {2, 1, 3, 0};
    vector<int> res = s.findEvenNumbers(digits);
    for (int num : res)
    {
        cout << num << " ";
    }
    return 0;
}
