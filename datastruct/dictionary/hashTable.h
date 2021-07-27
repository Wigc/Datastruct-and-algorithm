/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-27 14:25:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-27 15:45:08
 */
#ifndef hashTable_
#define hashTable_

#include <iostream>
#include "../CustomException.h"
#include "hash.h"

using std::pair;
using std::ostream;

template<class K,class E>
class hashTable{
    public:
        hashTable(int theDivisor = 11);
        ~hashTable();

        bool empty() const;
        int size() const;
        pair<const K,E>* find(const K& theKey) const;
        void insert(const pair<const K,E>& thePair);
        void erase(const K& theKey);
        void output(ostream& out) const;

    protected:
        int search(const K& theKey) const;
        pair<const K,E>** table;//散列表
        hash<K> hash;//把类型K映射到一个非整数
        int dSize;//字典中数对个数
        int divisor;//散列函数除数
};

template<class K,class E>
hashTable<K,E>::hashTable(int theDivisor){
    this->divisor = theDivisor;
    this->dSize = 0;

    //分配和初始化散列表数组
    this->table = new pair<const K,E>* [this->divisor];
    for(int i = 0;i<this->divisor;i++){
        this->table[i] = NULL;
    }
}

template<class K,class E>
hashTable<K,E>::~hashTable(){
    delete [] this->table;
}

/**
 * @description: 
 * @param {const K& theKey}     搜索一个公开地址的散列表，查找关键字为theKey的数对，如果匹配的数对存在，返回它的位置，否则，如果散列表不满，则返回关键字为theKey的数对可以插入的位置
 * @return {*}
 * @author: 
 */
template<class K,class E>
int hashTable<K,E>::search(const K& theKey) const{
    int i = (int) hash(theKey) % this->divisor;//起始位置
    int j = i;
    do{
        if(this->table[j] == NULL || this->table[j]->first == theKey){
            return j;
        }

        j = (j + 1) % this->divisor;//下一个位置
    }while(j != i);//是否返回到启示位置

    return j;//表满
}



template<class K,class E>
bool hashTable<K,E>::empty() const {
    return this->dSize == 0;
}

template<class K,class E>
int hashTable<K,E>::size() const {
    return this->dSize;
}

template<class K,class E>
pair<const K,E>* hashTable<K,E>::find(const K& theKey) const {
    int b = this->search(theKey);

    if(this->table[b] == NULL || this->table[b]->first != theKey){
        return NULL; //不匹配
    }

    return this->table[b];//找到
}

template<class K,class E>
void hashTable<K,E>::insert(const pair<const K,E>& thePair){
    int b = this->search(thePair.first);

    if(this->table[b] == NULL){
        //没有匹配，且表不满
        this->table[b] = new pair<const K,E>(thePair);
        this->dSize++;
    }else{
        //检查是否有重复的关键字或表满
        if(this->table[b]->first == thePair.first){
            this->table[b]->second = thePair.second;
        }else{
            throw hashTableFull();
        }
    }
}

template<class K,class E>
void hashTable<K,E>::erase(const K& theKey){
    int b = this->search(theKey);

    if(this->table[b] == NULL){
        std::cout<<"No match"<<std::endl;
        return;
    }else{
        if(this->table[b]->fisrt == theKey){
            delete this->table[b];
            this->table[b] = NULL;
            for(int i = b+1;this->table[i] != NULL;i++){
                if(this->table[i] != NULL && ((int)hash(this->table[i]->first)%this->divisor == i)){
                    break;
                }
                this->table[i-1] = this->table[i];
            }
        }
    }

    
}

template<class K,class E>
void hashTable<K,E>::output(ostream& out) const {
    for(int i = 0;i< this->divisor;i++){
        if(this->table[i]==NULL){
            out<<"(NULL)"<<std::endl;
        }else{
            out<<"("<<this->table[i]->first<<" "<<this->table[i]->second<< ")"<<std::endl;
        }
    }
}

template<class K,class E>
ostream& operator<<(ostream& out,const hashTable<K,E>& theTable){
    theTable.output(out);
    return out;
}

#endif