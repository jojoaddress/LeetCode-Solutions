/**
 * 全排列：给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
*/

#include <iostream>
#include <vector>
using namespace std;

void alg(vector<vector<int>> &res, vector<int> &num, vector<bool> &tag, vector<int> &temp, int depth, int len);
vector<vector<int>> premute(vector<int> &num);

int main()
{
    vector<int> num = {1, 2, 3};
    vector<vector<int>> res = premute(num);
    return 0;
}

void alg(vector<vector<int>> &res, vector<int> &num, vector<bool> &tag, vector<int> &temp, int depth, int len)
{
    
    if (depth == len)
    {
        res.emplace_back(temp);
        return;
    }

    for (int i = 0; i < len; i++)
    {
        if (!tag[i])
        {
            tag[i] = true;
            temp.emplace_back(num[i]);

            alg(res, num, tag, temp, depth + 1, len);

            tag[i] = false;
            temp.pop_back();
        }
    }
}

vector<vector<int>> premute(vector<int> &num)
{
    vector<vector<int>> res;
    int len = num.size();
    vector<bool> tag(len, false);
    vector<int> temp;
    alg(res, num, tag, temp, 0, len);
    return res;
}