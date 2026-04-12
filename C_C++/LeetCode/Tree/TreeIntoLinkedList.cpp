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

    void dfs_(TreeNode *root)
    {
        if (root == nullptr)
            return;
        list.push_back(root);
        dfs(root->left);
        dfs(root->right);
    }

    void flatten_(TreeNode *root)
    {
        dfs(root);
        for (int i = 1.; i < list.size(); i++)
        {
            root->left = nullptr;
            root->right = list[i];
            root = root->right;
        }
    }

    // 大佬方法
    void dfs(TreeNode *root)
    {
        if(root==nullptr)
            return;
        dfs(root->right);
        dfs(root->left);
        root->left = nullptr;
        root->right = head;
        head =root;
    }
    void flatten(TreeNode *root)
    {
        dfs(root);
    }

private:
    vector<TreeNode *> list;
    TreeNode *head;
};

int main()
{
    auto s = new Solution;
    vector<string> input = {"1", "2", "5", "3", "4", "null", "6"};
    TreeNode *root = s->buildTree(input);
    s->flatten(root);
    return 0;
}