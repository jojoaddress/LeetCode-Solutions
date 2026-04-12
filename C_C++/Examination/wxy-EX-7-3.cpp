#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int d, n;
    cout << "Please enter the endurance mileage of the car(7):" << endl;
    cin >> d;
    cout << "Please enter the number of petrol stations(4):" << endl;
    cin >> n;

    cout << "Please enter the distance between petrol stations(2 7 3 6):" << endl;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    int remain = d;       // 当前剩余油量
    int count = 0;        // 加油次数
    vector<int> stations; // 记录需要停靠加油的加油站编号
    for (int i = 0; i < n; ++i)
    {
        if (remain >= a[i])
        {
            remain -= a[i];
        }
        else
        {
            if (i == 0)
            {
                // 第一段距离就无法行驶，起点无法加油
                return 0;
            }
            // 即使加满油也无法通过这段距离
            if (a[i] > d)
            {
                cout << "No solutions!" << endl;
                return 0;
            }
            // 在加油站 i-1 加油
            stations.push_back(i - 1);
            count++;
            remain = d - a[i]; // 加满油后行驶这段距离
        }
    }

    cout << "The minimum number of refueling is " << count << endl;
    cout << "The serial number of petrol stations is:" << endl;
    if (count > 0)
    {
        for (int i = 0; i < stations.size(); ++i)
        {
            cout << stations[i] << " ";
        }
    }
    return 0;
}