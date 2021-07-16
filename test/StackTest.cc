#include <iostream>
#include <string>
#include <string.h>
#include "../datastruct/Stack.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

const int MaxLength = 100;

void PrintMatchedPairs(char *expr){
    //括号匹配
    Stack<int> s(MaxLength);
    int j,length = strlen(expr);
    //从表达式中搜索(和)
    for(int i=1;i<=length;i++){
        if(expr[i-1] == '('){
            s.Push(i);
        }else if(expr[i-1]==')'){
            try{
                s.Pop(j);
                cout<<j<<" "<<i<<endl;
            }catch (OutOfBounds){
                cout<<"No match for right parenthesis"<<" at " << i <<endl;
            }
        }
    }


    while (!s.IsEmpty())
    {
        s.Pop(j);
        cout<<"No match for left parnethesis at "<<j<<endl;
    }
    
}

/* void TowersOfHanoi(int n,int x,int y,int z){
    //把n个碟子从塔x移动到塔y，可借助于塔z
    if(n>0){
        TowersOfHanoi(n-1,x,z,y);
        cout<<"Move top disk from Tower " << x << " to top of Tower " <<y<<endl;
        TowersOfHanoi(n-1,z,y,x);
    }
} */

class Hanoi{
    friend void TowersOfHanoi(int n){
        Hanoi X;
        X.S[1] = new Stack<int>(n);
        X.S[2] = new Stack<int>(n);
        X.S[3] = new Stack<int>(n);

        for(int i=n;i>0;i--){
            // 把碟子 i 放到塔 1上
            X.S[1]->Push(i);
            //把塔 1上的n个碟子移动到塔 3上，借助于塔2 的帮助
            X.TowersOfHanoi(n,1,2,3);
        }
    }
    private:
     Stack<int> *S[4];
    public:
        void TowersOfHanoi(int n,int x,int y,int z);

};


int main(){
    char expr[MaxLength];
    cout << "Tpye an expressiion of length at most "<< MaxLength <<endl;
    cin.getline(expr,MaxLength);
    cout<<"The pairs of matching parnetheses in" <<endl;
    puts(expr);
    cout<<"are"<<endl;
    PrintMatchedPairs(expr);
    // TowersOfHanoi(3,1,2,3);
}