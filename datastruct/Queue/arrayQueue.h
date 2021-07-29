/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-19 16:14:18
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-29 16:49:31
 */
#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>

#include "../CustomException.h"
#include "queue.h"

template<typename T>
class arrayQueue : public Queue<T>{
    public:
        arrayQueue(int initialCapacity = 10);
        ~arrayQueue(){ delete [] this->element; }
        bool empty() const {
            return this->theFront == this->theBack;
        }
        int size() const {
            return (this->theBack - this->theFront + arrayLength) % this->arrayLength; 
        }
        T& front(){
            if(this->theFront == this->theBack){
                throw queueEmpty();
            }
            return this->element[(this->theFront + 1)% this->arrayLength] ;
        }
        T& back(){
            if(this->theBack == this->theFront){
                throw queueEmpty();
            }
            return this->element[this->theBack];
        }

        void pop(){
            if(this->theFront == this->theBack){
                throw queueEmpty();
            }

            this->theFront = (this->theFront +1)%this->arrayLength;
            this->element[this->theFront].~T();
        }
        void push(const T& theElement);

    private:
        int theFront;//1逆时针队首
        int theBack;//队尾
        int arrayLength;//队列容量
        T* element;//元素数组
};

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity){
    if(initialCapacity < 1){
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    this->arrayLength = initialCapacity;
    this->element = new T[this->arrayLength];
    this->theFront = 0;
    this->theBack = 0;

}

template<typename T>
void arrayQueue<T>::push(const T& theElement){
    
    //increase array length if neccary
    if( (this->theBack + 1) % this->arrayLength == this->theFront){
        //double array length
        T* newQueue = new T[2*this->arrayLength];

        int start = (this->theFront +1) % this->arrayLength;
        if(start < 2){
            //没有形成环
            std::copy(this->element + start,this->element + start + this->arrayLength -1 ,newQueue);
        }else{
            //形成环
            std::copy(this->element + start,this->element + this->arrayLength,newQueue);//复制到0开始的位置
            std::copy(this->element,this->element + this->theBack + 1,newQueue + this->arrayLength - start);
        }
        //设置新队列的首尾元素位置
        this->theFront = 2 * arrayLength -1;
        this->theBack = this->arrayLength - 2;
        this->arrayLength *= 2;
        delete [] this->element;
        this->element = newQueue;
    }

    //把元素插入队尾
    this->theBack = (theBack + 1)%this->arrayLength;
    this->element[this->theBack] = theElement;
}