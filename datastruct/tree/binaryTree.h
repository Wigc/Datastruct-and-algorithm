/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-29 15:45:00
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-29 15:53:13
 */
#ifndef binaryTree_
#define binaryTree_


#include <functional>

template<class T>
class binaryTree{
    public:
        virtual ~binaryTree(){}
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual void preOrder(void (*)(T *)) = 0;//前序遍历
        virtual void inOrder(void (*)(T*)) = 0;//中序
        virtual void postOrder(void(*)(T*)) = 0;//后序
        virtual void levelOrder(void(*)(T*)) = 0;//层次
        //void(*)(T*)是一种函数类型，这种函数的返回值是void，它的参数类型是T*

};








#endif
