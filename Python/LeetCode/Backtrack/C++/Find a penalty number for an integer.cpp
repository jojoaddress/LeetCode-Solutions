#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int punishmentNumber(int n)
    {
        int res = 0;
        for (int i = 1; i <= n; i++)
        {
            int num = i;
            string numPow = to_string(num * num);
            auto dfs = [&](auto &&self, int cur, int start) -> bool
            {
                if (start == numPow.size())
                {
                    return cur == num;
                }
                for (int i = start; i < numPow.size(); i++)
                {
                    auto temp = numPow.substr(start, i - start + 1);
                    int t = stoi(temp);
                    if (cur + t > num)
                        break;
                    if (self(self, cur+t, i + 1))
                        return true;
                }
                return false;
            };
            if (dfs(dfs, 0, 0))
            {
                res += num * num;
            }
        }
        return res;
    }
};