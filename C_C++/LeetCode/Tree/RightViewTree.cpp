#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
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
    TreeNode *buildTree(const vector<string> &nodes)
    {
        if (nodes.empty() || nodes[0] == "null")
        {
            return nullptr;
        }
        int rootVal = stoi(nodes[0]);
        TreeNode *root = new TreeNode(rootVal);
        queue<TreeNode *> q;
        q.push(root);
        int index = 1;
        while (!q.empty() && index < nodes.size())
        {
            TreeNode *current = q.front();
            q.pop();
            // Process left child
            if (index < nodes.size() && nodes[index] != "null")
            {
                int leftVal = stoi(nodes[index]);
                current->left = new TreeNode(leftVal);
                q.push(current->left);
            }
            index++;
            // Process right child
            if (index < nodes.size() && nodes[index] != "null")
            {
                int rightVal = stoi(nodes[index]);
                current->right = new TreeNode(rightVal);
                q.push(current->right);
            }
            index++;
        }
        return root;
    }

    // 层序遍历
    vector<int> rightSideView(TreeNode *root)
    {
        queue<TreeNode *> q;
        vector<int> result;
        if (root == nullptr)
            return result;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (node->left != nullptr)
                {
                    q.push(node->left);
                }
                if (node->right != nullptr)
                {
                    q.push(node->right);
                }

                if (i == size - 1)
                {
                    result.push_back(node->val);
                }
            }
        }

        return result;
    }

    // 先递归右子树
    void dfs(TreeNode *root, int depth)
    {
        if(root == nullptr)
            return;
        if(depth == ans.size())
        {
            ans.push_back(root->val);
        }
        dfs(root->right, depth + 1);
        dfs(root->left, depth + 1);
    }
    vector<int> rightSideView(TreeNode *root)
    {
        dfs(root, 0);
        return ans;
    }
private:
    vector<int> ans;
};

int main()
{
    auto s = new Solution;
    vector<string> input = {"1", "2", "3", "4", "null", "null", "null", "5"};
    TreeNode *root = s->buildTree(input);
    vector<int> res;
    res = s->rightSideView(root);
    return 0;
}