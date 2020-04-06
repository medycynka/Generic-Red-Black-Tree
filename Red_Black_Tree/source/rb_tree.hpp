#ifndef RBTREE_RB_TREE_HPP
#define RBTREE_RB_TREE_HPP

#pragma once

#include "rb_node.hpp"
#include "rbt_iterator.hpp"
#include "rbt_reverse_iterator.hpp"
#include "rbt_const_iterator.hpp"
#include "rbt_const_reverse_iterator.hpp"
#include <initializer_list>


template <typename T>
class RBTree{
private:
    /**
     * Helper functions
    */
    explicit        RBTree(RBNode<T>* in) : root(in){ size_ = Size(root); };

    inline size_t   Size(RBNode<T>*);
    inline void     Display(RBNode<T>*, size_t);
    inline void     Rotate_left(RBNode<T>*);
    inline void     Rotate_right(RBNode<T>*);
    inline void     Insert_fix(RBNode<T>*);
    inline void     Merge(RBNode<T>*);
    inline void     Split(RBNode<T>*);
    inline void     Delete_fix(RBNode<T>*);
    inline void     Copy(RBNode<T>*);
    inline void     Chop(RBNode<T>*);

public:
    /**
    * Constructors
    */
    RBTree()                             : size_(0), root(nullptr){};
    RBTree(const RBTree<T> &t)           : size_(0), root(nullptr){ Copy(t.root); };
    RBTree(const RBTree<T> &&t) noexcept : size_(0), root(nullptr){ Copy(t.root); };

    RBTree(std::initializer_list<T> init): size_(0){ for(auto &e : init){ insert(e); } };

    template<typename InputIt>
    RBTree(InputIt first, InputIt last)  : size_(0){ for(auto it = first; it != last; it++){ insert(*it); } };


    /**
     * Utility functions
    */
    inline RBNode<T>*         getRoot() const { return root; };
    inline size_t             size()          { return size_; };
    [[nodiscard]] inline bool isEmpty() const { return (root == nullptr && size_ == 0); };
    inline void               display()       { Display(root, 0); };
    inline void               clear()         { size_ = 0; Chop(root); root = nullptr; };
    inline RBNode<T>*         maxIt()   const { return ( isEmpty() ? nullptr : root->max_node() ); };
    inline RBNode<T>*         minIt()   const { return ( isEmpty() ? nullptr : root->min_node() ); };
    inline void               insert(const T &input);
    inline bool               find(const T&);
    inline Iterator<T>        find_it(const T&);
    inline ConstIterator<T>   find_it(const T&) const;
    inline RBNode<T>*         node_find(const T&);
    inline size_t             Black_hight();
    inline bool               remove(const T&);
    inline std::pair<Iterator<T>, Iterator<T>>           get_from_to(const T &from, const T &to);
    inline std::pair<ConstIterator<T>, ConstIterator<T>> get_from_to(const T &from, const T &to) const;
    inline std::pair<Iterator<T>, Iterator<T>>           equal_range(const T &x);
    inline std::pair<ConstIterator<T>, ConstIterator<T>> equal_range(const T &x) const;
    inline Iterator<T>                                   lower_bound(const T &x);
    inline ConstIterator<T>                              lower_bound(const T &x) const;
    inline Iterator<T>                                   upper_bound(const T &x);
    inline ConstIterator<T>                              upper_bound(const T &x) const;

    /**
     * Operators
    */
    inline void     operator+ (const RBTree<T>& in)         { Merge(in.root); };
    inline void     operator- (const RBTree<T>& in)         { Split(in.root); };
    inline RBTree&  operator+=(const T &x)                  { insert(x); return *this; };
    inline RBTree&  operator-=(const T &x)                  { remove(x); return *this; };
    inline T        operator[](const size_t &id);
    inline const T  operator[](const size_t &id)      const;
    inline RBTree&  operator= (const RBTree<T> &);
    inline RBTree&  operator= (RBTree<T> &&)       noexcept;
    inline bool     operator==(const RBTree<T> &)     const;
    inline bool     operator!=(const RBTree<T> &tree) const { return !(*this == tree); };
    inline bool     operator< (const RBTree<T> &tree) const;
    inline bool     operator<=(const RBTree<T> &tree) const { return !(*this > tree); };
    inline bool     operator> (const RBTree<T> &tree) const;
    inline bool     operator>=(const RBTree<T> &tree) const { return !(*this < tree); };

