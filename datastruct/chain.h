#pragma once
#include <iostream>

#include "LinearList.h"
#include "chainNode.h"
#include "CustomException.h"



template <class T>
class Chain : public LinearList<T>
{
public:
    Chain(int initialCapacity = 10);
    Chain(const Chain<T>& theList);
    ~Chain();

    bool empty() const { return this->listSize == 0; }
    int size() const {return this->listSize;}
    T& get(int theIndex) const = 0;                     //返回索引为theIndex的元素
    int indexOf(const T &theElement) const ;         //返回元素theElement第一次出现的索引
    void erase(int theIndex) ;                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement) ; //把theElement插入线性表中索引为theIndex的位置上
    void output(std::ostream &out) const ;           //把线性表插入输出流out


protected:
    void checkIndex(int theIndex) const; //若索引theIndex无效，则抛出异常
    ChainNode<T>* firstNode; //指向第一个节点的指针
    int listSize;//线性表元素个数
};

template<typename T>
Chain<T>::Chain(int initialCapacity){
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str())
    }

    firstNode = NULL;
    listSize = 0;
}

template<typename T>
Chain<T>::Chain(const Chain<T>& theList){
    this->listSize = theList.listSize;

    if(this->listSize == 0){
        this->firstNode = NULL;
        return;
    }

    ChainNode<T>* sourceNode = theList.firstNode;//要复制的链表节点

    this->firstNode = new ChainNode<T>(sourceNode->element);//复制链表首元素
    sourceNode = sourceNode->next;
    ChainNode<T>* targetNode = this->firstNode;//当前链表*this的最后一个节点

    while(sourceNode != NULL){
        //复制剩余元素
        targetNode->next = new ChainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;//链表结束
}


template <class T>
Chain<T>::~Chain()
{
    //链表的析构函数，用于删除链表的所有结点
    ChainNode<T> *next; //下一个节点
    while (first)
    {
        next = first->link;
        delete fisrt;
        first = next;
    }
}

template <class T>
int Chain<T>::Length() const
{
    //返回链表中元素总数
    ChainNode<T> *current = first;
    int len = 0;
    while (current)
    {
        len++;
        current = current->link;
    }
    return len;
}

template <class T>
bool Chain<T>::Find(int k, T &x) const
{
    //寻找链表中的第k个元素并将其传送至x，如果不存在，则返回false，否则返回true
    if (k < 1)
    {
        return false;
    }
    ChainNode<T> *current = first;
    int index = 1;
    while (index < k && current)
    {
        current = current->link;
        index++;
    }
    if (current)
    {
        x = current->data;
        return true;
    }

    return false;
}

template <class T>
int Chain<T>::Search(const T &x) const
{
    //寻找x,如果发现x，则返回x的地址，如果不存在，则返回0
    ChainNode<T> *current = first;
    int index = 1;
    while (current && current->data != x)
    {
        current = current->link;
        index++;
    }
    if (current)
    {
        return index;
    }
    return 0;
}

template <class T>
void Chain<T>::Output(std::ostream &out) const
{
    //将链表元素送入输出流
    ChainNode<T> *current;
    for (current = first; current; current->link)
    {
        out << current->data << " ";
    }
}

// 重载<<
template <class T>
std::ostream &operator<<(std::ostream &out, const Chain<T> &x)
{
    x.Output(out);
    return out;
}

template <class T>
Chain<T> &Chain<T>::Delete(int k, T &x)
{
    //将第k个元素取至x,然后从链表中删除第k元素
    //如果不存在第k个元素，则引发异常OutOfBounds
    if (k < 1 || !first)
    {
        throw OutOfBounds(); //不存在第k个元素
    }
    //p最终指向第k个元素
    ChainNode<T> *p = first;
    //移动到第k个元素,并将其删除
    if (k == 1)
    {
        //若为第一个元素，则头节点指向下一个节点
        first = first->link;
    }
    else
    {
        //不是删除第一个元素

        //用q指向第k-1个元素
        ChainNode<T> *q = first;
        for (int index = 1; index < k - 1 && q; index++)
        {
            q = q->link;
        }
        if (!q || !q->link)
        {
            throw OutOfBounds(); //不存在第k个元素
        }

        p = q->link; //存在第k个元素，p指向第k个元素

        if (p == last)
        {
            last = q;
        }

        q->link = p->link; //从链表删除改元素，将前一个元素节点指向p的下一个节点
    }

    x = p->data delete p;
    return *this;
}

template <class T>
Chain<T> &Chain<T>::Insert(int k, const T &x)
{
    //在第k个元素之后插入x
    //如果不存在第k个元素，则抛出异常outofbounds
    //如果没有足够的空间则抛出异常nomem
    if (k < 0)
    {
        throw OutOfBounds();
    }

    ChainNode<T> *p = first;
    //p指向第k个节点
    for (int index = 1; index < k && p; index++)
    {
        p = p->link;
    }

    if (k > 0 && !p)
    {
        //不存在第k个元素
        throw OutOfBounds()
    }

    //插入数据
    ChainNode<T> *newNode = new ChainNode<T>;
    newNode->data = x;
    if (k)
    {
        //不是插入开头
        //在p之后插入
        newNode->link = p->link; //新节点的指针域指向下一个节点
        p->link = newNode;       //p的指针指向新节点
    }
    else
    {
        //插入开头
        newNode->link = first;
        fisrt = y;
    }

    if (!newNode->link)
    {
        last = newNode;
    }

    return *this;
}

template <class T>
void Chain<T>::Erase()
{
    //删除所有链表节点
    ChainNode<T> *next;
    while (first)
    {
        next = first->link;
        delete fisrt;
        first = next;
    }
}

template <class T>
Chain<T> &Chain<T>::Append(const T &x)
{
    //在链表尾部追加
    ChainNode<T> *newNode;
    newNode = new ChainNode<T>;
    newNode->data = x;

    if (first)
    { //链表不为空
        last->link = newNode;
        last = newNode;
    }
    else
    {
        //链表为空
        first = last = newNode;
    }

    return *this;
}

/**
 * @range: 
 * @(*value)(T& x): 函数指针
 */
template<class T>
void Chain<T>::BinSort(int range,int(*value)(T& x)){
    //按分数排序
    int b;//箱子索引号
    ChainNode<T> **bottom,**top;
    //箱子初始化
    bottom = new ChainNode<T>*[range+1];
    top = new ChainNode<T>*[range+1];
    for(b = 0;b<=range;b++){
        bottom[b] = 0;
    }
    //把节点分配到各个箱子中
    for(;first;first = first->link){
        //添加到箱子中
        b = value(first->data);
        if(bottom[b]){
            top[b]->link = first;
            top[b] = first;
        }else{
            bottom[b] = top[b] = first;
        }
    }

    //收集各箱子中的元素，产生一个排序表
    ChainNode<T>* y = 0;
    for(b=0;b<=range;b++){
        if(bottom[b]){
            //箱子非空
            if(y){
                //不是第一个非空箱子
                y->link = bottom[b];
            }else{
                //第一个非空箱子
                first = bottom[b];
            }
            y = top[b];
        }
    }
    if(y) y->link = 0;
    delete [] bottom;
    delete [] top;
}

// int main(){
//     int* x;
//     Chainiterator<int> c;
//     x = c.Initialize(x);
//     while(x){
//         std::cout<<*x<<" ";
//         x = c.Next();
//     }
//     std::cout<<std::endl;
// }