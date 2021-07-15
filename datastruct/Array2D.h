#pragma once

#include <iostream>
#include "Array1D.h"
#include "xcept.h"

template <typename T>
class Array2D
{
private:
    int rows;
    int cols;
    Array1D<T> *row;

public:
    Array2D(int r = 0, int c = 0);
    Array2D(const Array2D<T> &m);
    ~Array2D()
    {
        delete[] row;
    }
    int Rows() const
    {
        return rows;
    }
    int Columns() const
    {
        return cols;
    }
    Array1D<T> &operator[](int i) const;
    Array2D<T> &operator=(const Array2D<T>& m);
    Array2D<T> operator+() const;
    Array2D<T> operator+(const Array2D<T>& m) const;
    Array2D<T> operator - () const;
    Array2D<T> operator-(const Array2D<T>& m) const;
    Array2D<T> operator*(const Array2D<T>& m) const;
    Array2D<T>& operator += (const T& x);
};

template <typename T>
Array2D<T>::Array2D(int r, int c)
{
    if (r < 0 || c < 0)
    {
        throw BadInitializers();
    }
    if((!r || !c)&&(r||c))
    {
        throw BadInitializers();
    }
    rows = r;
    cols = c;
    row = new Array1D<T>[rows];
    for (int i = 0; i < r; i++)
    {
        row[i].Resize(cols);
    }
}

template<typename T>
Array2D<T>::Array2D(const Array2D<T>& m){
    rows = m.rows;
    cols = m.cols;
    row = new Array1D<T>[rows];
    for(int i = 0;i<rows;i++){
        row[i]= m.row[i];
    }

}

template<typename T>
Array1D<T>& Array2D<T>::operator[](int i) const{
    if (i < 0 || i >= this->rows)
    {
        throw OutOfBounds();
    }
    return row[i];
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& m){
    if(this != &v){
        rows = m.rows;
        cols = m.cols;
        delete [] row;
        row = new Array1D<T>[rows];
        for(int i=0;i<rows;i++){
            row[i] = m.row[i];
        }
    }
    return *this;
}

template<typename T>
Array2D<T> Array2D<T>::operator+() const{
    Array2D<T> w(rows,cols);
    for(int i=0;i<row;i++){
        for(int j=0;i<cols;j++){
            w.row[i][j] = +row[i][j];
        }
    }
    return w;
}

template<typename T>
Array2D<T> Array2D<T>::operator+(const Array2D<T>& m) const{
    if(rows != m.rows || cols != m.cols){
        throw SizeMismatch();
    }

    Array2D<T> w(rows,cols);
    for(int i=0;i<rows;i++){
        w.row[i] = row[i] + m.row[i];
    }

    return w;
}

template<typename T>
Array2D<T> Array2D<T>::operator-(const Array2D<T>& m) const{
    if(rows != m.rows || cols != m.cols){
        throw SizeMismatch();
    }

    Array2D<T> w(rows,cols);
    for(int i=0;i<rows;i++){
        w.row[i] = row[i] - m.row[i];
    }

    return w;
}

template<typename T>
Array2D<T> Array2D<T>::operator*(const Array2D<T>& m) const{
    if(cols != m.rows){
        throw SizeMismatch();
    }

    Array2D<T> w(rows,m.cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<m.cols;j++){
            T sum = (*this)[i][0] * m[0][j];
            for(int k=1;k<cols;k++){
                sum += (*this)[i][k] * m[k][j];
            }
            w[i][j] = sum;
        }
    }

    return w;
}

template<typename T>
Array2D<T>& Array2D<T>::operator += (const T& x){
    for(int i=0;i<rows;i++){
        row[i] += x;
    }

    return *this;
}