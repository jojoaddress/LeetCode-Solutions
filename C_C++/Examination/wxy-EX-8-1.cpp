#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class PrimeGridSolver
{
public:
    bool isPrime(int num)
    {
        if (num <= 1)
            return false;
        if (num == 2)
            return true;
        if (num % 2 == 0)
            return false;
        int limit = sqrt(num);
        for (int i = 3; i <= limit; i += 2)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    bool isValid(int x, int y, int value)
    {
        if (x > 0 && grid[x - 1][y] != 0)
        {
            if (!isPrime(value + grid[x - 1][y]))
                return false;
        }
        if (x < 2 && grid[x + 1][y] != 0)
        {
            if (!isPrime(value + grid[x + 1][y]))
                return false;
        }
        if (y > 0 && grid[x][y - 1] != 0)
        {
            if (!isPrime(value + grid[x][y - 1]))
                return false;
        }
        if (y < 2 && grid[x][y + 1] != 0)
        {
            if (!isPrime(value + grid[x][y + 1]))
                return false;
        }
        return true;
    }

    void dfs(int pos)
    {
        if (pos == 9)
        {
            solutions.push_back(grid);
            solutionCount++;
            return;
        }
        int x = pos / 3;
        int y = pos % 3;
        for (int num = 1; num <= n; num++)
        {
            if (!used[num])
            {
                if (isValid(x, y, num))
                {
                    grid[x][y] = num;
                    used[num] = true;
                    dfs(pos + 1);
                    grid[x][y] = 0;
                    used[num] = false;
                }
            }
        }
    }

    void input(int limit)
    {
        n = limit;
        used = vector<bool>(n + 1, false);
        grid = vector<vector<int>>(3, vector<int>(3, 0));
        solutionCount = 0;
        solutions.clear();
        dfs(0);
    }

    int getSolutionCount() const
    {
        return solutionCount;
    }

    void output() const
    {
        cout << "All solutions are shown as follows:" << endl
             << endl;

        for (int idx = 0; idx < solutionCount; idx++)
        {
            cout << "Solution " << (idx + 1) << ":" << endl
                 << endl;

            for (int i = 0; i < 3; i++)
            {
                cout << "  ";
                for (int j = 0; j < 3; j++)
                {
                    cout << setw(2) << solutions[idx][i][j] << " ";
                }
                cout << endl;
            }

            if (idx < solutionCount - 1)
            {
                cout << endl;
            }
        }
    }

private:
    int n;
    vector<bool> used;
    vector<vector<int>> grid;
    vector<vector<vector<int>>> solutions;
    int solutionCount;
};

int main()
{
    PrimeGridSolver solver;

    int n;
    cout << "Please enter the upper bound of digits to be filled in 3 * 3 grid(10):" << endl;
    cin >> n;

    solver.input(n);
    if (solver.getSolutionCount() == 0)
    {
        cout << "No solutions!" << endl;
        return 0;
    }

    cout << "The number of solutions is: " << solver.getSolutionCount() << endl;
    cout << endl;

    if (solver.getSolutionCount() > 0)
    {
        solver.output();
    }

    return 0;
}