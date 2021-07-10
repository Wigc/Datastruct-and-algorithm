#pragma once
#include<iostream>


//内存不足
class NoMem{
    public:
        NoMem(){}
};

class OutOfBounds{
    public:
        OutOfBounds(){}
};

//使new引发NoMem异常而不是xalloc异常
void my_new_handler(){
    throw NoMem();
}

std::new_handler Old_Handler_ = std::set_new_handler(my_new_handler);
