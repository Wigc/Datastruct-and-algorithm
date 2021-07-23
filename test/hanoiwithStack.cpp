#include <iostream>
#include "../datastruct/Stack/arrayStack.h"

using namespace std;

//tower[1:3]表示三个塔
arrayStack<int> tower[4];

void moveAndShow(int n,int x,int y,int z){
    //将塔x顶部的n个碟子移到塔y，显示移动后的布局
    //用塔z作为中转站
    if(n>0){
        moveAndShow(n-1,x,z,y);
        int d = tower[x].top(); //把一个碟子
        tower[x].pop();//从塔x的顶部移到
        tower[y].push(d);//塔y的顶部
        //显示塔3的布局
        cout << "Move disk " << d << " from tower "
           << x << " to top of tower " << y << endl;
        moveAndShow(n-1,z,y,x);
    }
}

void towersOfHanoi(int n){
    for(int d = n;d>0;d--){
        tower[1].push(d);
    }
    moveAndShow(n,1,2,3);
}

int main(){
    cout << "Moves for a three disk problem are" << endl;
    towersOfHanoi(3);
}