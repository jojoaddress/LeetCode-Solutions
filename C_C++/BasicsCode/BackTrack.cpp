/**
 * 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    void outPut(vector<int> a)
    {
        for (int i = 0; i < a.size(); i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    void backtrack(vector<vector<int>> &res, vector<int> &a, int depth, int len)
    {
        if (depth == len)
        {
            res.push_back(a); // 用这个结果输出的话，存储的是最后一层的叶子节点
            return;
        }
        for (int i = depth; i < len; i++)
        {
            swap(a[depth], a[i]);
            backtrack(res, a, depth + 1, len);
            swap(a[depth], a[i]);
        }
        // res.push_back(a); 用这个结果输出的话，存储的是所有叶子结点
    }
    vector<vector<int>> permute(vector<int> &a)
    {
        vector<vector<int>> res;
        backtrack(res, a, 0, a.size());
        return res;
    }
};

int main()
{
    vector<int> a = {1, 2, 3};
    auto s = new Solution();
    vector<vector<int>> res = s->permute(a);
    for (int i = 0; i < res.size(); i++)
    {
        cout << endl;
        for (int j = 0; j < res[0].size(); j++)
            cout << res[i][j] << " ";
    }
    return 0;
}