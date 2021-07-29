/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-27 15:56:06
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-28 18:03:51
 */

#ifndef hashChain_
#define hashChain_

#include <iostream>
#include "hash.h"
#include "sortedChain.h"
#include "dictionary.h"
#include "../CustomException.h"

using std::pair;
using std::ostream;


template<class K,class E>
class hashChain : public Dictionary<K,E>{
    public:
        hashChain(int theDivisor = 11);
        ~hashChain();

        bool empty() const;
        int size() const;
        pair<const K,E>* find(const K& theKey) const;
        void insert(const pair<const K,E>& thePair);
        void erase(const K& theKey);
        void output(ostream& out) const;
    protected:
        sortedChain<K,E>* table;//hash表
        hash<K> hash;//把类型K映射到一个非整数
        int dSize;//字典中数对个数
        int divisor;//散列函数除数
};

template<class K,class E>
hashChain<K,E>::hashChain(int theDivisor){
    this->divisor = theDivisor;
    this->dSize = 0;

    //分配并初始化hash表数组
    this->table = new sortedChain<K,E>[this->divisor];
}

template<class K,class E>
hashChain<K,E>::~hashChain(){
    delete [] this->table;
}

template<class K,class E>
bool hashChain<K,E>::empty() const {
    return this->dSize == 0;
}

template<class K,class E>
int hashChain<K,E>::size() const {
    return this->dSize;
}

template<class K,class E>
pair<const K,E>* hashChain<K,E>::find(const K& theKey) const{
    return this->table[hash(theKey) % this->divisor].find(theKey);
}

template<class K,class E>
void hashChain<K,E>::insert(const pair<const K,E>& thePair){
    int homeBucket = (int) hash(thePair.first) % this->divisor;
    int homeSize = this->table[homeBucket].size();
    this->table[homeBucket].insert(thePair);
    if(this->table[homeBucket].size() > homeSize){
        this->dSize++;
    }
}

template<class K,class E>
void hashChain<K,E>::erase(const K& theKey){
    this->table[hash(theKey) % this->divisor ].erase(theKey);
}
template<class K,class E>
void hashChain<K,E>::output(ostream& out) const {
    for(int i = 0;i < this->dSize;i++){
        if(this->table[i].size() == 0){
            out<<"(NULL)"<<std::endl;
        }else{
            out<<this->table[i]<<std::endl;
        }
    }
}

template<class K,class E>
ostream& operator<<(ostream& out,const hashChain<K,E>& theChain) {
    theChain.output(out);
    return out;
}

#endif
