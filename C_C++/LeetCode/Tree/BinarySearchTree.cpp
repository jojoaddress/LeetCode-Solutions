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
    TreeNode *insert(vector<int> nums, int p, int q)
    {
        int size = nums.size();
        if (p >= q)
            return nullptr;
        TreeNode *node = new TreeNode;
        int mid = (q + p) / 2;
        node->val = nums[mid];
        node->left = insert(nums, p, mid);
        node->right = insert(nums, mid + 1, q);
        return node;
    }
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        int size = nums.size();
        TreeNode * node = insert(nums, 0, size);
        return node;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {-10, -3, 0, 5, 9};
    s.sortedArrayToBST(nums);
    return 0;
}