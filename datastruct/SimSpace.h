#pragma once
#include <iostream>
#include "xcept.h"


template<class T>
class SimSpace;

template<class T>
class SimNode
{
public:
//     friend SimSpace<T>;

// private:
    T data;
    int link;
};

template <class T>
class SimSpace
{
public:
    SimSpace(int MaxSpaceSize = 100);
    ~SimSpace() { delete[] node; }
    int Allocate();          //分配一个节点
    void Deallocate(int &i); //释放节点i

    SimNode<T> *node; //节点数组
private:
    int NumberOfNodes;
    // int first;
    int first1;
    int first2;
    
};

template <class T>
SimSpace<T>::SimSpace(int MaxSpaceSize)
{
    // 构造函数
    // 使用两个可用空间表
    NumberOfNodes = MaxSpaceSize;
    node = new SimNode<T>[NumberOfNodes];
    //初始化可用空间表
    //创建一个节点链表
    /* for(int i=0;i<NumberOfNodes-1;i++){
        node[i].link = i+1;
    }
    //链表的最后一个节点
    node[NumberOfNodes-1].link = -1;
    //链表的第一个节点
    first = 0; */
    // 初始化可用空间表
    first1 = 0;
    first2 = -1;
}

template <class T>
int SimSpace<T>::Allocate()
{
    //分配一个自由节点
    /* if(first == -1){
        throw NoMem();
    }
    int i = first;//分配第一个节点
    first = node[i].link;//first指向下一个自由节点
    return i; */

    if (first2 == -1)
    {
        if (first1 == NumberOfNodes)
        {
            throw NoMem();
        }
        return first1++;
    }
    //分配链表中的第一个节点
    int i = first2;
    first2 = node[i].link;
    return i;
}

template <class T>
void SimSpace<T>::Deallocate(int &i)
{
    //释放节点
    //使得i成为可用空间表的第一个节点
    /* node[i].link = first;
    first = i;
    i = -1; */

    node[i].link = first2;
    first2 = i;
    i = -1;
}
