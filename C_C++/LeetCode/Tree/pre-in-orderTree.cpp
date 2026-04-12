#include <algorithm>
#include <cmath>
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if(preorder.size()==0)
            return nullptr;
        int left_size = std::find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();
        vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_size);
        vector<int> pre2(preorder.begin() + 1 + left_size, preorder.end());
        vector<int> in1(inorder.begin(), inorder.begin() + left_size);
        vector<int> in2(inorder.begin() + left_size+1, inorder.end());
        TreeNode *left = buildTree(pre1, in1);
        TreeNode *right = buildTree(pre2, in2);
        return new TreeNode(preorder[0], left, right);
    }
};

int main()
{
    auto s = new Solution;
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode* root = s->buildTree(preorder, inorder);
    return 0;
}