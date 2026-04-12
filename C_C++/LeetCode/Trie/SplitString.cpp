#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> partitionString(string s)
    {
        vector<string> res;
        unordered_set<string> st;
        string t;
        for (char c : s)
        {
            t += c;
            if (st.insert(t).second)
            {
                res.push_back(t);
                t.clear();
            }
        }
        return res;
    }

    vector<string> partitionString2(string s)
    {
        struct Node
        {
            Node *son[26];
        };
        vector<string> res;
        int left = 0;
        Node *root = new Node();
        Node *cur = root;
        for (int i = 0; i < s.size();i++)
        {
            int c = s[i] - 'a';
            if(cur->son[c]==nullptr)
            {
                cur->son[c] = new Node();
                res.push_back(s.substr(left, i - left + 1));
                left = i+1;
                cur = root;
            }
            else
            {
                cur = cur->son[c];
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    string str = "abbccccd";
    vector<string> res = s.partitionString2(str);
    for (string &s : res)
        cout << s << endl;
}