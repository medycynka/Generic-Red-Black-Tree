#ifndef RBTREE_RBT_CONST_ITERATOR_HPP
#define RBTREE_RBT_CONST_ITERATOR_HPP

#pragma once

#include "rb_node.hpp"


template <typename T>
class ConstIterator{
protected:
    RBNode<T> * Iter;

public:
    typedef ConstIterator             self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    ConstIterator()                                 : Iter(nullptr){};
    explicit ConstIterator(RBNode<T>* ptr)          : Iter(ptr){};
    ConstIterator(const ConstIterator &s)           : Iter(s.Iter){};
    ConstIterator(const ConstIterator &&s) noexcept : Iter(s.Iter){};

    inline RBNode<T> * getIter() { return Iter; };

    ConstIterator       operator++                 ();
    const ConstIterator operator++                 (int);
    ConstIterator       operator--                 ();
    const ConstIterator operator--                 (int);
    ConstIterator &     operator=                  (const ConstIterator &source)       { if(this != &source){ this->Iter = source.Iter; } return (*this); };
    ConstIterator &     operator=                  (ConstIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
    bool                operator==                 (const ConstIterator& source) const { return (Iter == source.Iter); };
    bool                operator!=                 (const ConstIterator& source) const { return (Iter != source.Iter); };
    explicit            operator RBNode<T> &       ()                                  { return (*Iter); };
    explicit            operator const RBNode<T> & ()                            const { return (*Iter); };
    T const &           operator*                  ()                            const { return (Iter->key); };
    RBNode<T> const *   operator->                 ()                            const { return Iter; };
    explicit            operator bool              ()                            const { return (Iter != nullptr); };
};

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ConstIterator<T> ConstIterator<T>::operator++(int){
    ConstIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const ConstIterator<T> ConstIterator<T>::ConstIterator::operator--(int){
    ConstIterator pom = *this;
    --(*this);

    return pom;
}

#endif //RBTREE_RBT_CONST_ITERATOR_HPP
