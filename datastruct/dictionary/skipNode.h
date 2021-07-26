#pragma once

#include <iostream>

using std::pair;

template<typename K,typename E>
struct skipNode
{
    typedef pair<const K,E> pairType;

    pairType element;
    skipNode<K,E> **next;//指针数组

    skipNode(const pairType& thePair,int size):element(thePair){
        this->next = new skipNode<K,E>* [size];
    }
};
