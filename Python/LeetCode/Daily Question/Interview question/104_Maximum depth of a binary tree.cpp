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

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        int res = 0;
        auto dfs = [&](this auto  &&dfs, TreeNode *root, int depth) ->void
        {
            if(!root)
                return;
            res = max(res, depth);
            dfs(root->left, depth + 1);
            dfs(root->right, depth + 1);
        };
        dfs(root, 1);
        return res;
    }
};