#pragma once
#include <iostream>

template<class T>
class IndirectList{
    public:
        IndirectList(int MaxListSize = 10);
        ~IndirectList();
        bool IsEmpty()const{return length == 0;}
        int Length()const {return length}
        bool Find(int k,T& x)const;
        int Search(const T& x);
        IndirectList<T>& Delete(int k,T& x);
        IndirectList<T>& Insert(int k,const T& x);
        void Output(std::ostream& out)const;
    private:
        T **table;//一维T类型指针数组
        int length;
        int MaxSize;
};

template<class T>
IndirectList<T>::IndirectList(int MaxListSize = 10){
    //构造函数
    MaxSize = MaxListSize;
    table = new T*[MaxSize]
    length = 0;
}

template<class T>
IndirectList<T>::~IndirectList(){
    //析构函数，删除表
    for(int i=0;i<length;i++){
        delete table[i];
    }
    delete [] table;
}

template<class T>
bool IndirectList<T>::Find(int k,T& x)const{
    //取第k个元素之x
    //如果不存在第k个元素，函数返回false，否则返回true
    if(k<1 || k>length){
        return false;
    }

    x = *table[k-1];
    return true;
}

template<class T>
int IndirectList<T>::Search(const T& x){
    //查找元素x所在的位置，找到返回index，否则返回0
    int index = 0;
    for(int i=0;i<length;i++){
        if(x = *table[i]){
            index = i;
        }
    }

    return index;
}

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k,T& x){
    //把第k个元素传送至x,然后删除第k个元素
    //如果不存在第k个元素，则引发异常outofbounds
    if(Find(k,x)){
        //向前移动指针
    }
}
IndirectList<T>& Insert(int k,const T& x);
void Output(std::ostream& out)const;