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

TreeNode *root;

class Solution
{
public:
    //按层输入，例如1,2,3,-1,-1,4,5
    TreeNode *buildTree(const string &data)
    {
        if (data.empty())
            return nullptr;

        vector<string> values;
        stringstream ss(data);
        string item;

        while (getline(ss, item, ','))
        {
            values.push_back(item);
        }

        if (values[0] == "null")
            return nullptr;

        TreeNode *root = new TreeNode(stoi(values[0]));
        queue<TreeNode *> nodeQueue;
        nodeQueue.push(root);

        size_t index = 1;
        while (!nodeQueue.empty() && index < values.size())
        {
            TreeNode *node = nodeQueue.front();
            nodeQueue.pop();

            // 左子节点
            if (index < values.size() && values[index] != "null")
            {
                node->left = new TreeNode(stoi(values[index]));
                nodeQueue.push(node->left);
            }
            index++;

            // 右子节点
            if (index < values.size() && values[index] != "null")
            {
                node->right = new TreeNode(stoi(values[index]));
                nodeQueue.push(node->right);
            }
            index++;
        }

        return root;
    
    }
    void dfs(TreeNode *root)
    {
        if(root==nullptr)
            return;  
        dfs(root->left);
        res.push_back(root->val);
        dfs(root->right);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        dfs(root);
        return res;
    }
private:
    vector<int> res;
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> st;
        while(root!=nullptr&&!st.empty())
        {
            while(root!=nullptr)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
