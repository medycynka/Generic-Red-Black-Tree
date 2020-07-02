#ifndef RBTREE_RBT_ITERATOR_HPP
#define RBTREE_RBT_ITERATOR_HPP

#pragma once

#include "rbt_node.hpp"

namespace algo::ds::rbt::iterators {

    template <typename T>
    class Iterator {
    protected:
        algo::ds::rbt::node_impl::RBNode<T>* Iter;
 
    public:
        typedef Iterator                  self_type;
        typedef T                         value_type;
        typedef T&                        reference;
        typedef T*                        pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int                       difference_type;

        Iterator()                                                  : Iter{ nullptr } {}
        explicit Iterator(algo::ds::rbt::node_impl::RBNode<T>* ptr) : Iter{ ptr } {};
        Iterator(const Iterator& s)                                 : Iter{ s.Iter } {};
        Iterator(const Iterator&& s) noexcept                       : Iter{ s.Iter } {};

        inline algo::ds::rbt::node_impl::RBNode<T>* getIter() { return Iter; };

        Iterator       operator++                                          ();
        const Iterator operator++                                          (int);
        Iterator       operator--                                          ();
        const Iterator operator--                                          (int);
        Iterator&      operator=                                           (const Iterator& source)       { if (this != &source) { this->Iter = source.Iter; } return (*this); };
        Iterator&      operator=                                           (Iterator&& source)   noexcept { this->Iter = source.Iter; return (*this); };
        bool           operator==                                          (const Iterator& source) const { return (Iter == source.Iter); };
        bool           operator!=                                          (const Iterator& source) const { return (Iter != source.Iter); };
        explicit       operator algo::ds::rbt::node_impl::RBNode<T>&       ()                             { return (*Iter); };
        explicit       operator const algo::ds::rbt::node_impl::RBNode<T>& ()                       const { return (*Iter); };
        T&             operator*                                           ()                       const { return (Iter->key); };
        algo::ds::rbt::node_impl::RBNode<T>* operator->                    ()                       const { return Iter; };
        explicit       operator bool()                                                              const { return (Iter != nullptr); };
    };

    template <typename T>
    Iterator<T> Iterator<T>::operator++() {
        if (this->Iter != nullptr) {
            this->Iter = this->Iter->node_Successor();

            return *this;
        }
        else return *this;
    }

    template <typename T>
    const Iterator<T> Iterator<T>::operator++(int) {
        Iterator pom = *this;
        ++(*this);

        return pom;
    }

    template <typename T>
    Iterator<T> Iterator<T>::operator--() {
        if (this->Iter != nullptr) {
            this->Iter = this->Iter->node_Predecessor();

            return *this;
        }
        else return *this;
    }

    template <typename T>
    const Iterator<T> Iterator<T>::operator--(int) {
        Iterator pom = *this;
        --(*this);

        return pom;
    }

}

#endif