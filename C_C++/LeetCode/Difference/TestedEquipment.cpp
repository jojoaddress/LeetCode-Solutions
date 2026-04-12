#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int countTestedDevices(vector<int> &batteryPercentages)
    {
        int dec = 0;
        for (auto &b : batteryPercentages)
        {
            dec += b > dec;
        }
        return dec;
    }
};
