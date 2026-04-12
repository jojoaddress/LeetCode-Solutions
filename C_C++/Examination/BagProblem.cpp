#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class BagProblem
{
public:
    double maxBagValue(vector<double> &weights, vector<double> &values, double capacity)
    {
        int n = weights.size();
        double step = 0.01;
        int steps = (int)(capacity / step) + 1;
        vector<double> dp(steps + 1, 0.0);
        for (int i = 0; i < n; i++)
        {
            int weightSteps = (int)(weights[i] / step + 0.5);
            for (int j = steps; j >= weightSteps; j--)
            {
                dp[j] = max(dp[j], dp[j - weightSteps] + values[i]);
            }
        }
        return dp[steps];
    }
};

int main()
{
    BagProblem bagProblem;
    vector<double> weights = {0.5, 1.2, 3.0, 2.1};
    vector<double> values = {10.0, 20.0, 30.0, 40.0};
    double capacity;
    cin >> capacity;
    double maxValue = bagProblem.maxBagValue(weights, values, capacity);
    cout << maxValue << endl;
    return 0;
}