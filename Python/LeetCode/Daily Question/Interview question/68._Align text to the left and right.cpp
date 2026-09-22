#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        auto join = [&](int start, int end, const string &sep) -> string
        {
            string res;
            for (int i = start; i < end; i++)
            {
                if (i > start)
                    res += sep;
                res += words[i];
            }
            return res;
        };

        int n = words.size();
        vector<string> res;
        for (int i = 0; i < n;)
        {
            int start = i;
            int sum_len = words[i].size();
            for (i++; i < n && sum_len + words[i].size() + 1 <= maxWidth; i++)
                sum_len += words[i].size() + 1;

            int ex_space = maxWidth - sum_len;
            int gaps = i - start - 1;

            if (gaps == 0 || i == n)
            {
                string row = join(start, i, " ");
                row += string(ex_space, ' ');
                res.push_back(move(row));
                continue;
            }

            int avg = ex_space / gaps;
            int rem = ex_space % gaps;
            string space(avg + 1, ' ');
            string row = join(start, start + rem + 1, space + " ");
            row += space;
            row += join(start + rem + 1, i, space);
            res.push_back(move(row));
        }
        return res;
    }
};