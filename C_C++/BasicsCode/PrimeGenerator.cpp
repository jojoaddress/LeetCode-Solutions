/**
 * Prime generator 质数生成器
 */
#include <iostream>
#include <math.h>
using namespace std;
void PrimeGenerator(int n)
{
    if (n <= 1)
        return;
    for (int i = 2; i <= n; i++)
    {
        int temp = sqrt(i);
        int j = 2;
        while (j <= temp)
        {
            if (i % j == 0)
                break;
            j++;
        }
        if (j >= temp + 1)
            cout << i << " ";
    }
}

int main()
{
    int n = 0;
    cin >> n;
    PrimeGenerator(n);
    return 0;
}