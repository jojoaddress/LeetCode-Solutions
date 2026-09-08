#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1)
            return s;
        vector<string>  res(numRows);
        bool jud = false;
        int curRow = 0;
        for(char c:s)
        {
            res[curRow] += c;
            if(curRow==0||curRow==numRows-1)
                jud = !jud;
            curRow += jud ? 1 : -1;
        }
        string result="";
        for(auto r: res)
        {
            result += r;
        }
        return result;
    }
};