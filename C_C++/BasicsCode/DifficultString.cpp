/**
 * 如果一个字符串包含两个相邻的重复子串，则称它是“容易的串”，其他串称为“困难的串”。例如， BB、
 * ABCDABCD都是容易的串，而D、DC、ABDAD、CBABCBA都是困难的串。
 * 输入正整数n和L，输出由前L个字符组成的、字典序第n个困难的串。例如，当L=3时，前7个困难的串 分别
 * 为A、AB、ABA、ABAC、ABACA、ABACAB、ABACABA。输入保证答案不超过80个字符。
 */
#include <iostream>
#include <vector>
#include <regex>
#include <string>
using namespace std;

const string str = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

class Solution
{
public:
    bool isValid(vector<string> &tmp)
    {
        if (tmp.empty() || tmp.size() == 1)
        {
            return false;
        }

        ostringstream oss;
        for (const auto &str : tmp)
        {
            oss << str;
        }
        string concatenatedString = oss.str();
        int len = concatenatedString.length();
        // 遍历string，确认判断字符串是否包含两个相邻的重复子串
        for (int i = 1; i <= len / 2; ++i)
        {
            for (int j = 0; j <= len - 2 * i; ++j)
            {
                std::string substr1 = concatenatedString.substr(j, i);
                std::string substr2 = concatenatedString.substr(j + i, i);
                if (substr1 == substr2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(vector<vector<string>> &res, vector<string> &tmp, int depth, int n, int l)
    {
        if (isValid(tmp))
            return false;
        if (depth == n)
        {
            res.push_back(tmp);
            if (tmp.size() == n)
                return true;
        }
        for (int i = 0; i < l; i++)
        {
            tmp.emplace_back(string(1, str[i]));
            if (dfs(res, tmp, depth + 1, n, l))
                return true;
            tmp.pop_back();
        }
        return false;
    }

    vector<vector<string>> getRes(int n, int l)
    {
        auto res = vector<vector<string>>();
        auto tmp = vector<string>();
        dfs(res, tmp, 0, n, l);
        return res;
    }
};

int main()
{
    auto s = new Solution();
    s->getRes(7, 3);
    return 0;
}