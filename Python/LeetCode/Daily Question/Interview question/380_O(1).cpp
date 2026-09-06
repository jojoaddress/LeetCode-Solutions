#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <random>
using namespace std;

class RandomizedSet
{
public:
    RandomizedSet()
    {
        srand((unsigned)time(NULL));
    }

    bool insert(int val)
    {
        if (valueToIndex.count(val))
        {
            return false;
        }
        valueToIndex[val] = nums.size();
        nums.push_back(val);
        return true;
    }

    bool remove(int val)
    {
        auto it = valueToIndex.find(val);
        if (it == valueToIndex.end())
        {
            return false;
        }
        int idx = it->second;
        int last = nums.back();

        nums[idx] = last;
        valueToIndex[last] = idx;

        nums.pop_back();
        valueToIndex.erase(val);
        return true;
    }

    int getRandom()
    {
        int randomIndex = rand()%nums.size();
        return nums[randomIndex];
    }

private:
    unordered_map<int, int> valueToIndex;
    vector<int> nums;
};