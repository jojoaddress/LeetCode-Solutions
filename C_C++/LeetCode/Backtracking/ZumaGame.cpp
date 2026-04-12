#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution
{
public:
    void fullsort(string hand, string &temp, unordered_set<string> &res, vector<bool> &dp, int depth)
    {
        if (depth == hand.size())
        {
            res.insert(temp);
            return;
        }
        for (int i = 0; i < hand.size(); i++)
        {
            if (dp[i])
                continue; // 如果已经使用，跳过
            // 跳过重复字符
            if (i > 0 && hand[i] == hand[i - 1] && !dp[i - 1])
                continue;
            dp[i] = true;
            temp.push_back(hand[i]);
            fullsort(hand, temp, res, dp, depth + 1);
            temp.pop_back();
            dp[i] = false;
        }
    }

    bool dfs(string &board, string hand, int depth, int &cnt)
    {
        if (board.empty())
        {
            return true; // 如果棋盘为空，返回成功
        }
        if (depth == hand.size())
        {
            return false; // 如果手牌用完，返回失败
        }
        for (int i = 0; i < board.size(); i++)
        {
            if (board[i] == hand[depth])
            {
                char temp = board[i];
                board.erase(i, 1); // 移除当前球
                cnt++;             // 计数增加
                // 消除后检查是否有连续的球可以消除
                int left = i - 1, right = i; // 左右指针
                while (left >= 0 && board[left] == temp)
                {
                    board.erase(left, 1);
                    cnt++;
                    left--; // 更新左指针
                }
                while (right < board.size() && board[right] == temp)
                {
                    board.erase(right, 1);
                    cnt++;
                }
                // 递归调用
                if (dfs(board, hand, depth + 1, cnt))
                {
                    return true; // 如果成功，返回
                }
                // 回溯
                cnt--;                    // 计数减少
                board.insert(i, 1, temp); // 恢复当前球
                // 恢复消除的球
                for (int j = 0; j < cnt; j++)
                {
                    board.insert(i, 1, temp); // 恢复消除的球
                }
            }
        }
        return false; // 如果没有找到解决方案，返回失败
    }

    int findMinStep(string board, string hand)
    {
        int minSteps = INT_MAX;
        unordered_set<string> hands;
        vector<bool> dp(hand.size(), false);
        string temp;
        fullsort(hand, temp, hands, dp, 0);
        for (const string &h : hands)
        {
            int sum = 0;
            if (dfs(board, h, 0, sum))
            {
                minSteps = min(minSteps, sum);
            }
        }
        return minSteps == INT_MAX ? -1 : minSteps;
    }
};

int main()
{
    Solution s;
    cout << s.findMinStep("WWRRBBWW", "WRBRW") << endl; // 示例输出
    return 0;
}