#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isHappy(int n)
    {
        auto alg = [](int n)
        {
            int sum = 0;
            while (n)
            {
                int temp = n % 10;
                sum += temp * temp;
                n = n / 10;
            }
            return sum;
        };

        unordered_set<int> cnt;
        while(1)
        {
            if(n==1)
                return true;
            if(cnt.count(n)>0&&n!=1)
                return false;
            cnt.insert(n);
            n = alg(n);
        }
    }
};