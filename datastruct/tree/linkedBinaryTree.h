/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-29 15:58:17
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-08-04 20:16:25
 */

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

#include <iostream>
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "../CustomException.h"
#include "../Queue/arrayQueue.h"

using std::cout;
using std::endl;

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
protected:
    binaryTreeNode<E>* root;//指向根节点指针
    int treeSize;//树的节点个数
    typedef void (*visitfun)(binaryTreeNode<E>*);//访问函数
    static void (*visit)(binaryTreeNode<E>*);
    static int count;//统计子树的节点
    static void preOrder(binaryTreeNode<E>* t);
    static void inOrder(binaryTreeNode<E>* t);
    static void postOrder(binaryTreeNode<E>* t);
    static void countNodes(binaryTreeNode<E>* t){
        visit = addToCount;
        count = 0;
        preOrder(t);
    }

    static void dispose(binaryTreeNode<E>* t){
        delete t;
    }

    static void output(binaryTreeNode<E>* t){
        cout<<t->element<<" ";
    }

    static void addToCount(binaryTreeNode<E>* t){
        count++;
    }

    static int height(binaryTreeNode<E>* t);
public:
    linkedBinaryTree(){
        this->root = NULL;
        this->treeSize = 0;
    }

    ~linkedBinaryTree(){
        erase();
    }
    
    //ADT
    bool empty() const {
        return this->treeSize == 0;
    }

    int size() const {
        return this->treeSize;
    }

    E* rootElement() const ;
    void makeTree(const E& element, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
    linkedBinaryTree<E>& removeLeftSubtree();
    linkedBinaryTree<E>& removeRightSubtree();
    void preOrder(void(*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        preOrder(this->root);
    }

    void inOrder(void(*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        inOrder(this->root);
    }

    void postOrder(void(*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        postOrder(this->root);
    }

    void levelOrder(void(*)(binaryTreeNode<E>* ));

    void preOrderOutput(){
        preOrder(output);
        std::cout<<std::endl;
    }

    void inOrderOutput(){
        inOrder(output);
        std::cout<<std::endl;
    }

    void postOrderOutput(){
        postOrder(output);
        cout<<endl;
    }

    void levelOrderOutput(){
        levelOrder(output);
        cout<<endl;
    }

    void erase(){
        postOrder(dispose);
        this->root = NULL;
        this->treeSize = 0;
    }

    int height() const{
        return height(this->root);
    }
};

// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
template<class E>
typename linkedBinaryTree<E>::visitfun  linkedBinaryTree<E>::visit = nullptr; 
/* void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
void (*linkedBinaryTree<pair<int,int> >::visit)(binaryTreeNode<pair<int,int> >*);
void (*linkedBinaryTree<pair<const int,char> >::visit)(binaryTreeNode<pair<const int,char> >*);
void (*linkedBinaryTree<pair<const int,int> >::visit)(binaryTreeNode<pair<const int,int> >*); */

template<class E>
E* linkedBinaryTree<E>::rootElement() const{
    if(this->treeSize == 0){
        return NULL;
    }else{
        return &this->root->element;
    }
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,linkedBinaryTree<E>& left,linkedBinaryTree<E>& right){
    //create bombine tree
    this->root = new binaryTreeNode<E>(element,left.root,right.root);
    this->treeSize = left.treeSize + right.treeSize + 1;

    //deny acces from tree left and right
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree(){
    if(this->treeSize == 0){
        throw emptyTree();
    }

    //detach left subtree and save in leftSubtree
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = this->root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    this->root->leftChild = NULL;
    this->treeSize -= leftSubtree.treeSize;

    return leftSubtree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree(){
    if(this->treeSize == 0){
        throw emptyTree();
    }

    // detach right subtree and save in rightSubtree
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = this->root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    this->root->rightChild = NULL;
    this->treeSize -= rightSubtree.treeSize;

    return rightSubtree;
}

/**
 * @description: 先序遍历
 * @param {binaryTreeNode<E>*} t
 * @return {*}
 * @author: 
 */
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t){
    if(NULL != t){
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

//中序遍历
template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t){
    if(NULL != t){
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

//后序遍历
template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t){
    if(NULL != t){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

//层序遍历
template<class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>* )){
    arrayQueue<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = this->root;
    while(NULL != t){
        theVisit(t);

        if(NULL != t->leftChild){
            q.push(t->leftChild);
        }

        if(NULL != t->rightChild){
            q.push(t->rightChild);
        }

        try
        {
            t = q.front();
        }
        catch(queueEmpty)
        {
            return;
        }

        q.pop();
        
    }

}

//返回节点的高度
template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t){
    if(NULL == t){
        return 0;
    }

    int hl = height(t->leftChild);//左高度
    int hr = height(t->rightChild);//右高度
    if(hl > hr){
        return ++hl;
    }else{
        return ++hr;
    }
}

#endif
