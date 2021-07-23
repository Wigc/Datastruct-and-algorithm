#pragma once

#include <iostream>
#include <sstream>

#include "Stack.h"
#include "../List/chainNode.h"
#include "../CustomException.h"

template<typename T>
class linkedStack : public Stack<T>{
public:
    linkedStack(int initialCapacity = 10);

    ~linkedStack();

    bool empty() const {
        return this->stackSize == 0;
    }

    int size() const {
        return this->stackSize;
    }

    T& top(){
        if(this->stackSize == 0){
            throw stackEmpty();
        }

        return this->stackTop->element;
    }
    void pop();

    void push(const T& theElement){
        this->stackTop = new ChainNode<T>(theElement,this->stackTop);
        this->stackSize++;
    }
private:
    ChainNode<T>* stackTop;
    int stackSize;
};

template<typename T>
linkedStack<T>::linkedStack(int initialCapacity){
    this->stackTop = NULL;
    this->stackSize = 0;
}

template<typename T>
linkedStack<T>::~linkedStack(){
    while (this->stackTop != NULL)
    {
        ChainNode<T>* nextNode = this->stackTop->next;
        delete this->stackTop;
        this->stackTop = nextNode;
    }
    
}

template<typename T>
void linkedStack<T>::pop(){
    if(this->stackSize == 0){
        throw stackEmpty();
    }

    ChainNode<T>* nextNode = this->stackTop->next;
    delete this->stackTop;
    this->stackTop = nextNode;
    this->stackSize--;
}