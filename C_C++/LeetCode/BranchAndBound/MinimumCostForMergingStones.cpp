#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// 1 2 3 4
// 0 1 3 6 10
// dfs(i,j,p) = dfs(i,j,K) + sum[j+1]-sum[i] if p==1
// dfs(i,j,p) = min(dfs(i,m,1)+dfs(m+1,j,p-1)) if p>1
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
            res = min(res, dfs(i, m, 1) + dfs(m + 1, j, p - 1));
        return res;
    }
    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        if ((n - 1) % (k - 1))
            return -1;
        K = k;
        sum = vector<int>(n + 1);
        sum[0] = 0;
        for (int i = 0; i < n; i++)
            sum[i + 1] = sum[i] + stones[i];

        memo = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
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
    vector<int> stones = {3, 2, 4, 1};
    int k = 2;
    cout << sol.mergeStones(stones, k) << endl;
    return 0;
}