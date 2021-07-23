#pragma once

#include <iostream>

#include "../List/chain.h"
#include "Stack.h"
#include "../CustomException.h"

template<typename T>
class derivedLinkedStack : public Chain<T>,public Stack<T>{
    public:
        derivedLinkedStack(int initialCapacity = 10): Chain<T>(initialCapacity){}

        bool empty() const {
            return Chain<T>::empty();
        }

        int size() const {
            return Chain<T>::size();
        }

        T& top() {
            try{
                return this->get(0);
            }catch(illegalIndex){
                throw stackEmpty();
            }
        }

        void pop(){
            try{
                this->erase(0);
            }catch(illegalIndex){
                throw stackEmpty();
            }
        }

        void push(const T& theElement){
            this->insert(0,theElement);
        }
};