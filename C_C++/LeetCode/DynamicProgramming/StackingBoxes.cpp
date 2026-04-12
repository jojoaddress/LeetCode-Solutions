/**
 * dp[i] 表示以第 i 个箱子为最上层的最长套箱路径的长度。
 * 初始化时，所有的 dp[i] 值都设为 1，因为每个箱子至少可以单独存在，不套任何其他箱子。
 * 在动态规划的过程中，通过比较箱子之间的尺寸，更新 dp[i] 的值，
 * 以反映在第 i 个箱子上方可以放置的其他箱子的数量，从而计算出最长的套箱路径。
 *
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct Box
{
    int length, width, height;

    // 用于排序的比较函数
    bool operator<(const Box &b) const
    {
        return length < b.length && width < b.width && height < b.height;
    }
};

int maxNestingBoxes(vector<Box> &boxes)
{
    int n = boxes.size();
    vector<int> dp(n, 1); // 初始化 dp 数组

    // 对箱子进行排序
    sort(boxes.begin(), boxes.end(), [](const Box &a, const Box &b)
         { return a.length < b.length || (a.length == b.length && a.width < b.width) || (a.length == b.length && a.width == b.width && a.height < b.height); });

    // 动态规划计算最长套箱路径
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (boxes[i].length > boxes[j].length &&
                boxes[i].width > boxes[j].width &&
                boxes[i].height > boxes[j].height)
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // 返回最大值
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    vector<Box> boxes = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {2, 2, 2}};
    cout << "最长的套箱路径长度: " << maxNestingBoxes(boxes) << endl;
    return 0;
}