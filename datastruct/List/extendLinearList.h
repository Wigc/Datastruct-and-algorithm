#pragma once

#include <iostream>
#include "LinearList.h"

template<typename T>
class extendLinearList: LinearList<T>{
    public:
        virtual ~extendLinearList(){}
        virtual void clear() = 0;//清表
        virtual void push_back(const T& theElement) = 0;//在标为插入
};