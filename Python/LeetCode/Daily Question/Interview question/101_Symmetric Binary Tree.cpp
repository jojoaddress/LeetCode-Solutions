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
    bool isSymmetric(TreeNode* root) {
        auto dfs = [&](this auto &&dfs, TreeNode *p, TreeNode *q) ->bool
        {
            if(!q&&!p)
                return true;
            if(!q||!p)
                return false;
            return p->val == q->val && dfs(p->left, q->right) && dfs(p->right, q->left);
        };
        return dfs(root->left, root->right);
    }
};