#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring1(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;

        int n = s.size();
        int m = words.size();
        int len = words[0].size();
        int total_len = m * len;
        if (n < total_len) return result;

        unordered_map<string, int> ump;
        for (auto& w : words) ump[w]++;

        for (int i = total_len - 1; i < n; i++) {
            int left = i - total_len + 1;
            unordered_map<string, int> window;
            bool jud = true;

            for (int j = left; j <= i; j += len) {
                string temp = s.substr(j, len);
                auto it = ump.find(temp);
                if (it == ump.end()) {
                    jud = false;
                    break;
                }
                window[temp]++;
                if (window[temp] > it->second) {
                    jud = false;
                    break;
                }
            }

            if (jud) result.push_back(left);
        }
        return result;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.empty() || words.empty()) return res;

        int n = s.size();
        int m = words.size();
        int len = words[0].size();
        int totalLen = m * len;
        if (n < totalLen) return res;

        unordered_map<string, int> need;
        for (auto& w : words) need[w]++;

        for (int offset = 0; offset < len; offset++)
        {
            int left = offset;
            int right = offset;
            int matched = 0;
            unordered_map<string, int> window;
            while(right+len<=n)
            {
                string w = s.substr(right, len);
                right += len;
                if(need.count(w))
                {
                    window[w]++;
                    if(window[w]==need[w])
                        matched++;
                }

                while(right-left==totalLen)
                {
                    if(matched==(int)need.size())
                    {
                        res.push_back(left);
                    }
                    string lw = s.substr(left, len);
                    left += len;
                    if(need.count(lw))
                    {
                        if(window[lw]==need[lw])
                            matched--;
                        window[lw]--;
                    }
                }
            }
            
        }
        return res;
    }
};

int main()
{
    Solution s;
    string str = "barfoothefoobarman";
    vector<string> words = {"foo", "bar"};
    vector<int> result = s.findSubstring(str, words);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    return 0;
}