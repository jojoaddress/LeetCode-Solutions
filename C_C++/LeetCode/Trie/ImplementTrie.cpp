#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    Node *son[26]{};
    bool end = false;
};

class Trie
{

private:
    Node *root = new Node();

    int find(string word)
    {
        Node *cur = root;
        for (char c : word)
        {
            c -= 'a';
            if (cur->son[c] == nullptr)
                return 0;
            cur = cur->son[c];
        }
        return cur->end ? 2 : 1;
    }
    void destroy(Node *node)
    {
        if (node == nullptr)
            return;
        for (Node *son : node->son)
            destroy(son);
        delete (node);
    }

public:
    ~Trie()
    {
        delete (root);
    }

    void insert(string word)
    {
        Node *cur = root;
        for (char c : word)
        {
            c -= 'a';
            if (cur->son[c] == nullptr)
            {
                cur->son[c] = new Node();
            }
            cur = cur->son[c];
        }
        cur->end = true;
    }

    bool search(string word)
    {
        return find(word) == 2;
    }

    bool startsWith(string prefix)
    {
        return find(prefix) != 0;
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // returns true
    cout << trie.search("app") << endl;     // returns false
    cout << trie.startsWith("app") << endl; // returns true
    trie.insert("app");
    cout << trie.search("app") << endl;     // returns true
}