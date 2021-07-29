/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-29 15:33:10
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-29 16:40:08
 */

#ifndef binaryTreeNode_
#define binaryTreeNode_

template<class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T>* leftChild;//左子树
    binaryTreeNode<T>* rightChild;//右子树

    binaryTreeNode(){
        this->leftChild = this->rightChild = NULL;
    }

    binaryTreeNode(const T& theElement): element(theElement) {
        this->leftChild = this->rightChild = NULL;
    }

    binaryTreeNode(const T& theElement,binaryTreeNode* theLeftChild,binaryTreeNode* theRigthChild): element(theElement){
        
        this->leftChild = theLeftChild;
        this->rightChild = theRigthChild;
    }
};





#endif
