#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    void outPut(vector<vector<string>> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[0].size(); j++)
            {
                cout << res[i][j] << endl;
            }
            cout << "-----" << endl;
        }
    }

    bool isVaild(vector<string> board, int i, int j)
    {
        // 上
        for (int a = 0; a <= i; a++)
        {
            if (board[a][j] == 'Q')
                return false;
        }

        // 左上,不能从（0,0）开始检查，因为他的左上可能到不了（0,0）
        for (int a = i, b = j; a >= 0 && b >= 0; a--, b--)
        {
            if (board[a][b] == 'Q')
                return false;
        }

        // 右上
        for (int a = i, b = j; a >= 0 && b < board.size(); a--, b++)
        {
            if (board[a][b] == 'Q')
                return false;
        }
        return true;
    }

    void dfs(vector<string> &board, vector<vector<string>> &res, int depth, int n, int &num)
    {
        if (depth == n)
        {
            res.push_back(board);
            num++;
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (isVaild(board, depth, i))
            {
                board[depth][i] = 'Q';
                dfs(board, res, depth + 1, n, num);
                board[depth][i] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        auto board = vector<string>(n, string(n, '.'));
        vector<vector<string>> res;
        dfs(board, res, 0, n, num);
        return res;
    }

public:
    int num = 0;
};

int main()
{
    int n;
    cin >> n;
    auto s = new Solution();
    auto res = s->solveNQueens(n);
    s->outPut(res);
    cout << s->num;
}