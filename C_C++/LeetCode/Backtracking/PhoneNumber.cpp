// 电话号码的字母组合
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
class Solution
{
public:
    void outPut(vector<string> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                cout << res[i][j] << " " << endl;
            }
            cout << "-----" << endl;
        }
    }

    void dfs(string &digits, string &tmp, vector<string> &ans, vector<string> &nums, int depth)
    {
        if (depth == digits.size())
        {
            ans.push_back(tmp);
            return;
        }
        int j = digits[depth] - '0';
        int size = nums[j].size();

        for (int i = 0; i < size; i++)
        {
            char c = nums[j][i];
            tmp.push_back(c);
            dfs(digits, tmp, ans, nums, depth + 1);
            tmp.pop_back();
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string> nums(10, "");
        nums[2] = "abc";
        nums[3] = "def";
        nums[4] = "ghi";
        nums[5] = "jkl";
        nums[6] = "mno";
        nums[7] = "pqrs";
        nums[8] = "tuv";
        nums[9] = "wxyz";
        int n = digits.size();
        vector<string> ans;
        string tmp;
        vector<bool> dp(n);
        if (n == 0)
            return ans;
        dfs(digits, tmp, ans, nums, 0);
        return ans;
    }
};

int main()
{
    string str = "23";
    auto s = new Solution();
    auto ans = s->letterCombinations(str);
    s->outPut(ans);
    return 0;
}