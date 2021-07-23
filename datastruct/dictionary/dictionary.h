#pragma once



template<typename K,typename E>
class Dictionary{
    public:
        virtual ~Dictionary(){}
        virtual bool empty() const = 0;//当且仅当字典为空时，返回true
        virtual int size() const = 0;//返回字典中数对的数目
        virtual std::pair<const K, E>* find(const K&) const = 0;//返回匹配数对的指针
        virtual void erase(const K&) = 0;//删除匹配的数对
        virtual void insert(const std::pair<const K, E>& ) = 0;//往字典中插入一个数对
};