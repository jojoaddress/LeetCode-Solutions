/**
 * 733. 图像渲染
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &image, int x, int y, int oldcolor, int newcolor)
    {
        if (x < 0 || x >= image.size() || y < 0 || y >= image[0].size() )
        {
            return;
        }
        //写到后面是为了防止堆栈溢出
        if(image[x][y] != oldcolor) return;

        image[x][y] = newcolor;

        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, 1, -1, 0};
        for (int i = 0; i < 4; i++)
        {
            dfs(image, x + dx[i], y + dy[i], oldcolor,newcolor);
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        dfs(image, sr, sc, image[sr][sc], color);
        return image;
    }
};

int main()
{
    vector<vector<int>> board = {
        {1, 1, 0},
        {1, 1, 0},
        {1, 0, 1}};
    auto s = new Solution();
    s->floodFill(board, 1, 1, 2);
    return 0;
}