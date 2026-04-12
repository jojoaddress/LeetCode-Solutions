#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
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
    /*
    1.节点选上。保存此节点，继续往下走直到有刚好等于num的temp出现
    2.节点没选上。跳过此节点，看左右子树
    */
    void dfs(TreeNode *root, long long s, int targetSum)
    {

        if (root == nullptr)
            return;
        s += root->val;
        ans += cnt[s - targetSum];
        cnt[s]++;
        dfs(root->left, s,targetSum);
        dfs(root->right, s, targetSum);
        cnt[s]--;
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        dfs(root, 0, targetSum);
        return ans;
    }

private:
    int ans = 0;
    unordered_map<long long, int> cnt{{0, 1}};
};

int main()
{
    auto s = new Solution;
    vector<string> input = {"10", "5", "-3", "3", "2", "null", "11", "3", "-2", "null", "1"};
    TreeNode *root = s->buildTree(input);
    cout<<s->pathSum(root, 8);
    return 0;
}