    /**
     * Iterators
     * Begin/End functions
    */
    Iterator<T>             begin()   const { return Iterator<T>(minIt()); };
    Iterator<T>             end()     const { return Iterator<T>(); };
    ReverseIterator<T>      rbegin()  const { return ReverseIterator<T>(maxIt()); };
    ReverseIterator<T>      rend()    const { return ReverseIterator<T>(); };
    ConstIterator<T>        cbegin()  const { return ConstIterator<T>(minIt()); };
    ConstIterator<T>        cend()    const { return ConstIterator<T>(); };
    ConstReverseIterator<T> crbegin() const { return ConstReverseIterator<T>(maxIt()); };
    ConstReverseIterator<T> crend()   const { return ConstReverseIterator<T>(); };

private:
    size_t   size_;
    RBNode<T> *root;
};

template <typename T>
inline void RBTree<T>::Copy(RBNode<T> *in){
    if(in){
        insert(in->key);
        Copy(in->left);
        Copy(in->right);
    }
}

template <typename T>
inline void RBTree<T>::Chop(RBNode<T> *in){
    if(in){
        Chop(in->left);
        Chop(in->right);

        delete in;
    }
}

template <typename T>
inline RBTree<T>& RBTree<T>::operator=(const RBTree<T> &tree){
    if(this != &tree){
        Chop(root);
        root = nullptr;
        Copy(tree.root);
    }

    return *this;
}

template <typename T>
inline RBTree<T>& RBTree<T>::operator=(RBTree<T> &&tree) noexcept{
    if(this != &tree){
        Chop(root);
        root = nullptr;
        Copy(tree.root);
    }

    return *this;
}

template<typename T>
bool RBTree<T>::operator==(const RBTree<T> &tree) const{
    if(size_ != tree.size_ || root != tree.root) return false;
    else{
        auto it = begin();
        auto tree_it = tree.begin();

        while(it != end() && tree_it != tree.end()){
            if(*it != *tree_it) return false;
            else{
                ++it;
                ++tree_it;
            }
        }

        return true;
    }
}

template<typename T>
bool RBTree<T>::operator<(const RBTree<T> &tree) const{
    if(size_ == tree.size_ && root < tree.root){
        auto it = begin();
        auto tree_it = tree.begin();

        while(it != end() && tree_it != tree.end()){
            if(*it >= *tree_it) return false;
            else{
                ++it;
                ++tree_it;
            }
        }

        return true;
    }
    else{
        return (size_ < tree.size_ && root < tree.root);
    }
}

template <typename T>
bool RBTree<T>::operator>(const RBTree<T> &tree) const{
    if(size_ == tree.size_ && root > tree.root){
        auto it = begin();
        auto tree_it = tree.begin();

        while(it != end() && tree_it != tree.end()){
            if(*it <= *tree_it) return false;
            else{
                ++it;
                ++tree_it;
            }
        }

        return true;
    }
    else{
        return (size_ > tree.size_ && root > tree.root);
    }
}

template<typename T>
T RBTree<T>::operator[](const size_t &id){
    if(id < 0 || id >= size_) throw std::out_of_range("Wrong index");
    else{
        if(id == 0) return minIt()->key;

        auto count = 1;
        auto *n = minIt()->node_Successor();

        while(count++ != id) n = n->node_Successor();

        return n->key;
    }
}

template<typename T>
const T RBTree<T>::operator[](const size_t &id) const{
    if(id < 0 || id >= size_) throw std::out_of_range("Wrong index");
    else{
        if(id == 0) return minIt()->key;

        auto count = 1;
        auto *n = minIt()->node_Successor();

        while(count++ != id) n = n->node_Successor();

        return n->key;
    }
}

template <typename T>
inline void RBTree<T>::insert(const T &input){
    RBNode<T> *q;
    auto *create = new RBNode<T>(input);
    auto p = root;
    q = nullptr;

    if(root == nullptr ){
        root = create;
        create->father = nullptr;
    }
    else{
        while(p != nullptr){
            q = p;

            if(p->key > create->key) p = p->left;
            else if(p->key < create->key) p = p->right;
            else return;
        }

        create->father = q;

        if(q->key < create->key) q->right = create;
        else if(q->key > create->key) q->left = create;
        else return;
    }

    size_++;
    Insert_fix(create);
}

