#pragma once

#include <iostream>
#include "xcept.h"

template<typename T>
class Matrix{
    private:
        int rows;
        int cols;
        T* element;


    public:
        Matrix(int r=0,int c=0);
        Matrix(const Matrix<T>& m);
        ~Matrix(){
            delete [] element;
        }
        int Rows()const{
            return this->rows;
        }
        int Columns()const{
            return this->cols;
        }
        T& operator()(int i,int j)const;
        Matrix<T>& operator=(const Matrix<T>& m);
        Matrix<T> operator+(const Matrix<T>& m)const;
        Matrix<T> operator-(const Matrix<T>& m)const;
        Matrix<T> operator*(const Matrix<T>& m)const;
        Matrix<T>& operator+=(const T& x);
};

template<typename T>
Matrix<T>::Matrix(int r,int c){
    if (r < 0 || c < 0)
    {
        throw BadInitializers();
    }
    if((!r || !c)&&(r||c))
    {
        throw BadInitializers();
    }

    this->rows = r;
    this->cols = c;
    element = new T[r*c];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m){
    
    this->rows = m.rows;
    this->cols = m.cols;

    element = new T[this->rows*this->cols];

    for(int i=0;i<this->cols*this->rows;i++){
        element[i] = m.element[i];
    }
    
}

template<class T>
T& Matrix<T>::operator()(int i,int j)const{
    if(i<1 || i>this->rows || j<1 ||j>this->cols){
        throw OutOfBounds()
    }

    return element[(i-1)*this->cols + j-1];

}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m){
    if(this != &v){
        this->rows = m.rows;
        this->cols = m.cols;
        delete [] this->element;
        this->element = new T[this->rows*this->cols];
        for(int i=0;i<this->rows*this->cols;i++){
            this->element[i] = m.element[i];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const{
    if(this->rows != m.rows || this->cols != m.cols){
        throw SizeMismatch()
    }

    Matrix<T> w(this->rows,this->cols);
    for(int i=0;i< this->rows*this->cols;i++){
        w.element[i] = this->element[i] + m.element[i];
    }

    return w;

}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m)const{
    if(this->rows != m.rows || this->cols != m.cols){
        throw SizeMismatch()
    }

    Matrix<T> w(this->rows,this->cols);
    for(int i=0;i< this->rows*this->cols;i++){
        w.element[i] = this->element[i] - m.element[i];
    }

    return w;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m)const{
    if( this->cols != m.rows ){
        throw SizeMismatch()
    }

    Matrix<T> w(this->rows,m.cols);
    //为*this,w,m定义游标并设定初始位置(1,1)
    int ct = 0;
    int cm = 0;
    int cw = 0;
    //对所有的i,j计算w(i,j)
    for(int i=1;i<=this->rows;i++){
        for(int j=1;j<=m.cols;j++){
            //calculate first 
            T sum = element[ct] * m.element[cm];
            //sum others
            for(int k=2;k<= this->cols;k++){
                ct++;//指向*this第i行的下一个元素
                cm += m.cols;//指向m的第j列的下一项
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;//save w(i,j)
            //重新调整至行首
            ct -= this->cols-1;
            // 调整至下一列
            cm = j; 
        }
        //重新调整至下一行
        ct += cols;
        //重新调整至第一列
        cm = 0;
    }

    return w;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T& x){
    for(int i=0;i<this->rows*this->cols;i++){
        this->element[i] += x;
    }

    return *this;
}