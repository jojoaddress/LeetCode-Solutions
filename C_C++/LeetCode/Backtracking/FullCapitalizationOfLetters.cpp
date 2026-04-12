/**
 * 字母大小写排列
 * 给定一个字符串 s ，通过将字符串 s 中的每个字母转变大小写，我们可以获得一个新的字符串。
 * 返回 所有可能得到的字符串集合 。以 任意顺序 返回输出。
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    char changeLetter(char c)
    {
        if (c >= 'a' && c <= 'z')
        {
            return c - ('a' - 'A');
        }
        if (c >= 'A' && c <= 'Z')
        {
            return c + ('a' - 'A');
        }
        return NULL;
    }
    void dfs(vector<string> &res, string &s, int index, int n)
    {
        for (int i = index; i < n; i++)
        {
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            {
                s[i] = changeLetter(s[i]);
                dfs(res, s, i + 1, n);
                s[i] = changeLetter(s[i]);
            }
        }
        res.push_back(s); // 此句需写在循环下面，这意味着每个叶子结点都会加入结果
    }
    vector<string> letterCasePermutation(string s)
    {
        vector<string> res;
        int n = s.size();
        dfs(res, s, 0, n);
        return res;
    }
};

int main()
{
    string str = "a1b2";
    auto s = new Solution();
    auto res = s->letterCasePermutation(str);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}