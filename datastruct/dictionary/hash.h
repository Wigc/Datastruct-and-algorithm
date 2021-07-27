/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-27 14:30:28
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-27 14:35:11
 */
#ifndef hash_
#define hash_

#include <iostream>
#include <string>

using std::string;

template<class K> class hash;

template<>
class hash<string>{
  public:
    size_t operator()(const string theKey) const{
        //把关键字theKey转换为一个非负整数
        unsigned long hashValue = 0;
        int length = (int) theKey.length();
        for(int i = 0; i< length;i++){
            hashValue = 5 * hashValue + theKey.at(i);
        }

        return size_t(hashValue);
    }  
};

template<>
class hash<int>{
    public:
        size_t operator()(const int theKey) const{
            return size_t(theKey);
        }
};


template<>
class hash<long>{
    public:
        size_t operator()(const long theKey) const{
            return size_t(theKey);
        }
};

#endif