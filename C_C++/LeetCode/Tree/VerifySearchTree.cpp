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
    /*   方法一：最开始的本方法
        bool isValid(TreeNode *root, int val, bool jud)
        {
            if(root==nullptr)
                return true;
            if(jud)
            {
                if(root->val>=val)
                    return false;
            }
            else
            {
                if(root->val<=val)
                    return false;
            }
            return isValid(root->left, val, jud)&&isValid(root->right, val, jud);
        }
        bool isValidBST(TreeNode* root) {
            queue<TreeNode *> q;
            queue<TreeNode *> tmpQ;
            tmpQ.push(root);
            while(!tmpQ.empty())
            {
                TreeNode *node = tmpQ.front();
                tmpQ.pop();
                q.push(node);
                if(node->left!=nullptr)
                    tmpQ.push(node->left);
                if(node->right!=nullptr)
                    tmpQ.push(node->right);
            }

            while(!q.empty())
            {
                TreeNode *node = q.front();
                q.pop();
                if(!isValid(node->left,node->val,true))
                    return false;
                if(!isValid(node->right,node->val,false))
                    return false;
            }
            return true;
        }
    */

    /*方法二：递归*/
    bool isValid(TreeNode *root, long long low, long long high)
    {
        if (root == nullptr)
            return true;
        if (root->val <= low || root->val >= high)
            return false;
        return isValid(root->left, low, root->val) && isValid(root->right, root->val, high);
    }
    bool isValidBST_(TreeNode *root)
    {
        return isValid(root, LONG_MIN, LONG_MAX);
    }

    /*方法三：中序遍历*/
    bool isValidBST(TreeNode *root)
    {
        stack<TreeNode *> st;
        long long preVal = LONG_MIN;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            if (root->val <= preVal)
                return false;
            preVal = root->val;
            root = root->right;
        }
        return true;
    }
};

int main()
{
    auto s = new Solution;
    vector<string> input = {"3", "1", "5", "0", "2", "4", "6"};
    TreeNode *root = s->buildTree(input);
    cout << s->isValidBST(root);
    return 0;
}