#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "dictionary.h"
#include "../CustomException.h"
#include "skipNode.h"

using std::pair;
using std::ostream;


template<typename K,typename E>
class skipList : public Dictionary<K,E>{
    public:
        skipList(K largeKey,int maxPairs = 1000,float prob = 0.5);
        ~skipList();

        bool empty() const{
            return this->dSize == 0;
        }

        int size() const {
            return this->dSize;
        }

        pair<const K,E>* find(const K& theKey) const;

        void erase(const T& theKey);
        void insert(const pair<const K,E>& thePair);
        void output(ostream& out);

    protected:
        float cutOff; //用来确定层数
        int level() const; //生成一个随机层数
        int levels;//当前最大的非空链表
        int dSize;//字典对数个数
        int maxLevel;//允许的最大链表层数
        K tailKey;//最大关键字
        skipNode<K,E>* search(const K& theKey) const;//搜索保存的最近的节点

        skipNode<K,E>* headNode;//头节点指针
        skipNode<K,E>* tailNode;//尾节点指针
        skipNode<K,E>** last;//last[i] 表示第i层的最后节点
};

template<typename K,typename E>
skipList<K,E>::skipList(K largeKey,int maxPairs = 1000,float prob = 0.5){
    //构造函数，关键字小于largeKey且数对个数size最多为maxPairs。0<prob<1
    this->cutOff = prob * RAND_MAX;
    this->maxLevel = (int) ceil(logf((float) maxPairs) / logf(1/prob)) - 1;
    this->levels = 0;//初始化级数
    this->dSize = 0;
    this->tailKey = largeKey;

    //生成头节点、尾节点和数组last
    pair<K,E> tailPair;
    tailPair.first = this->tailKey;
    this->headNode = new skipNode<K,E>(tailPair,this->maxLevel+1);
    this->tailNode = new skipNode<K,E>(tailPair,0);
    this->last = new skipNode<K,E> *[this->maxLevel + 1];

    //链表为空时，任意级链表中的头节点都指向尾节点
    for(int i = 0;i<=this->maxLevel;i++){
        this->headNode->next[i] = this->tailNode;
    }
    
}

template<typename K,typename E>
skipList<K,E>::~skipList(){
    skipNode<K,E>* nextNode;

    while(this->headNode != this->tailNode){
        nextNode = this->headNode->next[0];
        delete this->headNode;
        this->headNode = nextNode;
    }
}

template<typename K,typename E>
pair<const K,E>* skipList<K,E>::find(const K& theKey) const{
    if(theKey >= tailKey){
        return NULL;
    }

    //位置beforeNode是关键字为theKey的节点之前最右边的位置
    skipNode<K,E>* beforeNode = this->headNode;
    for(int i = this->levels;i>=0;i--){
        //从上级列表到下级列表
        //跟踪i级链表指针
        while (beforeNode->next[i]->element.first < theKey)
        {
            beforeNode = beforeNode->next[i];
        }   
    }

    //检查下一个节点关键字是否是theKey
    if(beforeNode->next[0]->element.first == theKey){
        return &beforeNode->next[0]->element;
    }

    return NULL;//无匹配
}

template<class K,class E>
int skipList<K,E>::level() const{
    //返回一个表示链表的随机数，这个数不大于maxlevel
    int lev = 0;
    while(rand() <= this->cutOff){
        lev++;
    }

    return (lev <= maxLevel)? lev:maxLevel;
}

template<class K,class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const{
    //搜索关键字theKey，把每一级链表中要查看的最后一个节点存储在数组last中
    //返回包含关键theKey的节点

    //位置beforeNode是关键为theKey的节点之前最右边的位置
    skipNode<K,E>* beforeNode = this->headNode;
    for(int i=levels;i>=0;i--){
        while(beforeNode->next[i]->element.first <theKey){
            beforeNode = beforeNode->next;
        }
        last[i] = beforeNode;   //最后一级链表i的节点
    }

    return beforeNode->next[0];
}

template<typename K,typename E>
void skipList<K,E>::erase(const T& theKey){
    //删除关键字等于theKey的数对
    if(theKey >= this->tailKey){ //关键字太大
        return;
    }

    //查看是否有匹配的数对
    skipNode<K,E>* theNode = search(theKey);
    if(theNode->element.first != theKey){
        //不存在
        return;
    }

    //从跳表中删除
    for(int i=0;i<=this->levels && this->last[i]->next[i] == theNode;i++){
        this->last[i]->next[i] = theNode->next[i];
    }

    //更新链表级
    while(this->levels > 0 && this->headNode->next[this->levels] == this->tailNode){
        this->levels--;
    }

    delete theNode;
    this->dSize--;
}

template<typename K,typename E>
void skipList<K,E>::insert(const pair<const K,E>& thePair){
    //把数对thePair插入字典，覆盖器关键字相同的已存在的数对
    if(thePair.first >= this->tailKey){//关键字太大
        std::ostringstream s;
        s << "Key = " << thePair.first <<" Must be < "<<this->tailKey;
        throw illegalParameterValue(s.str());
    }

    //查看关键字theKey的数对是否已存在
    skipNode<K,E>* theNode = search(thePair.first);
    if(theNode->element.first == thePair.first){
        //若存在，则更新数值对
        theNode->element.second = thePair.second;
        return;
    }

    //若不存在，则确定新节点所在的级链表
    int theLevel = level();//新节点的级
    //使级theLevel为<= levels + 1
    if(theLevel > this->levels){
        theLevel = ++this->levels;
        this->last[theLevel] = this->headNode;
    }

    //在节点theNode之后插入新节点
    skipNode<K,E>* newNode = new skipNode<K,E>(thePair,theLevel + 1);
    for(int i = 0;i<=theLevel;i++){
        //插入i级链表
        newNode->next[i] = this->last[i]->next[i];
        this->last[i]->next[i] = newNode;
    }

    this->dSize++;
    return;
}

template<typename K,typename E>
void skipList<K,E>::output(ostream& out){
    for(skipNode<K,E>* currentNode = this->headNode->next[0];
                       currentNode != this->tailNode;
                       currentNode = currentNode->next[0]){
                           out<<"("<<currentNode->element.first<<" "
                              <<currentNode->element.second<<")";
                       }
}

template<class K,class E>
ostream& operator<<(ostream& out,const skipList<K,E>& theList){
    theList.output(out);
    return out;
}