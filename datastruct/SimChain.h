#pragma once
#include <iostream>


template <class T>
class SimChain
{
public:
    SimChain()
    {
        first = -1;
    }
    ~SimChain()
    {
        Destroy();
    }
    void Destroy(); //使表为空
    int Length() const;
    bool Find(int k, T &x) const;
    int Search(const T &x) const;
    SimChain<T> &Delete(int k, T &x);
    SimChain<T> &Insert(int k, const T &x);
    void Output(std::ostream &out) const;


private:
    int first;            //第一个节点索引
    static SimSpace<T> S; //使用static，是为了使得所有类型为T的模拟链表共享相同的模拟空间

};

template <class T>
void SimChain<T>::Destroy()
{
    //释放链表节点
    int next;
    while (first != -1)
    {
        next = S.node[first].link;
        S.Deallocate(first);
        first = next;
    }
}

template <class T>
int SimChain<T>::Length() const
{
    //返回链表的长度
    int current = first; //链节点当前位置
    int count = 0;       //元素计数
    while (current != -1)
    {
        current = S.node[current].link;
        count++;
    }
    return count;
}

template <class T>
bool SimChain<T>::Find(int k, T &x) const
{
    //查找第k个元素防止x，找到true，否则false
    if (k < 1)
    {
        return false;
    }

    int current = first; //链节点当前位置
    int index = 1;       //当前节点的索引
    //移动current至第k个节点
    while (index < k && current != -1)
    {
        current = S.node[current].link;
        index++;
    }

    if (current != -1)
    {
        x = S.node[current].data;
        return true;
    }
    return false;
}

template <class T>
int SimChain<T>::Search(const T &x) const
{
    //查找x所在位置,找不到返回0
    int current = first; //链节点当前位置
    int index = 0;       //当前节点的索引
    while (current != -1)
    {
        if (x == S.node[current].data)
        {
            return ++index;
        }
        else
        {
            current = S.node[current].link;
        }
    }
    return 0;
}

template <class T>
SimChain<T> &SimChain<T>::Delete(int k, T &x)
{
    //将第k个元素取至x，并删除

    //not exist
    if (k < 1 || first == -1)
    {
        throw OutOfBounds();
    }

    int current = first;
    if (current == 1)
    {
        first = S.node[first].link; //删除
    }
    else
    {
        int q = first;
        // q指向第k-1个
        for (int index = 1; index < k - 1 && q != -1; index++)
        {
            q = S.node[q].link;
        }
        //验证第k个元素存在性
        if (q == -1 || S.node[q].link == -1)
        {
            throw OutOfBounds(); //not exist
        }
        current = S.node[q].link;
        S.node[q].link = S.node[current].link;
    }

    //保存并释放
    x = S.node[current].data;
    S.Deallocate(current);
    return *this;
}

template <class T>
SimChain<T> &SimChain<T>::Insert(int k, const T &x)
{
    //在第k个元素之后插入x
    //如果不存在第k个元素，则抛出异常outofbounds
    //如果没有足够的空间则抛出异常nomem
    if (k < 0)
    {
        throw OutOfBounds();
    }

    int p = first;//p指向第k个节点
    for(int i=1;i<k && p!=-1;i++){
        p = S.node[p].link;
    }

    //验证第k个节点的存在性
    if(k>0&& p==-1){
        throw OutOfBounds();
    }

    int newnode = S.Allocate();
    S.node[newnode].data = x;
    //先向链表中插入新节点
    // 首先检查新节点是否要查到首部
    if(k){
        //在p之后插入
        S.node[newnode].link = S.node[p].link;
    }else{
        //作为首部插入
        S.node[newnode].link = first;
        first = newnode;
    }

    return *this;
}

template<class T>
void SimChain<T>::Output(std::ostream& out)const{
    int current = first;
    
    while(first!= -1){
        out<<S.node[current].data<<" ";
        current = S.node[current].link;
    }
}

template<class T>
std::ostream& operator<<(std::ostream& out,const SimChain<T>& x){
    x.Output(out);
    return out;
}