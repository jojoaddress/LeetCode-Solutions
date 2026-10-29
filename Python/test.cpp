#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class LRUCache
{
public:
    LRUCache(int capacity) : capacity(capacity)
    {
    }

    int get(int key)
    {
        auto iter = ump_to_iter.find(key);
        if(iter==ump_to_iter.end())
            return -1;
        auto list_iter = iter->second;
        list_cache.splice(list_cache.begin(), list_cache, list_iter);
        return list_iter->second;
    }

    void put(int key, int value)
    {
        auto iter = ump_to_iter.find(key);
        if(iter!=ump_to_iter.end())
        {
            auto list_iter = iter->second;
            list_iter->second = value;
            list_cache.splice(list_cache.begin(), list_cache, list_iter);
            return;
        }
        list_cache.emplace_front(key, value);
        ump_to_iter[key] = list_cache.begin();
        if(list_cache.size()>capacity)
        {
            ump_to_iter.erase(list_cache.back().first);
            list_cache.pop_back();
        }
    }

private:
    int capacity;
    list<pair<int, int>> list_cache;
    unordered_map<int, list<pair<int, int>>::iterator> ump_to_iter;
};
