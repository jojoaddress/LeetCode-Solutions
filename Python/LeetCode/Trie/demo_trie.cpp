#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

// ---------- Node ----------
struct Node {
    unordered_map<char, Node*> son;
    bool end;
    Node() : end(false) {}
};

// ---------- Trie ----------
class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    // 插入单词
    void insert(const string& word) {
        Node* cur = root;
        for (char c : word) {
            if (cur->son.find(c) == cur->son.end()) {
                cur->son[c] = new Node();
            }
            cur = cur->son[c];
        }
        cur->end = true;
    }

    // 查找状态: 0-不存在, 1-存在为前缀, 2-存在为单词
    int find(const string& word) const {
        Node* cur = root;
        for (char c : word) {
            auto it = cur->son.find(c);
            if (it == cur->son.end()) {
                return 0;   // 无此路径
            }
            cur = it->second;
        }
        return cur->end ? 2 : 1;
    }

    bool search(const string& word) const {
        return find(word) == 2;
    }

    bool startsWith(const string& prefix) const {
        return find(prefix) != 0;
    }
};

// ---------- 测试 ----------
int main() {
    Trie trie;
    trie.insert("apple");
    cout << boolalpha;  // 输出 true/false
    cout << trie.search("apple") << endl;   // true
    cout << trie.search("app") << endl;     // false
    cout << trie.startsWith("app") << endl; // true
    trie.insert("app");
    cout << trie.search("app") << endl;     // true
    return 0;
}