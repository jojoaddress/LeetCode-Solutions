#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class BrowserHistory
{
public:
    BrowserHistory(string homepage)
    {
        history.push_back(homepage);
        current++;
    }

    void visit(string url)
    {
        current++;
        history.erase(history.begin() + current, history.end());
        history.push_back(url);
        
    }

    string back(int steps)
    {
        current-=steps;
        current = current > 0 ? current : 0;
        return history[current];
    }

    string forward(int steps)
    {
        current+=steps;
        current = current < history.size() ? current : history.size() - 1;
        return history[current];
    }

private:
    vector<string> history;
    int current = -1;
};

int main()
{
    BrowserHistory *browserHistory = new BrowserHistory("leetcode.com");
    browserHistory->visit("google.com");
    browserHistory->visit("facebook.com");
    browserHistory->visit("youtube.com");
    cout << browserHistory->back(1) << endl;       // facebook.com
    cout << browserHistory->back(1) << endl;       // google.com
    cout << browserHistory->forward(1) << endl;    // facebook.com
    browserHistory->visit("linkedin.com");
    cout << browserHistory->forward(2) << endl;    // linkedin.com
    cout << browserHistory->back(2) << endl;       // google.com
    cout << browserHistory->back(7) << endl;       // leetcode.com
    return 0;
}