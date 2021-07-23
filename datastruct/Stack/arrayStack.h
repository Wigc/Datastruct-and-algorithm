#pragma once

#include <iostream>
#include <sstream>

#include "Stack.h"
#include "../CustomException.h"
#include "../changeLength1D.h"

template<typename T>
class arrayStack : public Stack<T>{
public:
    arrayStack(int initialCapacity = 10);

    ~arrayStack(){
        delete [] this->stack;
    }

    bool empty() const{
        return this->stackTop == -1;
    }

    int size() const{
        return this->stackTop + 1;
    }

    T& top(){
        if(this->stackTop == -1){
            throw stackEmpty();
        }
        return this->stack[this->stackTop];
    }

    void pop(){
        if(this->stackTop == -1){
            throw stackEmpty();
        }
        this->stack[this->stackTop--].~T();
    }
    void push(const T& theElement);
private:
    int stackTop;
    int arrayLength;
    T* stack;
};

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity){
    if(initialCapacity < 1){
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity <<" Must be > 0";
        throw illegalParameterValue(s.str());
    }

    this->stackTop = -1;
    this->arrayLength = initialCapacity;
    this->stack = new T[this->arrayLength];
}

template<typename T>
void arrayStack<T>::push(const T& theElement){
    if(this->stackTop == this->arrayLength - 1){
        //空间已满，容量加倍
        changeLength1D(this->stack,this->arrayLength,this->arrayLength*2);
        this->arrayLength *= 2;
    }

    this->stack[++this->stackTop] = theElement;
}