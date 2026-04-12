/*
* 2023.11.02
* 字母异位词分组
* 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
* 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
*
* 一开始想着用字母的ASCII码做哈希表的下标，unordered_map<int, vector<string>> hashmap;
* 这还是对哈希表不熟练导致，字母异位词最好的筛选自然是字母。 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> hashmap;
        for (int i = 0; i < strs.size(); i++)
        {
            auto str = strs[i];
            string key = str;
            sort(key.begin(), key.end());

            hashmap[key].push_back(str);
        }

        vector<vector<string>> resStr;
        auto it = hashmap.begin();
        for (; it != hashmap.end(); it++)
        {
            resStr.push_back(it->second);
        }
        return resStr;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<string> str = {"VCIPPV", "PCIPPV"};
    s->groupAnagrams(str);
    return 0;
}