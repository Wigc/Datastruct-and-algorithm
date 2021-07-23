# pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>

#include "LinearList.h"
#include "../changeLength1D.h"
#include "CustomException.h"


template <class T>
class vectorList : public LinearList<T>
{
public:
    vectorList(int initialCapacity = 10); //构造函数
    vectorList(const vectorList<T> &);
    ~vectorList() { delete element; } //析构函数

    bool empty() const { return element->empty(); }
    int size() const { return (int) element->size(); }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;

    int capacity() const
    {
        return (int) element->capacity();
    }

    //线性表的起始和结束位置的迭代器
    typedef typename vector<T>::iterator iterator;
    iterator begin() {
        return element->begin();
    }
    iterator end() {
        return element->end();
    }

protected:
    void checkIndex(int theIndex) const; //若索引theIndex无效，则抛出异常

    vector<T>* element;                          //存储线性表元素的向量
};

template <class T>
vectorList<T>::vectorList(int initialCapacity)
{
    //基于公式的线性表构造函数
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str())
    }

    this->element = new vector<T>;
    this->element->reserve(initialCapacity);
}

template <class T>
vectorList<T>::vectorList(const vectorList<T> &theList)
{
    //复制构造函数
    this->element = new vector<T>(*theList.element);
}

template <typename T>
void vectorList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= this->element->size())
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T &vectorList<T>::get(int theIndex) const
{
    //返回索引为theIndex的元素，若不存在，则抛出异常
    //如果不存在第k个元素则返回false，否则返回true
    this->checkIndex(theIndex);
    return (*this->element)[theIndex];
}

template <class T>
int vectorList<T>::indexOf(const T &theElement) const
{
    //返回元素theElement第一次出现时的索引，若不存在，返回-1
    //查找元素theElement
    int theIndex = (int)(std::find(this->element->begin(), this->element->end(), theElement) - this->element->begin());

    if (theIndex == this->element->size())
    {
        //没找到
        return -1;
    }
    else
    {
        return theIndex;
    }
}

template <class T>
void vectorList<T>::erase(int theIndex)
{
    //删除其索引为theIndex的元素
    //如果不存在，则抛出异常illegalIndex
    this->checkIndex(theIndex);

    
    this->element->erase(begin() + theIndex);
}

template <class T>
void vectorList<T>::insert(int theIndex, const T &theElement)
{
    //在索引theIndex后插入theElement
    if (theIndex < 0 || theIndex > this->element->size())
    {
        //无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->element->size();
        throw illegalIndex(s.str());
    }

    element->insert(this->element->begin() + theIndex,theElement);
}

template <class T>
void vectorList<T>::output(std::ostream &out) const
{
    //把表送入输出流
    std::copy(this->element, this->element + this->element->size(), std::ostream_iterator<T>(std::cout, " "))
}

//重载<<
template <class T>
std::ostream &operator<<(std::ostream &out, const vectorList<T> &x)
{
    x.output(out);
    return out;
}