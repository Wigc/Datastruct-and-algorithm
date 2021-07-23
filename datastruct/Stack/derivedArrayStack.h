#pragma once

#include <iostream>

#include "Stack.h"
#include "../CustomException.h"
#include "../List/arrayList.h"


template <class T>
class derivedArrayStack : public Stack<T>,public arrayList<T>
{
public:
    derivedArrayStack(int initialCapacity=10):arrayList<T>(initialCapacity){}
    bool empty() const{
        return arrayList<T>::empty();
    }
   
    int size() const{
        return arrayList<T>::size();
    }

    T& top(){
        try{
            return this->get(arrayList<T>::size()-1);
        }catch(illegalIndex){
            throw stackEmpty();
        }
    }

    void pop(){
        try{
            this->erase(arrayList<T>::size()-1);
        }catch(illegalIndex){
            throw stackEmpty();
        }
    }

    void push(const T& theElement){
        arrayList<T>::insert(arrayList<T>::size(),theElement);
    }
};

