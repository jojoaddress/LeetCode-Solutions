#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMinStep(string board, string hand) {
        unordered_map<char, int> handCount;
        for (char c : hand) {
            handCount[c]++;
        }
        return dfs(board, handCount);
    }

private:
    int dfs(string board, unordered_map<char, int> handCount) {
        if (board.empty()) return 0; // 如果棋盘为空，返回0步
        board = removeConsecutive(board); // 移除连续的球
        if (board.empty()) return 0; // 如果移除后棋盘为空，返回0步
        int minSteps = INT_MAX;
        
        for (int i = 0; i < board.size(); i++) {
            char current = board[i];
            int needed = 3; // 至少需要3个相同的球才能消除
            
            while (i < board.size() && board[i] == current) {
                needed--;
                i++;
            }
            
            if (needed > 0 && handCount[current] >= needed) {
                handCount[current] -= needed; // 使用手中的球
                int steps = dfs(board.substr(0, i) + board.substr(i), handCount);
                if (steps != -1) {
                    minSteps = min(minSteps, steps + needed);
                }
                handCount[current] += needed; // 回溯
            }
            i--; // 回退到当前球的最后一个位置
        }
        
        return minSteps == INT_MAX ? -1 : minSteps;
    }

    string removeConsecutive(string board) {
        for (int i = 0; i < board.size(); ) {
            int j = i;
            while (j < board.size() && board[j] == board[i]) {
                j++;
            }
            if (j - i >= 3) {
                board.erase(i, j - i); // 移除连续的球
                i = 0; // 从头开始检查
            } else {
                i = j; // 移动到下一个不同的球
            }
        }
        return board;
    }
};

int main() {
    Solution solution;
    string board = "G";
    string hand = "GGGGG";
    int result = solution.findMinStep(board, hand);
    cout << result << endl; // 示例输出
    return 0;
}