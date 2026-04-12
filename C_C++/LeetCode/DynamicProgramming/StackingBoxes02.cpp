/**堆箱子。给你一堆n个箱子，箱子宽 wi、深 di、高 hi。箱子不能翻转，
 * 将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。
 * 实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    int pileBox(vector<vector<int>> &box)
    {
        sort(box.begin(), box.end(), [=](vector<int> a, vector<int> b)
             { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]) || (a[0] == b[0] && a[1] == b[1] && a[2] < b[2]); });
        int size = box.size();
        vector<int> dp(size);
        for (int i = 0; i < size; i++)
        {
            dp[i] = box[i][2];
        }

        for (int i = 1; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (box[i][0] > box[j][0] &&
                    box[i][1] > box[j][1] &&
                    box[i][2] > box[j][2])
                {
                    // 以防出现第i个箱子比j个箱子加起来高的情况
                    dp[i] = max(dp[i], dp[j] + box[i][2]);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

int main()
{
    vector<vector<int>> boxes = {{1, 1, 1}, {2, 3, 4}, {2, 6, 7}, {3, 4, 5}};
    auto s = new Solution();
    cout << s->pileBox(boxes) << endl;
    return 0;
}