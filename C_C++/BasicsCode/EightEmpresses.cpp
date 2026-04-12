/**
 * 在8×8格的国际象棋上摆放八个皇后（在n×n格的国际象棋上摆放n个皇后），使其不能互相攻击，即任意两个皇后都不能处于同一行、同一列或同
 * 一斜线上，问一共有多少种摆法。
 */
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    void outPut(vector<vector<string>> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                cout << res[i][j] << endl;
            }
            cout << "-----"<<endl;
        }
    }

    bool isVaild(vector<string> board, int i, int j)
    {
        // 上
        for (int a = 0; a < board.size(); a++)
        {
            if (board[a][j] == 'Q')
                return false;
        }
        // 左上
        for (int a = i, b = j; a >= 0 && b >= 0; --a, --b)
        {
            if (board[a][b] == 'Q')
                return false;
        }
        // 右上
        for (int a = i, b = j; a >= 0 && b < board[a].size(); --a, ++b)
        {
            if (board[a][b] == 'Q')
                return false;
        }
        return true;
    }

    bool dfs(vector<string> &board, int depth, int n)
    {
        if (depth == n)
        {
            res.push_back(board);
            return true;
        }

        for (int i = 0; i < n; i++)
        {
            if (isVaild(board, depth, i))
            {
                board[depth][i] = 'Q';
                if(dfs(board, depth + 1, n)) return true;
                board[depth][i] = '.';
            }
        }
        return false;
    }

    void dfs1(vector<string> &board, int depth, int n)
    {
        if (depth == n)
        {
            res.push_back(board);
            return ;
        }

        for (int i = 0; i < n; i++)
        {
            if (isVaild(board, depth, i))
            {
                board[depth][i] = 'Q';
                dfs1(board, depth + 1, n);
                board[depth][i] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        auto borad = vector<string>(n, string(n, '.'));
        dfs1(borad,0,n);
        return res;
    }

private:
    vector<vector<string>> res;
};

int main()
{
    auto s = new Solution();
    auto res = s->solveNQueens(4);
    s->outPut(res);
    return 0;
}