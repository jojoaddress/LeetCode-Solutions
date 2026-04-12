/*
 * 实现代码来源：https://blog.csdn.net/llg070401046/article/details/73323934
 */
#include <iostream>    
#include <map>    
#include <string>    
   
using namespace std;    
  
class Context  
{  
private:  
    map<string, int> valueMap;  
  
public:  
    void addValue(string key,int value)  
    {         
        valueMap.insert(std::pair<string,int>(key,value));  
    }  
  
    int getValue(string key)  
    {  
        return valueMap[key];  
    }  
};  
  
class AbstractExpression  
{  
public :  
     virtual int interpreter(Context context) = 0;  
};  
  
class AddNonterminalExpression : public AbstractExpression  
{  
private :  
    AbstractExpression *left;  
    AbstractExpression *right;  
  
public:  
    AddNonterminalExpression(AbstractExpression *left, AbstractExpression *right)  
    {  
        this->left = left;  
        this->right = right;  
    }  
  
    int interpreter(Context context)  
    {  
        return this->left->interpreter(context) + this->right->interpreter(context);  
    }  
  
};  
  
class SubtractNonterminalExpression : public AbstractExpression  
{  
private :  
    AbstractExpression *left;  
    AbstractExpression *right;  
  
public:  
    SubtractNonterminalExpression(AbstractExpression *left, AbstractExpression *right)  
    {  
        this->left = left;  
        this->right = right;  
    }  
  
    int interpreter(Context context)  
    {  
        return this->left->interpreter(context) - this->right->interpreter(context);  
    }  
  
};  
  
class TerminalExpression : public AbstractExpression  
{  
private :  
    int i;  
  
public :  
    TerminalExpression(int i)  
    {  
        this->i = i;  
    }  
  
    int interpreter(Context context)  
    {  
        return this->i;  
    }  
};  
  
int main(){    
    //a-b+c  
    Context context;  
    context.addValue("a", 7);  
    context.addValue("b", 8);  
    context.addValue("c", 2);  
  
    SubtractNonterminalExpression *subtractValue = new SubtractNonterminalExpression(new TerminalExpression(  
        context.getValue("a")), new TerminalExpression(context.getValue("b")));  
  
    AddNonterminalExpression *addValue = new AddNonterminalExpression(subtractValue, new TerminalExpression(  
        context.getValue("c")));  
  
    cout<< addValue->interpreter(context);  
  
    return 0;    
} 
