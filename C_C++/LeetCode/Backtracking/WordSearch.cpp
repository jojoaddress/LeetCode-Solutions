#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool dfs(vector<vector<char>> &board, string word, int depth, int x, int y)
    {
        if (depth == word.size())
        {
            return true;
        }
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || board[x][y] != word[depth])
            return false;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        char temp = board[x][y];
        board[x][y] = '#';
        bool found = false;
        for (int i = 0; i < 4; i++)
        {
            found |= dfs(board, word, depth + 1, x + dx[i], y + dy[i]);
        }
        board[x][y] = temp;

        return found;
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == word[0])
                {
                    if (dfs(board, word, 0, i, j))
                        return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    auto s = new Solution();
    vector<vector<char>> board = {{'A', 'B', 'C', 'E'},
                                  {'S', 'F', 'C', 'S'},
                                  {'A', 'D', 'E', 'E'}};
    string word = "SEE";
    cout << s->exist(board, word);
}