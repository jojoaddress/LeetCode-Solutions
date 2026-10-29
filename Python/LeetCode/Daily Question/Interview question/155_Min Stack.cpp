#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class MinStack {
public:
    MinStack() {
     
    }
    
    void push(int value) {
        int curMin = stk.empty() ? value : min(value, stk.top().second);
        stk.push({value, curMin});
    }
    
    void pop() {
        stk.pop();
    }
    
    int top() {
        return stk.top().first;
    }
    
    int getMin() {
        return stk.top().second;
    }

private:
    stack<pair<int, int>> stk; 
};