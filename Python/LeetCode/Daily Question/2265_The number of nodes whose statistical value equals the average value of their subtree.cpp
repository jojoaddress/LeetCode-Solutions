#include <iostream>
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
    int averageOfSubtree(TreeNode *root)
    {
        int res = 0;
        auto dfs = [&](this auto &&dfs, TreeNode *root) -> pair<int, int>
        {
            if (root == nullptr)
                return {0, 0};
            auto [lsum, lnum] = dfs(root->left);
            auto [rsum, rnum] = dfs(root->right);
            int sum = root->val + lsum + rsum;
            int num = 1 + lnum + rnum;
            if (sum / num == root->val)
                res++;
            return {sum, num};
        };
        return res;
    }
};