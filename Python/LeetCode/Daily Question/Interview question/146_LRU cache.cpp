#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        auto ump_iter = key_to_iter.find(key);
        if(ump_iter==key_to_iter.end())
            return -1;
        auto list_iter = ump_iter->second;
        cache_list.splice(cache_list.begin(), cache_list, list_iter);
        return list_iter->second;
    }
    
    void put(int key, int value) {
        auto ump_iter = key_to_iter.find(key);
        if(ump_iter!=key_to_iter.end())
        {
            auto list_iter = ump_iter->second;
            list_iter->second = value;
            cache_list.splice(cache_list.begin(),cache_list,list_iter);
            return;
        }
        cache_list.emplace_front(key, value);
        key_to_iter[key] = cache_list.begin();
        if(key_to_iter.size()>capacity)
        {
            key_to_iter.erase(cache_list.back().first);
            cache_list.pop_back();
        }
    }

private:
    int capacity;
    list<pair<int, int>> cache_list;
    unordered_map<int, list<pair<int, int>>::iterator> key_to_iter;
};
