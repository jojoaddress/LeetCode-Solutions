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
    TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder)
    {
        if (preorder.size() == 0)
            return nullptr;
        if (preorder.size() == 1)
            return new TreeNode(preorder[0]);
        int left_size = std::find(postorder.begin(), postorder.end(), preorder[1]) - postorder.begin()+1;
        vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_size);
        vector<int> pre2(preorder.begin() + 1 + left_size, preorder.end());
        vector<int> post1(postorder.begin(), postorder.begin() + left_size);
        vector<int> post2(postorder.begin() + left_size, postorder.end()-1);
        TreeNode *left = constructFromPrePost(pre1, post1);
        TreeNode *right = constructFromPrePost(pre2, post2);
        return new TreeNode(preorder[0], left, right);
    }
};

int main()
{
    auto s = new Solution;
    vector<int> preorder = {1,2,4,5,3,6,7};
    vector<int> postorder = {4,5,2,6,7,3,1};
    TreeNode *root = s->constructFromPrePost(preorder, postorder);
    return 0;
}