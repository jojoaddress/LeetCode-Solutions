#include <algorithm>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isVowel(string word)
    {
        string v = "aeiou";
        int n = word.size();
        bool jud1 = false, jud2 = false;
        for (int i = 0; i < v.size(); i++)
        {
            if (word[0] == v[i])
                jud1 = true;
            if (word[n-1] == v[i])
                jud2 = true;
        }
        return jud1&&jud2;
    }
    vector<int> vowelStrings(vector<string> &words, vector<vector<int>> &queries)
    {
        int n = words.size();
        vector<int> vowel(n,0);
        for (int i = 0; i < n;i++)
        {
            if(isVowel(words[i]))
                vowel[i] = 1;
        }
        vector<int> s(n + 1, 0);
        for (int i = 1; i <= n;i++)
            s[i] = s[i - 1] + vowel[i - 1];

        vector<int> res;
        for (int i = 0; i < queries.size();i++)
        {
            int temp = s[queries[i][1] + 1] - s[queries[i][0]];
            res.push_back(temp);
        }
        return res;
    }

};

int main()
{
    auto s = new Solution;
    vector<string> words = {"aba","bcb","ece","aa","e"};
    vector<vector<int>> queries = { {0, 2}, {1, 4}, {1, 1}};
    auto res = s->vowelStrings(words, queries);
    return 0;
}