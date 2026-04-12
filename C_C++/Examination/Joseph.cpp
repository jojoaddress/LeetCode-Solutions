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
    int joseph(int n, int m, int k)
    {
        if (k == 1)
            return (m - 1) % n + 1;

        int p = (m - 1) % n + 1;
        int res = joseph(n - 1, m, k - 1);

        int result0 = (res + p - 1) % n ;
        return result0 + 1;
    }
};

int main()
{
    solution sol;
    int n, m, k;
    cin >> n >> m >> k;
    int result = sol.joseph(n, m, k);
    cout << result << endl;
    return 0;
}