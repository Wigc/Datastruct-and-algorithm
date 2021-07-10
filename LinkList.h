#pragma once
#include <iostream>


template<class T>
class ChainNode{
    friend Chain<T>;
    private:
        T data;
        ChainNode<T> *link;
};

template<class T>
class Chain{
    public:
        Chain(){first=0;}
        ~Chain();
        bool IsEmpty()const{return first==0;}
        int Length()const;
        bool Find(int k,T& x)const;
        int Search(const T& x)const;
        Chain<T>& Delete(int k,T& x);
        Chain<T>& Insert(int k,T& x);
        void Output(std::ostream& out)const;
    private:
        ChainNode<T> *first; //指向第一个节点的指针
};

template<class T>
Chain<T>::~Chain(){
    //链表的析构函数，用于删除链表的所有结点
    ChainNode<T> *next;//下一个节点
    while(first){
        next = first->link;
        delete fisrt;
        first = next;
    }
}

template<class T>
int Chain<T>::Length() const{
    //返回链表中元素总数
    ChainNode<T> *current = first;
    int len = 0;
    while(current){
        len++;
        current = current->link;
    }
    return len;
}

template<class T>
bool Chain<T>::Find(int k,T& x)const{
    //寻找链表中的第k个元素并将其传送至x，如果不存在，则返回false，否则返回true
    if(k<1){
        return false;
    }
    ChainNode<T> *current = first;
    int index = 1;
    while(index<k&&current){
        current = current->link;
        index++;
    }
    if(current){
        x = current->data;
        return true;
    }

    return false;

}

template<class T>
int Chain<T>::Search(const T& x)const{
    //寻找x,如果发现x，则返回x的地址，如果不存在，则返回0
    ChainNode<T> *current = first;
    int index = 1;
    while(current && current->data != x){
        current = current->link;
        index++;
    }
    if(current){
        return index;
    }
    return 0;
}