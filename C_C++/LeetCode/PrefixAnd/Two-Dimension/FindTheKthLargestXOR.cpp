#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int kthLargestValue(vector<vector<int>> &matrix, int k)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        auto s = vector<vector<int>>(n + 1, vector<int>(m + 1));
        priority_queue<int> pq;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s[i + 1][j + 1] = s[i + 1][j] ^ s[i][j + 1] ^ s[i][j] ^ matrix[i][j];
                pq.push(s[i + 1][j + 1]);
            }
        }
        while(--k)
        {
            pq.pop();
        }
        return pq.top();
    }
};

int main()
{
    vector<vector<int>> matrix = {
        {5, 2},
        {1, 6}};
    int k = 3;
    Solution sol;
    int ans = sol.kthLargestValue(matrix, k);
    cout << ans << endl;
    return 0;
}