#pragma once

#include <iostream>
#include <algorithm>

#include "ChainNode.h"
#include "CustomException.h"
#include "queue.h"

template<typename T>
class linkedQueue : public Queue<T>{
    public:
        linkedQueue(int initialCapacity = 10){
            this->queueFront = NULL;
            this->queueSize = 0;
        }

        ~linkedQueue();

        bool empty() const {
            return this->queueSize = 0;
        }

        int size() const {
            return this->queueSize; 
        }

        T& front(){
            if(this->queueSize == 0){
                throw queueEmpty();
            }
            return this->queueFront->element;
        }

        T& back(){
            if(this->queueSize == 0){
                throw queueEmpty();
            }
            return this->queueBack->element;
        }

        void pop();
        void push(const T& theElement);

    private:
        ChainNode<T>* queueFront;//队首指针
        ChainNode<T>* queueBack;//队尾指针
        int queueSize;//队列元素数量
};

template<typename T>
linkedQueue<T>::~linkedQueue(){
    while(this->queueFront != NULL){
        ChainNode<T>* nextNode = this->queueFront->next;
        delete this->queueFront;
        this->queueFront = nextNode;
    }
}

template<typename T>
void linkedQueue<T>::pop(){
    if(this->queueFront == NULL){
        throw queueEmpty();
    }

    ChainNode<T>* nextNode = this->queueFront->next;
    delete this->queueFront;
    this->queueFront = nextNode;
    this->queueSize--;
}

template<typename T>
void linkedQueue<T>::push(const T& theElement){
    ChainNode<T>* newNode = new ChainNode<T>(theElement,NULL);

    if(this->queueSize == 0){
        this->queueFront = newNode;
    }else{
        this->queueBack->next = newNode;
    }
    this->queueBack = newNode;//更新队尾指向最后一个元素
    this->queueSize++;
}