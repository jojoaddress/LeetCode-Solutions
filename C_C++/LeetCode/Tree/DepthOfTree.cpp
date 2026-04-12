#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <stack>
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
    int dfs(TreeNode *root)
    {
        if(root==nullptr)
            return 0;
        return max(dfs(root->left), dfs(root->right)) + 1;
    }
    int bfs(TreeNode *root)
    {
        int res = 0;
        queue<TreeNode *> q;
        if(root==nullptr)
            return res;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            while (size!=0)
            {
                TreeNode *node = q.front();
                q.pop();
                if(node->left!=nullptr)
                    q.push(node->left);
                if(node->right!=nullptr)
                    q.push(node->right);
                size -= 1;
            }
            res++;
        }
        return res;
    }
    int maxDepth(TreeNode* root) {
        
    }
};