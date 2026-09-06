#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm> // 需要 sort
using namespace std;

class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {
        string path;
        int n = characters.size();

        auto dfs = [&](this auto&& dfs, int start) -> void {
            if (path.size() == combinationLength) {
                res.push_back(path);
                return;
            }
            if (start == n || path.size() > combinationLength)
                return;

            // 不选当前字符
            dfs(start + 1);

            // 选当前字符
            path.push_back(characters[start]);
            dfs(start + 1);
            path.pop_back();
        };

        dfs(0);
        sort(res.begin(), res.end());
        index = 0; // 显式初始化，虽然类内已初始化
    }

    string next() {
        if (index < res.size()) {
            return res[index++];
        }
        return "";
    }

    bool hasNext() {
        return index < res.size();
    }

private:
    vector<string> res;
    int index = 0;
};