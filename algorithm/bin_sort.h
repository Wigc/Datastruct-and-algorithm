#pragma once

#include <iostream>
#include "../datastruct/LinkList.h"

class Node
{
    friend std::ostream &operator<<(std::ostream &out, const Node &x);

public:
    int operator!=(Node x) const
    {
        return (score != x.score || name[0] != x.name[0]);
    }

    operator int() const{
        return score;
    }

public:
    int score;
    char *name;
};

std::ostream& operator<<(std::ostream& out,const Node& x){\
    out<<x.score<<" "<<x.name[0]<<" ";
    return out;
}

void BinSort(Chain<Node>& L,int range){
    //按分数排序
    int len = L.Length();
    Node x;
    Chain<Node> *bin;
    bin = new Chain<Node>[range+1];
    //分配到每个箱子中
    for(int i = 1;i<=len;i++){
        L.Delete(1,x);
        bin[x.score].Insert(0,x);
    }
    //从箱子中收集个元素
    for(int j=range;j>=0;j--){
        while(!bin[j].IsEmpty()){
            bin[j].Delete(1,x);
            L.Insert(0,x);
        }
    }
    delete [] bin;
}