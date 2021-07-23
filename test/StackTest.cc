#include <iostream>
#include <string>
#include "../datastruct/Stack/arrayStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int MaxLength = 100;

void PrintMatchedPairs(string expr)
{
    //括号匹配
    arrayStack<int> s(MaxLength);
    int length = (int)expr.size();
    //从表达式中搜索(和)
    for (int i = 0; i < length; i++)
    {
        if (expr.at(i) == '(')
        {
            s.push(i);
        }
        else if (expr.at(i) == ')')
        {
            try
            {
                //从栈中删除匹配的左括号
                cout<< s.top() << " "<<i<<endl;
                s.pop();
            }
            catch (stackEmpty)
            {
                cout << "No match for right parenthesis"
                     << " at " << i << endl;
            }
        }
    }

    while (!s.empty())
    {
        
        cout << "No match for left parnethesis at " << s.top() << endl;
        s.pop();
    }
}



int main()
{
    string s;
    cout << "Tpye an expressiion of length at most " << MaxLength << endl;
    cin>>s;
    cout << "The pairs of matching parnetheses in" << endl;
    cout<<s << " ";
    cout << "are" << endl;
    PrintMatchedPairs(s);

}