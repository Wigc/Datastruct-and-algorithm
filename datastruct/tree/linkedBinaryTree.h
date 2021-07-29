/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-29 15:58:17
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-29 16:03:20
 */

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

#include <iostream>
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "../CustomException.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
private:
    binaryTreeNode<E>* root;//指向根节点指针
    int treeSize;//树的节点个数
    static void(*visit)(binaryTreeNode<E>* );//访问函数
public:
    linkedBinaryTree(/* args */);
    ~linkedBinaryTree();
};

template<class E>
linkedBinaryTree<E>::linkedBinaryTree(/* args */)
{
}

template<class E>
linkedBinaryTree<E>::~linkedBinaryTree()
{
}






#endif
