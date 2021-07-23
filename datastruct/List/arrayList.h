#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "LinearList.h"
#include "../changeLength1D.h"
#include "../CustomException.h"

template <class T>
class arrayList : public LinearList<T>
{
public:
    arrayList(int initialCapacity = 10); //构造函数
    arrayList(const arrayList<T>& theList);
    ~arrayList() { delete[] element; } //析构函数
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;

    int capacity() const
    {
        return arrayLength;
    }

    class iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        //constructor
        iterator(T *thePosition = 0)
        {
            this->position = thePosition;
        }

        //解引用操作符
        T &operator*() const
        {
            return *position;
        }

        T *operator->() const
        {
            return &*position;
        }

        //迭代器的值增加
        //前加
        iterator &operator++()
        {
            ++position;
            return *this;
        }
        //后加
        iterator operator++(int)
        {
            iterator old = *this;
            ++position;
            return old;
        }

        //迭代器的值减少
        //前减
        iterator &operator--()
        {
            --position;
            return *this;
        }
        //后减
        iterator operator--(int)
        {
            iterator old = *this;
            --position;
            return old;
        }

        //测试是否相等
        bool operator!=(const iterator right) const
        {
            return position != right.position;
        }

        bool operator==(const iterator right) const
        {
            return position == right.position;
        }

    protected:
        T *position; //指向表元素的指针
    };

protected:
    void checkIndex(int theIndex) const; //若索引theIndex无效，则抛出异常
    int listSize;                        //线性表元素个数
    int arrayLength;                     //一维数组容量
    T *element;                          //一维动态数组
};

template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    //基于公式的线性表构造函数
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    this->arrayLength = initialCapacity;
    this->element = new T[arrayLength];
    this->listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    //复制构造函数
    this->arrayLength = theList.arrayLength;
    this->listSize = theList.listSize;
    this->element = new T[this->arrayLength];
    std::copy(theList.element, theList.element + listSize, this->element);
}

template <typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T &arrayList<T>::get(int theIndex) const
{
    //返回索引为theIndex的元素，若不存在，则抛出异常
    //如果不存在第k个元素则返回false，否则返回true
    this->checkIndex(theIndex);
    return this->element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    //返回元素theElement第一次出现时的索引，若不存在，返回-1
    //查找元素theElement
    int theIndex = (int)(std::find(this->element, this->element + this->listSize, theElement) - this->element);

    if (theIndex == this->listSize)
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
void arrayList<T>::erase(int theIndex)
{
    //删除其索引为theIndex的元素
    //如果不存在，则抛出异常illegalIndex
    this->checkIndex(theIndex);

    //有效索引，移动其索引大于theIndex的元素
    std::copy(this->element + theIndex + 1, this->element + this->listSize, this->element + theIndex);

    this->element[--listSize].~T(); //调用析构

    if (this->listSize < this->arrayLength / 4)
    {
        changeLength1D(this->element, this->arrayLength, 10 > this->arrayLength / 2 ? 10 : this->arrayLength / 2);
    }
}

template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    //在索引theIndex后插入theElement
    if (theIndex < 0 || theIndex > listSize)
    {
        //无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    //有效索引，确定数组是否已满
    if (this->listSize == this->arrayLength)
    {
        changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }

    //把元素向右移动
    std::copy_backward(this->element + theIndex, this->element + this->listSize,
                       this->element + this->listSize + 1);

    this->element[theIndex] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream &out) const
{
    //把表送入输出流
    std::copy(this->element, this->element + this->listSize, std::ostream_iterator<T>(std::cout, " "));
}

//重载<<
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}