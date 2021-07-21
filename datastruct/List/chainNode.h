#pragma once

template <class T>
struct ChainNode 
{
   // data members
   T element;
   ChainNode<T> *next;
 
   // methods
   ChainNode() {}
   ChainNode(const T& element)
      {this->element = element;}
   ChainNode(const T& element, ChainNode<T>* next)
      {this->element = element;
       this->next = next;}
};