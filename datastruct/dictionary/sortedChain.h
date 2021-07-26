#pragma once

#include <iostream>

#include "dictionary.h"
#include "pairNode.h"

using std::pair;
using std::ostream;

template<typename K,typename E>
class sortedChain : public Dictionary<K,E>{
    public:
        sortedChain(){
            this->firstNode = NULL;
            this->dictionarySize = 0;
        }

        ~sortedChain();

        bool empty() const {
            return this->dictionarySize == 0;
        }

        int size() const {
            return this->dictionarySize;
        }

        std::pair<const K,E>* find(const K&) const;

        void erase(const K&);

        void insert(const std::pair<const K,E>&);

        void output(std::ostream& out) const ;
    protected:
        pairNode<K,E>* firstNode;//指向第一个节点的指针
        int dictionarySize;
};



template<typename K,typename E>
sortedChain<K,E>::~sortedChain(){
    while(this->firstNode != NULL){
        pairNode<K,E>* nextNode = this->firstNode->next;
        delete this->firstNode;
        this->firstNode = nextNode;
    }
}

template<typename K,typename E>
std::pair<const K,E>* sortedChain<K,E>::find(const K& theKey) const{
    pairNode<K,E>* currentNode = this->firstNode;

    while (currentNode != NULL && currentNode->element.first != theKey)
    {
        currentNode = currentNode->next;
    }

    if(currentNode != NULL && currentNode->element.first == theKey){
        return currentNode->element;
    }

    return NULL;
    
}

template<typename K,typename E>
void sortedChain<K,E>::erase(const K& theKey){
    pairNode<K,E>* p = this->firstNode;
    pairNode<K,E>* tp = NULL;//tp 跟踪p

    while(p != NULL && p->element.first != theKey){
        tp = p;
        p = p->next;
    }

    if(p != NULL && p->element.first == theKey){
        if(tp == NULL){
            this->firstNode = p->next;//p是首节点
        }else{
            tp->next = p->next;
        }

        delete p;
        this->dictionarySize--;
    }
}

template<typename K,typename E>
void insert(const std::pair<const K,E>&);

template<typename K,typename E>
void output(std::ostream& out) const ;