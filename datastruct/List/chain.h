#pragma once
#include <iostream>
#include <sstream>
#include <iterator>

#include "LinearList.h"
#include "chainNode.h"
#include "../CustomException.h"

template <class T>
class Chain : public LinearList<T>
{
public:
    Chain(int initialCapacity = 10);
    Chain(const Chain<T> &theList);
    ~Chain();

    bool empty() const { return this->listSize == 0; }
    int size() const { return this->listSize; }
    T &get(int theIndex) const;                     //返回索引为theIndex的元素
    int indexOf(const T &theElement) const;         //返回元素theElement第一次出现的索引
    void erase(int theIndex);                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); //把theElement插入线性表中索引为theIndex的位置上
    void output(std::ostream &out) const;           //把线性表插入输出流out

    class iterator
    {
    public:
        //前向迭代器所需的typedef
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        iterator(ChainNode<T> *theNode = NULL)
        {
            this->node = theNode;
        }

        //解引用操作符
        T &operator*() const
        {
            return node->element;
        }

        T *operator->() const
        {
            return &(this->node->element);
        }

        //迭代器加法操作
        iterator &operator++()
        {
            //前加
            this->node = this->node->next;
            return *this;
        }
        iterator operator++(int)
        {
            //后加
            iterator old = *this;
            this->node = this->node->next;
            return old;
        }

        //相等检验
        bool operator!=(const iterator right) const
        {
            return this->node != right.node;
        }

        bool operator==(const iterator right) const
        {
            return this->node == right.node;
        }

    protected:
        ChainNode<T> *node;
    };

    iterator begin()
    {
        return iterator(this->firstNode);
    }

    iterator end()
    {
        return iterator(NULL);
    }

    void binSort(int range);

protected:
    void checkIndex(int theIndex) const; //若索引theIndex无效，则抛出异常
    ChainNode<T> *firstNode;             //指向第一个节点的指针
    int listSize;                        //线性表元素个数
};

template <typename T>
Chain<T>::Chain(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    firstNode = NULL;
    listSize = 0;
}

template <typename T>
Chain<T>::Chain(const Chain<T> &theList)
{
    this->listSize = theList.listSize;

    if (this->listSize == 0)
    {
        this->firstNode = NULL;
        return;
    }

    ChainNode<T> *sourceNode = theList.firstNode; //要复制的链表节点

    this->firstNode = new ChainNode<T>(sourceNode->element); //复制链表首元素
    sourceNode = sourceNode->next;
    ChainNode<T> *targetNode = this->firstNode; //当前链表*this的最后一个节点

    while (sourceNode != NULL)
    {
        //复制剩余元素
        targetNode->next = new ChainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; //链表结束
}

template <class T>
Chain<T>::~Chain()
{
    //链表的析构函数，用于删除链表的所有结点
    while (this->firstNode != NULL)
    {
        ChainNode<T> *nextNode = this->firstNode->next;
        delete this->firstNode;
        this->firstNode = nextNode;
    }
}

template <typename T>
void Chain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= this->listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T &Chain<T>::get(int theIndex) const
{
    //寻找链表中的第k个元素并将其传送至x，如果不存在，则返回false，否则返回true
    checkIndex(theIndex);
    ChainNode<T> *currentNode = this->firstNode;
    for (int i = 0; i < theIndex; i++)
    {
        currentNode = currentNode->next;
    }

    return currentNode->element;
}

template <class T>
int Chain<T>::indexOf(const T &theElement) const
{
    //寻找theElement,如果发现theElement，则返回theElement首次出现的索引，不存在返回-1
    ChainNode<T> *currentNode = this->firstNode;
    int index = 0; //当前节点索引
    while (currentNode != NULL && currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == NULL)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

template <class T>
void Chain<T>::output(std::ostream &out) const
{
    //将链表元素送入输出流
    ChainNode<T> *current;
    for (current = this->firstNode; current != NULL; current = current->next)
    {
        out << current->element << " ";
    }
}

// 重载<<
template <class T>
std::ostream &operator<<(std::ostream &out, const Chain<T> &x)
{
    x.output(out);
    return out;
}

template <class T>
void Chain<T>::erase(int theIndex)
{
    //删除索引为theIndex的元素
    //如果不存在则抛出异常
    checkIndex(theIndex);

    ChainNode<T> *deleteNode;
    if (theIndex == 0)
    {
        deleteNode = this->firstNode;
        this->firstNode = this->firstNode->next;
    }
    else
    {
        //用指针p指向要删除节点的前驱节点
        ChainNode<T> *p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
        {
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next; //从链表中删除deletenode指向的节点
    }

    this->listSize--;
    //释放空间
    delete deleteNode;
}

template <class T>
void Chain<T>::insert(int theIndex, const T &theElement)
{
    //在theindex的位置上插入元素theElement
    if (theIndex < 0 || theIndex > this->listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
    {
        this->firstNode = new ChainNode<T>(theElement, this->firstNode);
    }
    else
    {
        //寻找新元素的前驱
        ChainNode<T> *p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
        {
            p = p->next;
        }

        //在p之后插入
        p->next = new ChainNode<T>(theElement, p->next);
    }

    this->listSize++;
}

template <typename T>
void Chain<T>::binSort(int range)
{
    //对链表的节点进行排序
    //创建并初始化箱子
    ChainNode<T> **bottom, **top;
    bottom = new ChainNode<T> *[range + 1];
    top = new ChainNode<T> *[range + 1];

    for (; this->firstNode != NULL; this->firstNode = this->firstNode->next)
    {
        //把首节点firstnode加入到箱子中
        int theBin = this->firstNode->element; //元素类型转换为int
        if (bottom[theBin] == NULL)
        { //箱子为空
            bottom[theBin] = top[theBin] = this->firstNode;
        }
        else
        {
            //箱子不为空
            top[theBin]->next = this->firstNode;
            top[theBin] = this->firstNode;
        }
    }

    //把箱子中的节点收集到有序链表中
    ChainNode<T> *y = NULL;
    for (int theBin = 0; theBin < range; theBin++)
    {
        if (bottom[theBin] != NULL)
        {
            //箱子不空
            if (y == NULL)
            {
                //第一个非空箱子
                this->firstNode = bottom[theBin];
            }
            else
            {
                //不是第一个非空箱子
                y->next = bottom[theBin];
            }
            y = top[theBin];
        }
    }

    if (y != NULL)
    {
        y->next = NULL;
    }

    delete[] bottom;
    delete[] top;
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
