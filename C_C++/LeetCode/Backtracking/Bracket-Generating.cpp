/**
 * @file Bracket-Generating.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 * 括号生成
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(vector<string> &res, string str, int left, int right, int n)
    {
        if (left == 0 && right == 0)
        {
            res.push_back(str);
        }
        if (left > right)
            return;
        if (left > 0)
        {
            dfs(res, str + '(', left - 1, right, n);
        }
        if (right > 0)
        {
            dfs(res, str + ')', left, right - 1, n);
        }
    }
    vector<string> generateParenthesis(int n)
    {
        if (n == 0)
            return {""};
        if (n == 1)
            return {"()"};
        vector<string> res;
        string str = "";
        dfs(res, str, n, n, n);
        return res;
    }
};

int main()
{
    auto s = new Solution();
    auto res = s->generateParenthesis(5);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}