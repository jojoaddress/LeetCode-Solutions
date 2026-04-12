#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isValid()
    {
        return (path[0] * path[1] - path[2] * path[3] - path[4] == 1);
    }
    void dfs(int step)
    {
        if (step == 5)
        {
            if (isValid())
                res.push_back(path);
            return;
        }
        for (int i = 1; i <= 5; i++)
        {
            if (!used[i])
            {
                used[i] = true;
                path[step] = i;
                dfs(step + 1);
                used[i] = false;
            }
        }
    }

    void input()
    {
        path.resize(5, 0);
        used.resize(6, false);
        dfs(0);
    }
    void output()
    {
        cout << "All solutions are as follows:" << endl
             << endl;

        for (const auto &sol : res)
        {
            int a = sol[0], b = sol[1], c = sol[2], d = sol[3], e = sol[4];
            cout << "  " << a << " * " << b << " - " << c
                 << " * " << d << " - " << e << " = 1" << endl;
        }
    }

      int getNumberOfSolutions() const {
        return res.size();
    }

private:
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used;
};

int main()
{
    auto s = new Solution;
    s->input();
    cout << "The number of solutions is: " << s->getNumberOfSolutions() << endl;
    cout << endl;

    s->output();

    return 0;
}