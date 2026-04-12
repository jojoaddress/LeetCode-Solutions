#include <iostream>
#include <string>
using namespace std;

string removeKDigits(const string &d, int k)
{
    if (k <= 0) return d;
    if (k >= d.length()) return "0";
    
    string result;  // 用字符串作为栈
    int removeCount = 0;
    
    for (char digit : d)
    {
        // 当结果字符串不为空且栈顶数字大于当前数字且还有删除名额时
        while (removeCount < k && !result.empty() && result.back() > digit)
        {
            result.pop_back();
            removeCount++;
        }
        result.push_back(digit);
    }
    
    // 如果还有要删除的数字，从末尾删除
    while (removeCount < k && !result.empty())
    {
        result.pop_back();
        removeCount++;
    }
    
    // 删除前导零
    int i = 0;
    while (i < result.length() && result[i] == '0')
    {
        i++;
    }
    
    // 如果所有数字都是0，返回0
    if (i == result.length())
    {
        return "0";
    }
    
    return result.substr(i);
}

int main()
{
    string d;
    int k;
    
    // 输入数字和k值
    cout << "Please enter an integer(3001527): "<<endl;
    cin >> d;
    
    cout << "Please enter the number of digits to be deleted(3): "<<endl;
    cin >> k;
    
    // 输入验证
    if (k < 0)
    {
        cout << "Error: k must be non-negative!" << endl;
        return 1;
    }
    
    // 计算并输出结果
    string result = removeKDigits(d, k);
    cout << "After deletion, The smallest integer is: " << result << endl;
    
    return 0;
}