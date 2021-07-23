#pragma once

template<typename T>
class Stack{
    public:
        virtual ~Stack(){}
        virtual bool empty() const = 0;//返回true，当且仅当栈为空
        virtual int size() const = 0;//返回栈中元素个数
        virtual T& top() = 0;//返回栈顶元素的引用
        virtual void pop() = 0;//出栈
        virtual void push(const T& theElement) = 0;//入栈
};