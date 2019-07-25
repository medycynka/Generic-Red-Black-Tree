#ifndef _SIMPLE_RED_BLACK_TREE_HPP_
#define _SIMPLE_RED_BLACK_TREE_HPP_

#pragma once
#include "tree_node.hpp"

template <typename T>
class RBTree{
    private:
        /**
        * Helper functions
        */
        explicit        RBTree(node<T>* in) : root(in){ size_ = Size(root); };

        inline size_t   Size(node<T>*);
        inline void     Display(node<T>*, size_t);
        inline void     Rotate_left(node<T>*);
        inline void     Rotate_right(node<T>*);
        inline void     Insert_fix(node<T>*);
        inline void     Merge(node<T>*);
        inline void     Split(node<T>*);
        inline void     Delete_fix(node<T>*);
        inline void     Copy(node<T>*);
        inline void     Chop(node<T>*);

    public:
        /**
        * Iterators
        */
        class Iterator{
            protected:
                node<T> * Iter;

            public:
                friend class RBTree;
                typedef Iterator                  self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                Iterator()                            : Iter(nullptr){}
                explicit Iterator(node<T>* ptr)       : Iter(ptr){};
                Iterator(const Iterator &s)           : Iter(s.Iter){};
                Iterator(const Iterator &&s) noexcept : Iter(s.Iter){};

                inline node<T> *getIter() { return Iter; };

                Iterator       operator++               ();
                const Iterator operator++               (int);
                Iterator       operator--               ();
                const Iterator operator--               (int);
                Iterator &     operator=                (const Iterator &source)       { this->Iter = source.Iter; return (*this); };
                Iterator &     operator=                (Iterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
                bool           operator==               (const Iterator& source) const { return (Iter == source.Iter); };
                bool           operator!=               (const Iterator& source) const { return (Iter != source.Iter); };
                explicit       operator node<T> &       ()                             { return (*Iter); };
                explicit       operator const node<T> & ()                       const { return (*Iter); };
                T &            operator*                ()                       const { return (Iter->key); };
                node<T> *      operator->               ()                       const { return Iter; };
                explicit       operator bool            ()                       const { return (Iter != nullptr); };
        };

        class ReverseIterator{
            protected:
                node<T> * Iter;

            public:
                friend class RBTree;
                typedef ReverseIterator           self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ReverseIterator()                                   : Iter(nullptr){};
                explicit ReverseIterator(node<T>* ptr)              : Iter(ptr){};
                ReverseIterator(const ReverseIterator &s)           : Iter(s.Iter){};
                ReverseIterator(const ReverseIterator &&s) noexcept : Iter(s.Iter){};

                inline node<T> * getIter() { return Iter; };

                ReverseIterator       operator++              ();
                const ReverseIterator operator++              (int);
                ReverseIterator       operator--              ();
                const ReverseIterator operator--              (int);
                ReverseIterator &     operator=               (const ReverseIterator &source)       { this->Iter = source.Iter; return (*this); };
                ReverseIterator &     operator=               (ReverseIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
                bool                  operator==              (const ReverseIterator& source) const { return (Iter == source.Iter); };
                bool                  operator!=              (const ReverseIterator& source) const { return (Iter != source.Iter); };
                explicit              operator node<T>&       ()                                    { return (*Iter); };
                explicit              operator const node<T>& ()                              const { return (*Iter); };
                T &                   operator*               ()                              const { return (Iter->key); };
                node<T> *             operator->              ()                              const { return Iter; };
                explicit              operator bool           ()                              const { return (Iter != nullptr); };
        };

        class ConstIterator{
            protected:
                node<T> * Iter;

            public:
                friend class RBTree;
                typedef ConstIterator             self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ConstIterator()                                 : Iter(nullptr){};
                explicit ConstIterator(node<T>* ptr)            : Iter(ptr){};
                ConstIterator(const ConstIterator &s)           : Iter(s.Iter){};
                ConstIterator(const ConstIterator &&s) noexcept : Iter(s.Iter){};

                inline node<T> * getIter() { return Iter; };

