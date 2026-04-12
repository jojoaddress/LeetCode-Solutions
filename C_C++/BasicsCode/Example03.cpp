/*
找出一个二维数组中的鞍点，
即该位置上的元素在该行上最大，在该列上最小，也可能没有鞍点
*/
#include <iostream>
using namespace std;
#define A_COL_MAX 4
#define A_ROW_MAX 4

pair<int, int> minCol(int a[][A_COL_MAX], int row, int col)
{
    int minNum = a[row][col];
    int res = -1;
    for (int i = 0; i < A_COL_MAX; i++)
    {
        if (a[i][col] < minNum)
        {
            minNum = a[i][col];
            res = i;
        }
    }
    if (res < 0)
    {
        return {row, col};
    }
    return {res, col};
}

pair<int, int> maxRow(int a[][A_COL_MAX], int row, int col)
{
    int maxNum = a[row][col];
    int res = -1;
    for (int i = 0; i < A_ROW_MAX; i++)
    {
        if (a[row][i] > maxNum)
        {
            maxNum = a[row][i];
            res = i;
        }
    }
    if (res < 0)
    {
        return {row, col};
    }
    return {row, res};
}

void calRes(int a[][A_COL_MAX])
{
    for (int i = 0; i < A_ROW_MAX; i++)
    {
        for (int j = 0; j < A_COL_MAX; j++)
        {
            // cout << minCol(a, i, j).first << " " << minCol(a, i, j).second << endl;
            // cout << maxRow(a, i, j).first << " " << maxRow(a, i, j).second << endl;
            if (minCol(a, i, j) == maxRow(a, i, j))
            {
                cout << "(i,j):" << i << "," << j << endl;
            }
        }
    }
}

int main()
{
    int a[A_ROW_MAX][A_COL_MAX] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4}};
    calRes(a);
    return 0;
}