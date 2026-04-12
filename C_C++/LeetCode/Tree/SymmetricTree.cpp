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

//错误思路，中序遍历的输出无法判断是否为镜像
class Solution {
public:
    void inorderTree(TreeNode* root)
    {
        if(root==nullptr)
            return ;
        inorderTree(root->left);
        res.push_back(root->val);
        inorderTree(root->right);
    }

    bool isSymmetric(TreeNode* root) {
        if(root->left==nullptr&&root->right==nullptr)
            return true;
        if(root->left==nullptr||root->right==nullptr)
            return false;
        inorderTree(root);
        int i = 0, j = res.size() - 1;
        while(i<j)
        {
            if(res[i]!=res[j])
                return false;
            ++i;
            --j;
        }
        return true;
    }
private:
    vector<int> res;
};

//很妙
class Solution {
public:
    bool check(TreeNode *p, TreeNode *q)
    {
        if(!p&&!q)
            return true;
        if(!p||!q)
            return false;
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }
    bool isSymmetric(TreeNode* root) {
        return check(root->left, root->right);
    }
};