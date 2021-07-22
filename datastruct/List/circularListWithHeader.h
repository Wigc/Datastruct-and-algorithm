#pragma once

#include <iostream>
#include <sstream>

#include "../CustomException.h"
#include "chainNode.h"

template<typename T>
class CircularListWithHeader{
public:
    CircularListWithHeader();

    int size() const {
        return this->listSize;
    }

    int indexOf(const T& theElement) const;

    void insert(int theIndex,const T& theElement);
    void output(std::ostream& out)const;

protected:
    void checkIndex(int theIndex) const;
    ChainNode<T>* headNode; //指向头节点的指针
    int listSize;//链表元素个数
};

template<typename T>
CircularListWithHeader<T>::CircularListWithHeader(){
    this->headNode = new ChainNode<T>();
    this->headNode->next = this->headNode;
    this->listSize = 0;
}

template<typename T>
void CircularListWithHeader<T>::checkIndex(int theIndex) const {
    //确保索引在0到listSize-1之间
    if(theIndex < 0 || theIndex >= this->listSize){
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }
}

template<typename T>
int CircularListWithHeader<T>::indexOf(const T& theElement) const {

    //将theElement赋给headNode，确保一定能找到
    this->headNode->element = theElement;

    ChainNode<T>* currentNode = headNode->next;
    int index = 0;
    while(currentNode->element != theElement){
        currentNode = currentNode->next;
        index++;
    }

    //确保找到匹配
    if(currentNode == this->headNode){
        return -1;
    }else{
        return index;
    }
}

template<typename T>
void CircularListWithHeader<T>::insert(int theIndex,const T& theELement){
    if(theIndex < 0 || theIndex > this->listSize){
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    //找到新元素的前驱
    ChainNode<T>* p = headNode;
    for(int i=0;i<theIndex;i++){
        p = p->next;
    }

    p->next = new ChainNode<T>(theELement,p->next);
    this->listSize++;
}

template<typename T>
void CircularListWithHeader<T>::output(std::ostream& out) const {
    for(ChainNode<T>* currentNode = this->headNode->next;currentNode != headNode;currentNode = currentNode->next){
        out<< currentNode->element <<" ";
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out,const CircularListWithHeader<T>& list){
    list.output(out);
    return out;
}