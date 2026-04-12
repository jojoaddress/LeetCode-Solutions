/**
 * 给定一个承重量为C的背包，n个重量分别为w1,w2,...,wn的物品，物品i放入背包能产生pi(>0)的价值
 * (i=1,2,...,n)。 每个物品要么整个放入背包，要么不放。要求找出最大价值的装包方案。
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Soultion
{
public:
    void dfs(vector<pair<int, int>> a, int &resDepthMax, int &resValueMax, vector<bool> &tag, int depth, int value, int container)
    {
        if (depth > container)
        {
            return;
        }
        if (depth == container)
        {
            if (value > resDepthMax)
            {
                resDepthMax = value;
            }
        }
        if (value > resValueMax)
        {
            resValueMax = value;
        }
        for (int i = 0; i < a.size(); i++)
        {
            if (!tag[i])
            {
                tag[i] = true;
                dfs(a, resDepthMax, resValueMax, tag, depth + a[i].first, value + a[i].second, container);
                tag[i] = false;
            }
        }
    }
    vector<int> solve(vector<pair<int, int>> a, int container)
    {
        vector<int> res;
        vector<bool> tag(a.size(), false);
        int resDepthMax = 0;
        int resValueMax = 0;
        dfs(a, resDepthMax, resValueMax, tag, 0, 0, container);
        res.push_back(resValueMax);
        res.push_back(resDepthMax);
        return res;
    }
};
int main()
{
    vector<pair<int, int>> a = {{12, 6}, {11, 8}, {6, 8}};
    vector<pair<int, int>> a1 = {{2, 10}, {4, 5}, {1, 4}};
    auto s = new Soultion();
    int container = 5;
    auto res = s->solve(a1, container);
    return 0;
}