template<typename T>
inline void RBTree<T>::Insert_fix(RBNode<T> *create){
    auto *x = create;

    while(x != root && x->father->color == red){
        if(x->father == x->father->father->left){
            auto *y = x->father->father->right;

            if((y != nullptr ) && (y->color == red)){
                x->father->color = black;
                y->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else{
                if(x->father->right == x){
                    x = x->father;
                    Rotate_left(x);
                }

                x->father->color = black;
                x->father->father->color = red;
                Rotate_right(x->father->father);
            }
        }
        else{
            auto *y = x->father->father->left;

            if((y != nullptr) && (y->color == red)){
                x->father->color = black;
                y->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else{
                if(x->father->left == x){
                    x = x->father;
                    Rotate_right(x);
                }

                x->father->color = black;
                x->father->father->color = red;
                Rotate_left(x->father->father);
            }
        }
    }

    root->color = black;
}

template<typename T>
inline void RBTree<T>::Rotate_right(RBNode<T>* in){
    if(in->left == nullptr) return;
    else{
        auto *x = in->left;
        auto *b = x->right;
        auto *f = in->father;

        if(f == nullptr){
            x->father = nullptr;
            root = x;
        }
        else{
            x->father = f;

            if(f->left == in) f->left = x;
            if(f->right == in) f->right = x;
        }

        x->right = in;
        in->father = x;
        in->left = b;

        if(b != nullptr) b->father = in;
    }
}

template <typename T>
inline void RBTree<T>::Rotate_left(RBNode<T>* x){
    if(x->right == nullptr) return;
    else{
        auto *y = x->right;
        auto *b = y->left;
        auto *f = x->father;

        if(f == nullptr){
            y->father = nullptr;
            root = y;
        }
        else{
            y->father = f;

            if(f->left == x) f->left = y;
            if(f->right == x) f->right = y;
        }

        y->left = x;
        x->father = y;
        x->right = b;

        if(b != nullptr) b->father = x;
    }
}

template <typename T>
inline bool RBTree<T>::find(const T &in){
    auto *t = root;

    while(t != nullptr){
        if(t->key == in) return true;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    return false;
}

template <typename T>
inline Iterator<T> RBTree<T>::find_it(const T &x) {
    for(auto it = begin(); it != end(); ++it){
        if(*it == x){
            return it;
        }
    }

    return end();
}

template <typename T>
inline ConstIterator<T> RBTree<T>::find_it(const T &x) const {
    for(const auto it = cbegin(); it != cend(); ++it){
        if(*it == x){
            return it;
        }
    }

    return cend();
}

template<typename T>
RBNode<T>* RBTree<T>::node_find(const T &in){
    auto *t = root;

    while(t != nullptr){
        if(t->key == in) return t;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    return nullptr;
}


template<typename T>
inline void RBTree<T>::Merge(RBNode<T> *p ){
    if(p != nullptr){
        if(p->left) Merge(p->left);
        if(p->right) Merge(p->right);

        insert(p->key);
    }
}

template<typename T>
inline void RBTree<T>::Split(RBNode<T> *p ) {
    if(p != nullptr){
        if(p->left) Split(p->left);
        if(p->right) Split(p->right);

        remove(p->key);
    }
}

template<typename T>
inline size_t RBTree<T>::Black_hight(){
    auto *p = root;
    auto num = 0;

    while(p != nullptr){
        if(p->color == black) num++;

        p = p->left;
    }

    return num;
}

template<typename T>
inline size_t RBTree<T>::Size(RBNode<T> * in){
    if(in == nullptr) return 0;
    else{
        auto ls = Size(in->left);
        auto rs = Size(in->right);

        return (ls + rs + 1);
    }
}

template<typename T>
inline void RBTree<T>::Display(RBNode<T>* in, size_t level){
    if(in == nullptr) return;

    std::cout << "level: " << level << std::endl;
    std::cout << in;

    Display(in->left, level+1);
    Display(in->right, level+1);
}

template <typename T>
inline bool RBTree<T>::remove(const T &x){
    if(root == nullptr){
        std::cout << "\nEmpty RBTree." ;

        return false;
    }

    auto *p = root;
    auto found = 0;

    while(p != nullptr && found == 0){
        if(p->key == x) found = 1;
        if(found == 0){
            if(p->key < x) p = p->right;
            else p = p->left;
        }
    }

    if(found == 0) return false;
    else{
        //std::cout << "Deleted Element: " << p->key << " Colour: " << (p->color == black ? "Black" : "Red" ) << "   SIZE: " << size_-1 << std::endl;

        RBNode<T> *y = nullptr;
        RBNode<T> *q = nullptr;

        if(p->left == nullptr || p->right == nullptr) y = p;
        else y = p->node_Successor();

        if(y->left != nullptr) q = y->left;
        else{
            if(y->right != nullptr) q = y->right;
            else q = nullptr;
        }

        if(q != nullptr) q->father = y->father;

        if(y->father == nullptr) root = q;
        else{
            if(y == y->father->left) y->father->left = q;
            else y->father->right = q;
        }

        if(y != p){
            p->color = y->color;
            p->key = y->key;
        }

        if(y->color == black) Delete_fix(q);

        size_--;

        return true;
    }
}

template <typename T>
inline void RBTree<T>::Delete_fix(RBNode<T> *p){
    if(p != nullptr){
        RBNode<T> *s;

        while(p != root && p->color == black){
            if(p->father->left == p){
                s = p->father->right;

                if(s->color == red){
                    s->color = black;
                    p->father->color = red;
                    Rotate_left(p->father);
                    s = p->father->right;
                }
                if(s->right->color == black && s->left->color == black){
                    s->color = red;
                    p = p->father;
                }
                else{
                    if(s->right->color == black){
                        s->left->color = black;
                        s->color = red;
                        Rotate_right(s);
                        s = p->father->right;
                    }

                    s->color = p->father->color;
                    p->father->color = black;
                    s->right->color = black;
                    Rotate_left(p->father);
                    p = root;
                }
            }
            else{
                s = p->father->left;

                if(s->color == red){
                    s->color = red;
                    p->father->color = red;
                    Rotate_right(p->father);
                    s = p->father->left;
                }
                if(s->left->color == black && s->right->color == black){
                    s->color = red;
                    p = p->father;
                }
                else{
                    if(s->left->color == black){
                        s->right->color = black;
                        s->color = red;
                        Rotate_left(s);
                        s = p->father->left;
                    }

                    s->color = p->father->color;
                    p->father->color = black;
                    s->left->color = black;
                    Rotate_right(p->father);
                    p = root;
                }
            }

            p->color = black;
            root->color = black;
        }
    }
}

template<typename T>
std::pair<Iterator<T>, Iterator<T>> RBTree<T>::get_from_to(const T &from, const T &to) {
    if(from <= to) {
        Iterator<T> f_;
        Iterator<T> t_;

        for (auto it = begin(); it != end(); ++it) {
            if (!f_ && *it == from) {
                f_ = it;
            }
            if (!t_ && *it == to) {
                t_ = it;
            }
            if(f_ && t_){
                break;
            }
        }

        return {f_ ? f_ : end(), t_ ? t_ : end()};
    } else{
        return {end(), end()};
    }
}

template<typename T>
std::pair<ConstIterator<T>, ConstIterator<T>> RBTree<T>::get_from_to(const T &from, const T &to) const {
    if(from <= to) {
        ConstIterator<T> f_;
        ConstIterator<T> t_;

        for (const auto it = cbegin(); it != cend(); ++it) {
            if (!f_ && *it == from) {
                f_ = it;
            }
            if (!t_ && *it == to) {
                t_ = it;
            }
            if(f_ && t_){
                break;
            }
        }

        return {f_ ? f_ : cend(), t_ ? t_ : cend()};
    } else{
        return {cend(), cend()};
    }
}

template<typename T>
std::pair<Iterator<T>, Iterator<T>> RBTree<T>::equal_range(const T &x) {
    return {lower_bound(x), upper_bound(x)};
}

template<typename T>
std::pair<ConstIterator<T>, ConstIterator<T>> RBTree<T>::equal_range(const T &x) const {
    return {lower_bound(x), upper_bound(x)};
}

template<typename T>
Iterator<T> RBTree<T>::lower_bound(const T &x) {
    for(auto it = begin(); it != end(); ++it){
        if(*it >= x){
            return it;
        }
    }

    return end();
}

template<typename T>
ConstIterator<T> RBTree<T>::lower_bound(const T &x) const {
    for(const auto it = cbegin(); it != cend(); ++it){
        if(*it >= x){
            return it;
        }
    }

    return cend();
}

template<typename T>
Iterator<T> RBTree<T>::upper_bound(const T &x) {
    for(auto it = begin(); it != end(); ++it){
        if(*it > x){
            return it;
        }
    }

    return end();
}

template<typename T>
ConstIterator<T> RBTree<T>::upper_bound(const T &x) const {
    for(const auto it = cbegin(); it != cend(); ++it){
        if(*it > x){
            return it;
        }
    }

    return cend();
}

#endif //RBTREE_RB_TREE_HPP
