#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "extendLinearList.h"
#include "chain.h"

template<typename T>
class extendChain: public extendLinearList<T>, public Chain<T>{
    public:
        extendChain(int initialCapacity = 10): Chain<T>(initialCapacity){}

        extendChain(const extendChain<T>& theList):Chain<T>(theList){}

        //ADT 
        bool empty() const{
            return this->listSize==0;
        }

        int size() const{
            return this->listSize;
        }

        T& get(int theIndex) const{
            return Chain<T>::get(theIndex);
        }

        int indexOf(const T& theElement) const{
            return Chain<T>::indexOf(theElement);
        }

        void erase(int theIndex);
        void insert(int theIndex,const T& theElement);
        void clear(){
            //删除所有元素
            while (this->firstNode != NULL)
            {
                ChainNode<T>* nextNode = this->firstNode->next;
                delete this->firstNode;
                this->firstNode = nextNode;
            }
            this->listSize = 0;
        }

        void push_back(const T& theElement);
        void output(std::ostream& out) const {
            Chain<T>::output(out);
        }

        //aditiional
        void zero(){
            this->firstNode = NULL;
            this->listSize = 0;
        }
    protected:
        ChainNode<T>* lastNode ;//指向尾节点的指针
};


template<typename T>
void extendChain<T>::erase(int theIndex){
    this->checkIndex(theIndex);

    ChainNode<T>* deleteNode ;
    if(theIndex == 0){
        deleteNode = this->firstNode;
        this->firstNode = this->firstNode->next;
    }else{
        ChainNode<T>* p = this->firstNode;
        for(int i=0;i<theIndex-1;i++){
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next;
        if(deleteNode == this->lastNode){
            this->lastNode = p;
        }
    }

    this->listSize--;
    delete deleteNode;
}

template<typename T>
void extendChain<T>::insert(int theIndex,const T& theElement){
    if(theIndex < 0 || theIndex > this->listSize){
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    if(theIndex == 0){
    
        this->firstNode = new ChainNode<T>(theElement,this->firstNode);
        if(this->listSize == 0){
            this->lastNode = this->firstNode;
        }
    }else{
        ChainNode<T>* p = this->firstNode;
        for(int i = 0;i<theIndex - 1;i++){
            p = p->next;
        }

        p->next = new ChainNode<T>(theElement,p->next);
        if(this->listSize = theIndex){
            this->lastNode = p->next;
        }
    }
    this->listSize++;
}


template<typename T>
void extendChain<T>::push_back(const T& theElement){
    ChainNode<T>* newNode = new ChainNode<T>(theElement,NULL);
    if(this->firstNode == NULL){
        this->firstNode = newNode;
        this->lastNode = newNode;
    }else{
        lastNode->next = newNode;
        lastNode = newNode;
    }
    this->listSize++;
}