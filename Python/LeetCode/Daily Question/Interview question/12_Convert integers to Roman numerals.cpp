#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    string intToRoman(int num)
    {
        const std::pair<int, std::string> valueSymbols[] = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
        string res;
        for (auto &[v, s] : valueSymbols)
        {
            if (num == 0)
                break;
            while (num >= v)
            {
                num -= v;
                res += s;
            }
        }
        return res;
    }
};