                ConstIterator       operator++               ();
                const ConstIterator operator++               (int);
                ConstIterator       operator--               ();
                const ConstIterator operator--               (int);
                ConstIterator &     operator=                (const ConstIterator &source)       { this->Iter = source.Iter; return (*this); };
                ConstIterator &     operator=                (ConstIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
                bool                operator==               (const ConstIterator& source) const { return (Iter == source.Iter); };
                bool                operator!=               (const ConstIterator& source) const { return (Iter != source.Iter); };
                explicit            operator node<T> &       ()                                  { return (*Iter); };
                explicit            operator const node<T> & ()                            const { return (*Iter); };
                T const &           operator*                ()                            const { return (Iter->key); };
                node<T> const *     operator->               ()                            const { return Iter; };
                explicit            operator bool            ()                            const { return (Iter != nullptr); };
        };

        class ConstReverseIterator{
            protected:
                node<T> * Iter;

            public:
                friend class RBTree;
                typedef ConstReverseIterator      self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ConstReverseIterator()                                        : Iter(nullptr){};
                explicit ConstReverseIterator(node<T>* ptr)                   : Iter(ptr){};
                ConstReverseIterator(const ConstReverseIterator &s)           : Iter(s.Iter){};
                ConstReverseIterator(const ConstReverseIterator &&s) noexcept : Iter(s.Iter){};

                inline node<T> * getIter() { return Iter; };

                ConstReverseIterator       operator++              ();
                const ConstReverseIterator operator++              (int);
                ConstReverseIterator       operator--              ();
                const ConstReverseIterator operator--              (int);
                ConstReverseIterator &     operator=               (const ConstReverseIterator &source)       { this->Iter = source.Iter; return (*this); };
                ConstReverseIterator &     operator=               (ConstReverseIterator &&source)   noexcept { this->Iter = source.Iter; return (*this); };
                bool                       operator==              (const ConstReverseIterator& source) const { return (Iter == source.Iter); };
                bool                       operator!=              (const ConstReverseIterator& source) const { return (Iter != source.Iter); };
                explicit                   operator node<T>&       ()                                         { return (*Iter); };
                explicit                   operator const node<T>& ()                                   const { return (*Iter); };
                T const &                  operator*               ()                                   const { return (Iter->key); };
                node<T> const *            operator->              ()                                   const { return Iter; };
                explicit                   operator bool           ()                                   const { return (Iter != nullptr); };
        };

        /**
        * Constructors
        */
        RBTree()                             : size_(0), root(nullptr){};
        RBTree(const RBTree<T> &t)           : size_(0), root(nullptr){ Copy(t.root); };
        RBTree(const RBTree<T> &&t) noexcept : size_(0), root(nullptr){ Copy(t.root); };

        /**
        * Utility functions
        */
        inline node<T>* getRoot() const { return root; };
        inline size_t   size()          { return size_; };
        inline bool     isEmpty() const { return (root == nullptr && size_ == 0); };
        inline void     Display()       { Display(root, 0); };
        inline void     clear()         { size_ = 0; Chop(root); root = nullptr; };
        inline node<T>* maxIt()   const { return ( isEmpty() ? nullptr : root->max_node() ); };
        inline node<T>* minIt()   const { return ( isEmpty() ? nullptr : root->min_node() ); };
        inline void     Insert(T input);
        inline bool     T_find(T);
        inline node<T>* T_node_find(T);
        inline size_t   Black_hight();
        inline bool     Delete(T);

        /**
        * Operators
        */
        inline void     operator+ (const RBTree<T>& in)         { Merge(in.root); };
        inline void     operator- (const RBTree<T>& in)         { Split(in.root); };
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
        * Begin/End functions
        */
        Iterator             begin()   const { return Iterator( minIt() ); };
        Iterator             end()     const { return Iterator(); };
        ReverseIterator      rbegin()  const { return ReverseIterator( maxIt() ); };
        ReverseIterator      rend()    const { return ReverseIterator(); };
        ConstIterator        cbegin()  const { return ConstIterator( minIt() ); };
        ConstIterator        cend()    const { return ConstIterator(); };
        ConstReverseIterator crbegin() const { return ConstReverseIterator(maxIt()); };
        ConstReverseIterator crend()   const { return ConstReverseIterator(); };

