#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    bool dfs(vector<vector<int>> &board, int x, int y)
    {
        int n = board.size();
        int m = board[0].size();
        if (x < 0 || x >= n || y < 0 || y >= m)
            return false;
        if (board[x][y] == 1)
            return false;
        board[x][y] = 1;
        res.push_back({x, y});
        if (x == n - 1 && y == m - 1)
            return true;
        for (int i = 0; i < 2; i++)
        {
            if(dfs(board,x+dx[i],y+dy[i]))
                return true;
        }
        res.pop_back();
        return false;
    }
    vector<vector<int>> pathWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        if(!dfs(obstacleGrid,0,0))
            return {};
        return res;
    }

private:
    int dx[2] = {0, 1};
    int dy[2] = {1, 0};
    vector<vector<int>> res;
};

int main()
{
    Solution sol;
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    vector<vector<int>> path = sol.pathWithObstacles(obstacleGrid);
    for (const auto &p : path)
    {
        cout << "(" << p[0] << "," << p[1] << ") ";
    }
    return 0;
}