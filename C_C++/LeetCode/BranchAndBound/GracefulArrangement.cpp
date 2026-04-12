#include <iostream>
#include <vector>
using namespace std;

class Solution
{

private:
    vector<vector<int>> match;
    vector<bool> visited;
    int result;

public:
    void dfs(int index, int n)
    {
        if (index == n + 1)
        {
            result++;
            return;
        }
        for (auto m : match[index])
        {
            if (!visited[m])
            {
                visited[m] = true;
                dfs(index + 1, n);
                visited[m] = false;
            }
        }
        return;
    }
    int countArrangement(int n)
    {
        match.clear();
        match.resize(n + 1);
        visited.resize(n + 1, false);
        result = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i % j == 0 || j % i == 0)
                    match[i].push_back(j);
            }
        }
        dfs(1, n);
        return result;
    }
};

int main()
{
    Solution sol;
    cout << sol.countArrangement(1) << endl; // Output: 1
    cout << sol.countArrangement(2) << endl; // Output: 2
    cout << sol.countArrangement(3) << endl; // Output: 3
    cout << sol.countArrangement(4) << endl; // Output: 8
    return 0;
}