    private:
        size_t   size_;
        node<T> *root;
};

template <typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(int){
    Iterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::Iterator RBTree<T>::Iterator::operator--(int){
    Iterator pom = *this;
    --(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator++(int){
    ReverseIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator--(int){
    ReverseIterator pom = *this;
    --(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ConstIterator RBTree<T>::ConstIterator::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ConstIterator RBTree<T>::ConstIterator::operator++(int){
    ConstIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ConstIterator RBTree<T>::ConstIterator::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ConstIterator RBTree<T>::ConstIterator::operator--(int){
    ConstIterator pom = *this;
    --(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ConstReverseIterator RBTree<T>::ConstReverseIterator::operator++(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Predecessor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ConstReverseIterator RBTree<T>::ConstReverseIterator::operator++(int){
    ConstReverseIterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::ConstReverseIterator RBTree<T>::ConstReverseIterator::operator--(){
    if(this->Iter != nullptr){
        this->Iter = this->Iter->node_Successor();

        return *this;
    }
    else return *this;
}

template <typename T>
const typename RBTree<T>::ConstReverseIterator RBTree<T>::ConstReverseIterator::operator--(int){
    ConstReverseIterator pom = *this;
    --(*this);

    return pom;
}

template <typename T>
inline void RBTree<T>::Copy(node<T> *in){
    if(in){
        Insert(in->key);
        Copy(in->left);
        Copy(in->right);
    }
}

template <typename T>
inline void RBTree<T>::Chop(node<T> *in){
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

        while(it != end() && tree_it != end()){
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
    if(size_ == tree.size_){
        auto it = begin();
        auto tree_it = tree.begin();

        while(it != end() && tree_it != end()){
            if(*it >= *tree_it) return false;
            else{
                ++it;
                ++tree_it;
            }
        }

        return true;
    }
    else{
        return (size_ < tree.size_);
    }
}

template <typename T>
bool RBTree<T>::operator>(const RBTree<T> &tree) const{
    if(size_ == tree.size_){
        auto it = begin();
        auto tree_it = tree.begin();

        while(it != end() && tree_it != end()){
            if(*it <= *tree_it) return false;
            else{
                ++it;
                ++tree_it;
            }
        }

        return true;
    }
    else{
        return (size_ > tree.size_);
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
inline void RBTree<T>::Insert(T input){
    node<T> *q;
    auto *create = new node<T>(input);
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
inline void RBTree<T>::Insert_fix(node<T> *create){
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
inline void RBTree<T>::Rotate_right(node<T>* in){
    if(in->left == nullptr) return;
    else{
        auto *y = in;
        auto *x = y->left;
        auto *b = x->right;
        auto *f = y->father;

        if(f == nullptr){
            x->father = nullptr;
            root = x;
        }
        else{
            x->father = f;

            if(f->left == y) f->left = x;
            if(f->right == y) f->right = x;
        }

        x->right = y;
        y->father = x;
        y->left = b;

        if( b != nullptr) b->father =y;
    }
}

template <typename T>
inline void RBTree<T>::Rotate_left(node<T>* x){
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
inline bool RBTree<T>::T_find(T in){
    auto *t = root;

    while(t != nullptr){
        if(t->key == in) return true;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    return false;
}

template<typename T>
node<T>* RBTree<T>::T_node_find(T in){
    auto *t = root;

    while(t != nullptr){
        if(t->key == in) return t;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    return nullptr;
}


template<typename T>
inline void RBTree<T>::Merge(node<T> *p ){
    if(p != nullptr){
        if(p->left) Merge(p->left);
        if(p->right) Merge(p->right);

        Insert(p->key);
    }
}

template<typename T>
inline void RBTree<T>::Split(node<T> *p ) {
    if(p != nullptr){
        if(p->left) Split(p->left);
        if(p->right) Split(p->right);

        Delete(p->key);
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
inline size_t RBTree<T>::Size(node<T> * in){
    if(in == nullptr) return 0;
    else{
        auto ls = Size(in->left);
        auto rs = Size(in->right);

        return (ls + rs + 1);
    }
}

template<typename T>
inline void RBTree<T>::Display(node<T>* in, size_t level){
    if(in == nullptr) return;

    std::cout << "level: " << level << std::endl;
    std::cout << in;

    Display(in->left, level+1);
    Display(in->right, level+1);
}

template <typename T>
inline bool RBTree<T>::Delete(T x){
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

        node<T> *y = nullptr;
        node<T> *q = nullptr;

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
inline void RBTree<T>::Delete_fix(node<T> *p){
    if(p != nullptr){
        node<T> *s;

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

#endif //_SIMPLE_RED_BLACK_TREE_HPP_
