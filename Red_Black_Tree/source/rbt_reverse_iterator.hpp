#ifndef RBTREE_UNIQUE_PTR_RBT_REVERSE_ITERATOR_HPP
#define RBTREE_UNIQUE_PTR_RBT_REVERSE_ITERATOR_HPP

#pragma once

#include "rb_node.hpp"


template <typename T>
class ReverseIterator{
protected:
    RBNode<T> * Iter;

public:
    typedef ReverseIterator           self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    ReverseIterator()                                   : Iter(nullptr){};
    explicit ReverseIterator(RBNode<T>* ptr)            : Iter(ptr){};
    ReverseIterator(const ReverseIterator &s)           : Iter(s.Iter){};
    ReverseIterator(const ReverseIterator &&s) noexcept : Iter(s.Iter){};

    inline RBNode<T> * getIter() { return Iter; };

    ReverseIterator       operator++                ();
    const ReverseIterator operator++                (int);
    ReverseIterator       operator--                ();
    const ReverseIterator operator--                (int);
    ReverseIterator &     operator=                 (const ReverseIterator &source)       { if(this != &source){ this->Iter = source.Iter; } return (*this); };
    ReverseIterator &     operator=                 (ReverseIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
    bool                  operator==                (const ReverseIterator& source) const { return (Iter == source.Iter); };
    bool                  operator!=                (const ReverseIterator& source) const { return (Iter != source.Iter); };
    explicit              operator RBNode<T>&       ()                                    { return (*Iter); };
    explicit              operator const RBNode<T>& ()                              const { return (*Iter); };
    T &                   operator*                 ()                              const { return (Iter->key); };
    RBNode<T> *           operator->                ()                              const { return Iter; };
    explicit              operator bool             ()                              const { return (Iter != nullptr); };
};

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ReverseIterator<T> ReverseIterator<T>::operator++(int){
    ReverseIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
ReverseIterator<T> ReverseIterator<T>::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ReverseIterator<T> ReverseIterator<T>::operator--(int){
    ReverseIterator pom = *this;
    --(*this);

    return pom;
}

#endif //RBTREE_UNIQUE_PTR_RBT_REVERSE_ITERATOR_HPP
