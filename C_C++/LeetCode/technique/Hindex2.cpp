/*
* 2023.10.30
* 给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数，citations 已经按照 升序排列 。计算并返回该研究者的 h 指数。
* h 指数的定义：h 代表“高引用次数”（high citations），一名科研人员的 h 指数是指他（她）的 （n 篇论文中）总共有 h 篇论文分别被引用了至少 h 次。
* 请你设计并实现对数时间复杂度的算法解决此问题。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int> &citations) {
        // 在区间 [left, right] 内询问
        int n = citations.size();
        int left = 1;
        int right = n;
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // left-1 的回答一定为「是」
            // right+1 的回答一定为「否」
            int mid = (left + right) / 2; // left+(right-left)/2
            // 引用次数最多的 mid 篇论文，引用次数均 >= mid
            if (citations[n - mid] >= mid) {
                left = mid + 1; // 询问范围缩小到 [mid+1, right]
            } else {
                right = mid - 1; // 询问范围缩小到 [left, mid-1]
            }
        }
        // 循环结束后 right 等于 left-1，回答一定为「是」
        // 根据循环不变量，right 现在是最大的回答为「是」的数
        return right;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> num = {0};
    cout<<s->hIndex(num)<<endl;
    return 0;
}
