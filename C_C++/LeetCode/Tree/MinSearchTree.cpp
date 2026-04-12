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

class Solution {
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
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *> st;
        int cnt = 1;
        while(!st.empty()||root!=nullptr)
        {
            while(root!=nullptr)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            if(cnt==k)
            {
                return root->val;
            }
            cnt++;
            root = root->right;
        }
        return 0;
    }
};

int main()
{
    auto s = new Solution;
    vector<string> input = {"5", "3", "6", "2", "4", "null", "null","1"};
    TreeNode *root = s->buildTree(input);
    cout << s->kthSmallest(root,3);
    return 0;
}