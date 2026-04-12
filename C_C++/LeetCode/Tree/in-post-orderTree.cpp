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

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(!postorder.size())
            return nullptr;
        int test = postorder.back();
        int left_size = std::find(inorder.begin(), inorder.end(), postorder.back()) - inorder.begin();
        vector<int> post1(postorder.begin(), postorder.begin() + left_size);
        vector<int> post2(postorder.begin() + left_size, postorder.end() - 1);
        vector<int> in1(inorder.begin(), inorder.begin() + left_size);
        vector<int> in2(inorder.begin() + left_size + 1, inorder.end());
        TreeNode *left = buildTree(in1, post1);
        TreeNode *right = buildTree(in2, post2);
        return new TreeNode(postorder.back(), left, right);
    }
};

int main()
{
    auto s = new Solution;
    vector<int> postorder = {9,15,7,20,3};
    vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode* root = s->buildTree(inorder, postorder);
    return 0;
}