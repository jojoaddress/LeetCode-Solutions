/*
用选择法或冒泡法对输入的 50 个字符（按 ASCII 码由小到大）进行排序。(15 分)
*/
#include <iostream>
using namespace std;

void Sort(int a[],int k)
{
    for (int i = 0; i < k; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < k; j++)
        {
            if (a[minIndex] > a[j])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
            swap(a[minIndex], a[i]);
    }
}

int main()
{
    char ch[5];
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        cin >> ch[i];
        a[i] = ch[i] - '0';
    }
    Sort(a,5);
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << static_cast<char>(a[i] + '0') << endl;
    }
    return 0;
}