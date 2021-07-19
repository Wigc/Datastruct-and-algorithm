#pragma once

#include<iostream>

template<typename T>
class Queue{
    public:
        virtual ~Queue(){}
        virtual bool empty() const = 0;// 返回true,当且仅当队列为空
        virtual int size() const = 0;//返回队列中元素个数
        virtual T& front() = 0;//返回对头元素引用
        virtual T& back() = 0;//返回队尾元素的引用
        virtual void pop() = 0;//删除首元素
        virtual void push(const T& theElement) = 0;//把元素theElement加入队尾
};