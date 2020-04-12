#ifndef RBTREE_RBT_CONST_REVERSE_ITERATOR_HPP
#define RBTREE_RBT_CONST_REVERSE_ITERATOR_HPP

#pragma once

#include "rb_node.hpp"


template <typename T>
class ConstReverseIterator{
protected:
    RBNode<T> * Iter;

public:
    typedef ConstReverseIterator      self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    ConstReverseIterator()                                        : Iter(nullptr){};
    explicit ConstReverseIterator(RBNode<T>* ptr)                 : Iter(ptr){};
    ConstReverseIterator(const ConstReverseIterator &s)           : Iter(s.Iter){};
    ConstReverseIterator(const ConstReverseIterator &&s) noexcept : Iter(s.Iter){};

    inline RBNode<T> * getIter() { return Iter; };

    ConstReverseIterator       operator++                ();
    const ConstReverseIterator operator++                (int);
    ConstReverseIterator       operator--                ();
    const ConstReverseIterator operator--                (int);
    ConstReverseIterator &     operator=                 (const ConstReverseIterator &source)       { if(this != &source){ this->Iter = source.Iter; } return (*this); };
    ConstReverseIterator &     operator=                 (ConstReverseIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
    bool                       operator==                (const ConstReverseIterator& source) const { return (Iter == source.Iter); };
    bool                       operator!=                (const ConstReverseIterator& source) const { return (Iter != source.Iter); };
    explicit                   operator RBNode<T>&       ()                                         { return (*Iter); };
    explicit                   operator const RBNode<T>& ()                                   const { return (*Iter); };
    T const &                  operator*                 ()                                   const { return (Iter->key); };
    RBNode<T> const *          operator->                ()                                   const { return Iter; };
    explicit                   operator bool             ()                                   const { return (Iter != nullptr); };
};

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ConstReverseIterator<T> ConstReverseIterator<T>::operator++(int){
    ConstReverseIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ConstReverseIterator<T> ConstReverseIterator<T>::operator--(int){
    ConstReverseIterator pom = *this;
    --(*this);

    return pom;
}

#endif //RBTREE_RBT_CONST_REVERSE_ITERATOR_HPP
