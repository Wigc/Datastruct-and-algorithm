#pragma once
#include <iostream>
#include "xcept.h"


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
        Chain<T>& Insert(int k,const T& x);
        void Output(std::ostream& out)const;
        void Erase();
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

template<class T>
void Chain<T>::Output(std::ostream& out)const{
    //将链表元素送入输出流
    ChainNode<T> *current;
    for(current=first;current;current->link){
        out<<current->data<<" ";
    }
}

// 重载<<
template<class T>
std::ostream& operator<<(std::ostream& out,const Chain<T>& x){
    x.Output(out);
    return out;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k,T& x){
    //将第k个元素取至x,然后从链表中删除第k元素
    //如果不存在第k个元素，则引发异常OutOfBounds
    if(k<1||!first){
        throw OutOfBounds();//不存在第k个元素
    }
    //p最终指向第k个元素
    ChainNode<T> *p = first;
    //移动到第k个元素,并将其删除
    if(k==1){
        //若为第一个元素，则头节点指向下一个节点
        first = first->link;
    }else{
        //不是删除第一个元素

        //用q指向第k-1个元素
        ChainNode<T> *q = first;
        for(int index=1;index<k-1 && q;index++){
            q = q->link;
        }
        if(!q || !q->link){
            throw OutOfBounds();//不存在第k个元素
        }

        p = q->link;//存在第k个元素，p指向第k个元素
        q->link = p->link;//从链表删除改元素，将前一个元素节点指向p的下一个节点

    }

    x = p->data
    delete p;
    return *this;
    
}

template<class T>
Chain<T>& Chain<T>::Insert(int k,const T& x){
    //在第k个元素之后插入x
    //如果不存在第k个元素，则抛出异常outofbounds
    //如果没有足够的空间则抛出异常nomem
    if(k<0){
        throw OutOfBounds();
    }

    ChainNode<T> *p = first;
    //p指向第k个节点
    for(int index = 1;index<k&& p;index++){
        p = p->link;
    }

    if(k>0 && !p){
        //不存在第k个元素
        throw OutOfBounds()
    }

    //插入数据
    ChainNode<T> *newNode = new ChainNode<T>;
    newNode->data = x;
    if(k){
        //不是插入开头
        //在p之后插入
        newNode->link = p->link;//新节点的指针域指向下一个节点
        p->link = newNode;//p的指针指向新节点
    }else{
        //插入开头
        newNode->link = first;
        fisrt = y;
    }

    return *this;
}

template<class T>
void Chain<T>::Erase(){
    //删除所有链表节点
}