#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int canCompleteCircuit2(vector<int> &gas, vector<int> &cost)
    {

        int n = gas.size();
        for (int i = 0; i < n; i++)
        {
            int tank = 0;
            int j = i;
            int count = 0;
            while (count < n)
            {
                tank += gas[j % n] - cost[j % n];
                if (tank < 0)
                    break;
                count++;
                j++;
            }
            if (count == n)
                return i;
        }
        return -1;
    }

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int total = 0;
        int current = 0;
        int start = 0;
        int n = gas.size();
        for (int i = 0; i < n;i++)
        {
            total += gas[i] - cost[i];
            current += gas[i] - cost[i];
            if(current<0)
            {
                start = i + 1;
                current = 0;
            }
        }
        return total < 0 ? -1 : start;
    }
};