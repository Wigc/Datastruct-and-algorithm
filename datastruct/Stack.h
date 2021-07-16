#pragma once

#include <iostream>
#include "LinearList.h"
#include "xcept.h"

template <class T>
class Stack 
{
private:
    int top;
    int MaxTop;
    T* stack;
public:
    Stack(int MaxStackSize=10);
    ~Stack(){
        delete [] stack;
    }
    bool IsEmpty()const{
        return this->top == -1;
    }
    bool IsFull()const{
        return this->top == this->MaxTop;
    }
    T Top()const;
    Stack<T>& Push(const T& x);
    Stack<T>& Pop(T& x);
};

template<typename T>
Stack<T>::Stack(int MaxStackSize){
    this->MaxTop = MaxStackSize;
    this->stack = new T[MaxStackSize];
    this->top = -1;
}

template<typename T>
T Stack<T>::Top()const{
    if(this->IsEmpty()){
        throw OutOfBounds();
    }else{
        return stack[this->top];
    }
}

template<typename T>
Stack<T>& Stack<T>::Push(const T& x){
    if(this->IsFull()){
        throw NoMem();
    }
    this->stack[++top] = x;
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::Pop(T& x){
    if(this->IsEmpty()){
        throw OutOfBounds();
    }else{
        x = stack[top--];
        return *this;
    }
}