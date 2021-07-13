#pragma once
#include<iostream>


/**
 * 内存不足
**/
class NoMem{
    public:
        NoMem(){}
};

/**
 * 超出范围
**/
class OutOfBounds{
    public:
        OutOfBounds(){}
};

/**
 * 初始化错误
**/
class BadInitializers {
    public:
       BadInitializers() {}
};

class SizeMismatch {
    public:
       SizeMismatch() {}
};

//使new引发NoMem异常而不是xalloc异常
void my_new_handler(){
    throw NoMem();
}

class MustBeZero {
    public:
       MustBeZero() {}
};
 
// use when zero was expected
class BadInput {
    public:
       BadInput() {}
};

std::new_handler Old_Handler_ = std::set_new_handler(my_new_handler);
