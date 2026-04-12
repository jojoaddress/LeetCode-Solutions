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

class solution
{
public:
    double maxBagValue(vector<double> &weights, vector<double> &values, double capacity)
    {
        int n = weights.size();
        vector<pair<double, double>> vp;
        for (int i = 0; i < n; i++)
        {
            vp.push_back({values[i] / weights[i], weights[i]});
        }

        sort(vp.begin(), vp.end(), [](const pair<double, double> a, const pair<double, double> b)
             { return a.first > b.first; });

        double res = 0;
        for (auto &[value, weight] : vp)
        {
            if (weight <= capacity)
            {
                res += value * weight;
                capacity -= weight;
            }
            else
            {
                res += value * capacity;
                break;
            }
        }
        return res;
    }
};

int main()
{
    solution sol;
    vector<double> weights = {2, 6, 7, 4, 10, 3};
    vector<double> values = {8, 1, 9, 3, 2, 4};
    double capacity = 19.0;
    double maxValue = sol.maxBagValue(weights, values, capacity);
    cout << "Max bag value: " << maxValue << endl;
    return 0;
}