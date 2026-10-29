#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool same = true;
        auto dfs = [&](this auto &&dfs, TreeNode *p, TreeNode *q) -> void
        {
            if(!same)
                return;
            if(!q&&!p)
                return;
            if(!q||!p)
            {
                same = false;
                return;
            }
            if(q->val!=p->val)
            {
                same = false;
                return;
            }
            dfs(p->left, q->left);
            dfs(p->right, q->right);
        };
        dfs(p, q);
        return same;
    }
};