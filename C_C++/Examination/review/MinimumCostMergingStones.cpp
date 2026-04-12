#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int dfs(int i, int j, int p)
    {
        int &res = memo[i][j][p];
        if (res != -1)
            return res;
        if (p == 1)
            return res = i == j ? 0 : dfs(i, j, K) + sum[j + 1] - sum[i];
        res = INT_MAX;
        for (int m = i; m < j; m += K - 1)
        {
            res = min(res, dfs(i, m, 1) + dfs(m + 1, j, p - 1));
        }
        return res;
    }
    int mergeStones(vector<int> &stones, int k)
    {
        K = k;
        int n = stones.size();
        if((n-1)%(K-1))
            return -1;
        sum = vector<int>(n + 1);
        for (int i = 0; i < n; i++)
            sum[i + 1] = sum[i] + stones[i];
        memo = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(K + 1, -1)));
        return dfs(0, n - 1, 1);
    }

private:
    int K;
    vector<int> sum;
    vector<vector<vector<int>>> memo;
};

int main()
{
    Solution sol;
    vector<int> stones = {3,5,1,2,6};
    int k = 3;
    cout << sol.mergeStones(stones, k) << endl;
    return 0;
}