#pragma once

#include <iostream>
#include "../CustomException.h"

template <typename T>
class Matrix
{
    friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &m);

private:
    int theRows;    //矩阵行数
    int theColumns; //矩阵列数
    T *element;

public:
    Matrix(int theRows = 0, int theColumns = 0);
    Matrix(const Matrix<T> &m);
    ~Matrix()
    {
        delete[] element;
    }
    int rows() const
    {
        return this->theRows;
    }
    int columns() const
    {
        return this->theColumns;
    }
    T &operator()(int i, int j) const;
    Matrix<T> &operator=(const Matrix<T> &m);
    Matrix<T> operator+() const; // 一元+
    Matrix<T> operator+(const Matrix<T> &m) const;
    Matrix<T> operator-() const; //一元-
    Matrix<T> operator-(const Matrix<T> &m) const;
    Matrix<T> operator*(const Matrix<T> &m) const;
    Matrix<T> &operator+=(const T &x);
};

template <typename T>
Matrix<T>::Matrix(int theRows, int theColumns)
{
    if (theRows < 0 || theColumns < 0)
    {
        throw illegalParameterValue("Rows and columns must be >= 0");
    }

    if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
    {
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    }

    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m)
{

    this->theRows = m.theRows;
    this->theColumns = m.theColumns;

    element = new T[this->theRows * this->theColumns];

    for (int i = 0; i < this->theColumns * this->theRows; i++)
    {
        element[i] = m.element[i];
    }
}

template <class T>
T &Matrix<T>::operator()(int i, int j) const{
    if (i < 1 || i > this->theRows || j < 1 || j > this->theColumns)
    {
        throw matrixIndexOutOfBounds();
    }

    return element[(i - 1) * this->theColumns + j - 1];
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m){
    if (this != &m)
    {
        
        this->theRows = m.theRows;
        this->theColumns = m.theColumns;
        delete[] this->element;
        this->element = new T[this->theRows * this->theColumns];
        for (int i = 0; i < this->theRows * this->theColumns; i++)
        {
            this->element[i] = m.element[i];
        }
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const{
    if (this->theRows != m.theRows || this->theColumns != m.theColumns)
    {
        throw matrixSizeMismatch();
    }

    Matrix<T> w(this->theRows, this->theColumns);
    for (int i = 0; i < this->theRows * this->theColumns; i++)
    {
        w.element[i] = this->element[i] + m.element[i];
    }

    return w;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const
{
    if (this->theRows != m.theRows || this->theColumns != m.theColumns)
    {
        throw matrixSizeMismatch();
    }

    Matrix<T> w(this->theRows, this->theColumns);
    for (int i = 0; i < this->theRows * this->theColumns; i++)
    {
        w.element[i] = this->element[i] - m.element[i];
    }

    return w;
}

template<class T>
Matrix<T> Matrix<T>::operator+() const
{// Return w = -(*this).
 
   // create result matrix w
   Matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = +element[i];
   return w;
 
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{// Return w = -(*this).
 
   // create result matrix w
   Matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = -element[i];
   return w;
 
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) const
{
    if (this->theColumns != m.theRows)
    {
        throw matrixSizeMismatch();
    }

    Matrix<T> w(this->theRows, m.theColumns);
    //为*this,w,m定义游标并设定初始位置(1,1)
    int ct = 0;
    int cm = 0;
    int cw = 0;
    //对所有的i,j计算w(i,j)
    for (int i = 1; i <= this->theRows; i++)
    {
        for (int j = 1; j <= m.theColumns; j++)
        {
            //calculate first
            T sum = element[ct] * m.element[cm];
            //sum others
            for (int k = 2; k <= this->theColumns; k++)
            {
                ct++;               //指向*this第i行的下一个元素
                cm += m.theColumns; //指向m的第j列的下一项
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum; //save w(i,j)
            //重新调整至行首
            ct -= this->theColumns - 1;
            // 调整至下一列
            cm = j;
        }
        //重新调整至下一行
        ct += theColumns;
        //重新调整至第一列
        cm = 0;
    }

    return w;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const T &x)
{
    for (int i = 0; i < this->theRows * this->theColumns; i++)
    {
        this->element[i] += x;
    }

    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& out,const Matrix<T>& m){
    int k = 0;
    for(int i = 0;i<m.theRows;i++){
        for(int j=0;j<m.theColumns;j++){
            out << m.element[k++] << " ";
        }
        out<<std::endl;
    }
    return out;
}

// for some reason compiler can't create this on its own
std::ostream& operator<<(std::ostream& out, const Matrix<int>& m)
{// Put matrix m into the stream out.
 // One row per line.
   int k = 0;  // index into element array
   for (int i = 0; i < m.theRows; i++)
   {// do row i
      for (int j = 0; j < m.theColumns; j++)
         out << m.element[k++] << "  ";
 
      // row i finished
      out << std::endl;
   }
 
   return out;
}