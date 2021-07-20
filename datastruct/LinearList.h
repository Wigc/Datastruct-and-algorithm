#pragma once
#include <iostream>

template <typename T>
class LinearList
{
public:
    virtual ~LinearList();
    virtual bool empty() const = 0;                             //返回true，当且仅当线性表为空
    virtual int size() const = 0;                               //返回线性表元素个数
    virtual T &get(int theIndex) const = 0;                     //返回索引为theIndex的元素
    virtual int indexOf(const T &theElement) const = 0;         //返回元素theElement第一次出现的索引
    virtual void erase(int theIndex) = 0;                       //删除索引为theIndex的元素
    virtual void insert(int theIndex, const T &theElement) = 0; //把theElement插入线性表中索引为theIndex的位置上
    virtual void output(std::ostream &out) const = 0;           //把线性表插入输出流out
};
