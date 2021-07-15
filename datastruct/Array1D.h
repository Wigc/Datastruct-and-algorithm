#pragma once

#include <iostream>
#include "xcept.h"

template <class T>
class Array1D
{
private:
    int size;
    T *element; //一维数组
public:
    Array1D(int size = 0);
    Array1D(const Array1D<T> &v); //复制构造函数
    ~Array1D()
    {
        delete[] element;
    }
    T &operator[](int i) const;
    int Size()
    {
        return size;
    }
    Array1D<T> &operator=(const Array1D<T> &v);
    Array1D<T> operator+() const; //一元加法操作
    Array1D<T> operator+(const Array1D<T> &v) const;
    Array1D<T> operator-() const;
    Array1D<T> operator-(const Array1D<T> &v) const;
    Array1D<T> operator*(const Array1D<T> &v) const;
    Array1D<T> &operator+=(const T &x);
    void Resize(int sz){
        delete [] element;
        size = sz;
        element = new T[size];
    }
};

template <class T>
Array1D<T>::Array1D(int size)
{
    if (size < 0)
    {
        throw BadInitializers();
    }
    this->size = size;
    element = new T[this->size];
}

template <class T>
Array1D<T>::Array1D(const Array1D<T> &v)
{
    this->size = v.size;
    element = new T[this->size];
    for (int i = 0; i < this->size; i++)
    {
        element[i] = v.element[i];
    }
}

template <typename T>
T &Array1D<T>::operator[](int i) const
{
    if (i < 0 || i >= this->size)
    {
        throw OutOfBounds();
    }
    return element[i];
}

template <typename T>
Array1D<T> &Array1D<T>::operator=(const Array1D<T> &v)
{
    if (this != &v)
    {
        //不是自我赋值
        this->size = v.size;
        delete[] element;
        element = new T[size];
        for (int i = 0; i < size; i++)
        {
            element[i] = v.element[i];
        }
    }
    return *this;
}

template <typename T>
Array1D<T> Array1D<T>::operator+() const
{ //一元加法操作
    Array1D<T> w(size);
    for (int i = 0; i < size; i++)
    {
        w.element[i] = +element[i];
    }
    return w;
}

template <typename T>
Array1D<T> Array1D<T>::operator+(const Array1D<T> &v) const
{
    if (size != v.size)
    {
        throw SizeMismatch();
    }
    Array1D<T> w(size);
    for (int i = 0; i < size; i++)
    {
        w.element[i] = element[i] + v.element[i];
    }
    return w;
}

template <typename T>
Array1D<T> Array1D<T>::operator-() const
{
    Array1D<T> w(size);
    for (int i = 0; i < size; i++)
    {
        w.element[i] = -element[i];
    }
    return w;
}

template <typename T>
Array1D<T> Array1D<T>::operator-(const Array1D<T> &v) const
{
    if (size != v.size)
    {
        throw SizeMismatch();
    }
    Array1D<T> w(size);
    for (int i = 0; i < size; i++)
    {
        w.element[i] = element[i] - v.element[i];
    }
    return w;
}

template <typename T>
Array1D<T> Array1D<T>::operator*(const Array1D<T> &v) const
{
    if (size != v.size)
    {
        throw SizeMismatch();
    }
    Array1D<T> w(size);
    for (int i = 0; i < size; i++)
    {
        w.element[i] = element[i] * v.element[i];
    }
    return w;
}

template <typename T>
Array1D<T> &Array1D<T>::operator+=(const T &x)
{
    for (int i = 0; i < size; i++)
    {
        element[i] += x;
    }
    return *this;
}