#ifndef RBTREE_RB_TREE_HPP
#define RBTREE_RB_TREE_HPP

#pragma once

#include "rbt_iterator.hpp"
#include "rbt_reverse_iterator.hpp"
#include "rbt_const_iterator.hpp"
#include "rbt_const_reverse_iterator.hpp"
#include <initializer_list>
#include <vector>

namespace algo::ds::rbt {

    template <typename T>
    class RBTree {
    private:
        /**
            * Helper functions
        */
        size_t Size(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Display(algo::ds::rbt::node_impl::RBNode<T>*, size_t);
        void   Rotate_left(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Rotate_right(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Insert_fix(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Merge(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Split(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Delete_fix(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Copy(algo::ds::rbt::node_impl::RBNode<T>*);
        void   Chop(algo::ds::rbt::node_impl::RBNode<T>*);

    public:
        /**
        * Constructors
        */
        RBTree()                              : size_{ 0 }, root_{ nullptr } {};
        RBTree(const RBTree<T>& t)            : size_{ 0 }, root_{ nullptr } { Copy(t.root_); };
        RBTree(const RBTree<T>&& t) noexcept  : size_{ 0 }, root_{ nullptr } { Copy(t.root_); };
        RBTree(std::initializer_list<T> init) : size_{ 0 } { for (auto& e : init) { insert(e); } };
        template<typename InputIt>
        RBTree(InputIt first, InputIt last)   : size_{ 0 } { for (auto it = first; it != last; it++) { insert(*it); } };


        /**
            * Utility functions
        */
        algo::ds::rbt::node_impl::RBNode<T>*                   getRoot() const { return root_; };
        algo::ds::rbt::iterators::Iterator<T>                  root() { return algo::ds::rbt::iterators::Iterator<T>(root_); };
        algo::ds::rbt::iterators::ConstIterator<T>             root()    const { return algo::ds::rbt::iterators::ConstIterator<T>(root_); };
        algo::ds::rbt::iterators::ConstIterator<T>             croot()   const { return algo::ds::rbt::iterators::ConstIterator<T>(root_); };
        size_t                                                 size() { return size_; };
        [[nodiscard]] bool                                     isEmpty() const { return (root_ == nullptr && size_ == 0); };
        void                                                   display() { Display(root_, 0); };
        void                                                   clear() { size_ = 0; Chop(root_); root_ = nullptr; };
        algo::ds::rbt::node_impl::RBNode<T>*                   maxIt()   const { return (isEmpty() ? nullptr : root_->max_node()); };
        algo::ds::rbt::iterators::Iterator<T>                  maxIter() { return algo::ds::rbt::iterators::Iterator<T>(maxIt()); };
        algo::ds::rbt::node_impl::RBNode<T>*                   minIt()   const { return (isEmpty() ? nullptr : root_->min_node()); };
        algo::ds::rbt::iterators::Iterator<T>                  minIter() { return algo::ds::rbt::iterators::Iterator<T>(minIt()); };
        algo::ds::rbt::iterators::Iterator<T>                  insert(const T&);
        void                                                   insert(algo::ds::rbt::iterators::Iterator<T> first, algo::ds::rbt::iterators::Iterator<T> last);
        std::pair<algo::ds::rbt::iterators::Iterator<T>, bool> insert_unique(const T&);
        bool                                                   find(const T&);
        std::size_t                                            count(const T&);
        algo::ds::rbt::iterators::Iterator<T>                  iterator_to(const T&);
        algo::ds::rbt::iterators::ConstIterator<T>             iterator_to(const T&) const;
        algo::ds::rbt::node_impl::RBNode<T>*                   node_find(const T&);
        size_t                                                 Black_hight();
        void                                                   replace(const T&, const T&);
        bool                                                   remove(const T&);
        algo::ds::rbt::iterators::Iterator<T>                  erase(algo::ds::rbt::iterators::ConstIterator<T> pos);
        algo::ds::rbt::iterators::Iterator<T>                  erase(algo::ds::rbt::iterators::Iterator<T> pos);
        algo::ds::rbt::iterators::Iterator<T>                  erase(algo::ds::rbt::iterators::Iterator<T> first, algo::ds::rbt::iterators::Iterator<T> last);
        std::size_t                                            erase(const T&);
        void                                                   swap(RBTree<T>&) noexcept;
        void                                                   copy_from(const RBTree<T>& src);
        void                                                   copy_from(RBTree<T>&& src);
        std::pair<algo::ds::rbt::iterators::Iterator<T>, algo::ds::rbt::iterators::Iterator<T>>           bounded_range(const T& from, const T& to);
        std::pair<algo::ds::rbt::iterators::ConstIterator<T>, algo::ds::rbt::iterators::ConstIterator<T>> bounded_range(const T& from, const T& to) const;
        std::pair<algo::ds::rbt::iterators::Iterator<T>, algo::ds::rbt::iterators::Iterator<T>>           equal_range(const T& x);
        std::pair<algo::ds::rbt::iterators::ConstIterator<T>, algo::ds::rbt::iterators::ConstIterator<T>> equal_range(const T& x) const;
        algo::ds::rbt::iterators::Iterator<T>                  lower_bound(const T& x);
        algo::ds::rbt::iterators::ConstIterator<T>             lower_bound(const T& x) const;
        algo::ds::rbt::iterators::Iterator<T>                  upper_bound(const T& x);
        algo::ds::rbt::iterators::ConstIterator<T>             upper_bound(const T& x) const;

        /**
            * Operators
        */
        void     operator+ (const RBTree<T>& in)         { Merge(in.root_); };
        void     operator- (const RBTree<T>& in)         { Split(in.root_); };
        RBTree&  operator+=(const T& x)                  { insert(x); return *this; };
        RBTree&  operator-=(const T& x)                  { remove(x); return *this; };
        T        operator[](const size_t& id);
        const T  operator[](const size_t& id)      const;
        RBTree&  operator= (const RBTree<T>&);
        RBTree&  operator= (RBTree<T>&&)        noexcept;
        bool     operator==(const RBTree<T>&)      const;
        bool     operator!=(const RBTree<T>& tree) const { return !(*this == tree); };
        bool     operator< (const RBTree<T>& tree) const;
        bool     operator> (const RBTree<T>& tree) const { return tree < *this; };
        bool     operator<=(const RBTree<T>& tree) const { return !(*this > tree); };
        bool     operator>=(const RBTree<T>& tree) const { return !(*this < tree); };
        explicit operator bool()                   const { return !isEmpty(); };

        /**
            * Iterators
            * Begin/End functions
        */
        algo::ds::rbt::iterators::Iterator<T>             begin()         { return algo::ds::rbt::iterators::Iterator<T>(minIt()); };
        algo::ds::rbt::iterators::Iterator<T>             end()           { return algo::ds::rbt::iterators::Iterator<T>(); };
        algo::ds::rbt::iterators::ConstIterator<T>        begin()   const { return algo::ds::rbt::iterators::ConstIterator<T>(minIt()); };
        algo::ds::rbt::iterators::ConstIterator<T>        end()     const { return algo::ds::rbt::iterators::ConstIterator<T>(); };
        algo::ds::rbt::iterators::ReverseIterator<T>      rbegin()        { return algo::ds::rbt::iterators::ReverseIterator<T>(maxIt()); };
        algo::ds::rbt::iterators::ReverseIterator<T>      rend()          { return algo::ds::rbt::iterators::ReverseIterator<T>(); };
        algo::ds::rbt::iterators::ConstReverseIterator<T> rbegin()  const { return algo::ds::rbt::iterators::ConstReverseIterator<T>(maxIt()); };
        algo::ds::rbt::iterators::ConstReverseIterator<T> rend()    const { return algo::ds::rbt::iterators::ConstReverseIterator<T>(); };
        algo::ds::rbt::iterators::ConstIterator<T>        cbegin()  const { return algo::ds::rbt::iterators::ConstIterator<T>(minIt()); };
        algo::ds::rbt::iterators::ConstIterator<T>        cend()    const { return algo::ds::rbt::iterators::ConstIterator<T>(); };
        algo::ds::rbt::iterators::ConstReverseIterator<T> crbegin() const { return algo::ds::rbt::iterators::ConstReverseIterator<T>(maxIt()); };
        algo::ds::rbt::iterators::ConstReverseIterator<T> crend()   const { return algo::ds::rbt::iterators::ConstReverseIterator<T>(); };

    private:
        size_t                               size_;
        algo::ds::rbt::node_impl::RBNode<T>* root_;
    };

    template <typename T>
    inline void RBTree<T>::Copy(algo::ds::rbt::node_impl::RBNode<T>* in) {
        if (in) {
            insert(in->key);
            Copy(in->left);
            Copy(in->right);
        }
    }

    template <typename T>
    inline void RBTree<T>::Chop(algo::ds::rbt::node_impl::RBNode<T>* in) {
        if (in) {
            Chop(in->left);
            Chop(in->right);

            delete in;
        }
    }

    template <typename T>
    inline RBTree<T>& RBTree<T>::operator=(const RBTree<T>& tree) {
        if (this != &tree) {
            Chop(root_);
            root_ = nullptr;
            Copy(tree.root_);
        }

        return *this;
    }

    template <typename T>
    inline RBTree<T>& RBTree<T>::operator=(RBTree<T>&& tree) noexcept {
        if (this != &tree) {
            Chop(root_);
            root_ = nullptr;
            Copy(tree.root_);
        }

        return *this;
    }

    template<typename T>
    inline bool RBTree<T>::operator==(const RBTree<T>& tree) const {
        if (size_ != tree.size_ || root_ != tree.root_) return false;
        else {
            auto it = begin();
            auto tree_it = tree.begin();

            while (it != end() && tree_it != tree.end()) {
                if (*it != *tree_it) return false;
                else {
                    ++it;
                    ++tree_it;
                }
            }

            return true;
        }
    }

    template<typename T>
    inline bool RBTree<T>::operator<(const RBTree<T>& tree) const {
        if (size_ == tree.size_ && root_ < tree.root_) {
            auto it = begin();
            auto tree_it = tree.begin();

            while (it != end() && tree_it != tree.end()) {
                if (*it >= *tree_it) return false;
                else {
                    ++it;
                    ++tree_it;
                }
            }

            return true;
        }
        else {
            return (size_ < tree.size_&& root_ < tree.root_);
        }
    }

    template<typename T>
    inline T RBTree<T>::operator[](const size_t& id) {
        if (id < 0 || id >= size_) throw algo::ds::rbt::exception::TreeIndexOutOfBoundException();
        else {
            if (id == 0) return minIt()->key;

            auto count = 1;
            auto* n = minIt()->node_Successor();

            while (count++ != id) n = n->node_Successor();

            return n->key;
        }
    }

    template<typename T>
    inline const T RBTree<T>::operator[](const size_t& id) const {
        if (id < 0 || id >= size_) throw algo::ds::rbt::exception::TreeIndexOutOfBoundException();
        else {
            if (id == 0) return minIt()->key;

            auto count = 1;
            auto* n = minIt()->node_Successor();

            while (count++ != id) n = n->node_Successor();

            return n->key;
        }
    }

    template <typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::insert(const T& input) {
        algo::ds::rbt::node_impl::RBNode<T>* q;
        auto* create = new algo::ds::rbt::node_impl::RBNode<T>(input);
        auto p = root_;
        q = nullptr;

        if (root_ == nullptr) {
            root_ = create;
            create->father = nullptr;
        }
        else {
            while (p != nullptr) {
                q = p;

                if (p->key > create->key) p = p->left;
                else if (p->key < create->key) p = p->right;
                else return end();
            }

            create->father = q;

            if (q->key < create->key) q->right = create;
            else if (q->key > create->key) q->left = create;
            else return end();
        }

        size_++;
        Insert_fix(create);

        return iterator_to(input);
    }

    template<typename T>
    inline void RBTree<T>::Insert_fix(algo::ds::rbt::node_impl::RBNode<T>* create) {
        auto* x = create;

        while (x != root_ && x->father->color == algo::ds::rbt::node_impl::red) {
            if (x->father == x->father->father->left) {
                auto* y = x->father->father->right;

                if ((y != nullptr) && (y->color == algo::ds::rbt::node_impl::red)) {
                    x->father->color = algo::ds::rbt::node_impl::black;
                    y->color = algo::ds::rbt::node_impl::black;
                    x->father->father->color = algo::ds::rbt::node_impl::red;
                    x = x->father->father;
                }
                else {
                    if (x->father->right == x) {
                        x = x->father;
                        Rotate_left(x);
                    }

                    x->father->color = algo::ds::rbt::node_impl::black;
                    x->father->father->color = algo::ds::rbt::node_impl::red;
                    Rotate_right(x->father->father);
                }
            }
            else {
                auto* y = x->father->father->left;

                if ((y != nullptr) && (y->color == algo::ds::rbt::node_impl::red)) {
                    x->father->color = algo::ds::rbt::node_impl::black;
                    y->color = algo::ds::rbt::node_impl::black;
                    x->father->father->color = algo::ds::rbt::node_impl::red;
                    x = x->father->father;
                }
                else {
                    if (x->father->left == x) {
                        x = x->father;
                        Rotate_right(x);
                    }

                    x->father->color = algo::ds::rbt::node_impl::black;
                    x->father->father->color = algo::ds::rbt::node_impl::red;
                    Rotate_left(x->father->father);
                }
            }
        }

        root_->color = algo::ds::rbt::node_impl::black;
    }

    template<typename T>
    inline void RBTree<T>::Rotate_right(algo::ds::rbt::node_impl::RBNode<T>* in) {
        if (in->left == nullptr) return;
        else {
            auto* x = in->left;
            auto* b = x->right;
            auto* f = in->father;

            if (f == nullptr) {
                x->father = nullptr;
                root_ = x;
            }
            else {
                x->father = f;

                if (f->left == in) f->left = x;
                if (f->right == in) f->right = x;
            }

            x->right = in;
            in->father = x;
            in->left = b;

            if (b != nullptr) b->father = in;
        }
    }

    template <typename T>
    inline void RBTree<T>::Rotate_left(algo::ds::rbt::node_impl::RBNode<T>* x) {
        if (x->right == nullptr) return;
        else {
            auto* y = x->right;
            auto* b = y->left;
            auto* f = x->father;

            if (f == nullptr) {
                y->father = nullptr;
                root_ = y;
            }
            else {
                y->father = f;

                if (f->left == x) f->left = y;
                if (f->right == x) f->right = y;
            }

            y->left = x;
            x->father = y;
            x->right = b;

            if (b != nullptr) b->father = x;
        }
    }

    template <typename T>
    inline bool RBTree<T>::find(const T& in) {
        auto* t = root_;

        while (t != nullptr) {
            if (t->key == in) return true;
            if (in > t->key) t = t->right;
            else if (in < t->key) t = t->left;
        }

        return false;
    }

    template <typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::iterator_to(const T& x) {
        return algo::ds::rbt::iterators::Iterator<T>(node_find(x));
    }

    template <typename T>
    inline algo::ds::rbt::iterators::ConstIterator<T> RBTree<T>::iterator_to(const T& x) const {
        return algo::ds::rbt::iterators::ConstIterator<T>(node_find(x));
    }

    template<typename T>
    algo::ds::rbt::node_impl::RBNode<T>* RBTree<T>::node_find(const T& in) {
        auto* t = root_;

        while (t != nullptr) {
            if (t->key == in) return t;
            if (in > t->key) t = t->right;
            else if (in < t->key) t = t->left;
        }

        return nullptr;
    }

    template<typename T>
    inline void RBTree<T>::Merge(algo::ds::rbt::node_impl::RBNode<T>* p) {
        if (p != nullptr) {
            if (p->left) Merge(p->left);
            if (p->right) Merge(p->right);

            insert(p->key);
        }
    }

    template<typename T>
    inline void RBTree<T>::Split(algo::ds::rbt::node_impl::RBNode<T>* p) {
        if (p != nullptr) {
            if (p->left) Split(p->left);
            if (p->right) Split(p->right);

            remove(p->key);
        }
    }

    template<typename T>
    inline size_t RBTree<T>::Black_hight() {
        auto* p = root_;
        auto num = 0;

        while (p != nullptr) {
            if (p->color == algo::ds::rbt::node_impl::black) num++;

            p = p->left;
        }

        return num;
    }

    template<typename T>
    inline size_t RBTree<T>::Size(algo::ds::rbt::node_impl::RBNode<T>* in) {
        if (in == nullptr) return 0;
        else {
            auto ls = Size(in->left);
            auto rs = Size(in->right);

            return (ls + rs + 1);
        }
    }

    template<typename T>
    inline void RBTree<T>::Display(algo::ds::rbt::node_impl::RBNode<T>* in, size_t level) {
        if (in == nullptr) return;

        std::cout << "level: " << level << std::endl;
        std::cout << in;

        Display(in->left, level + 1);
        Display(in->right, level + 1);
    }

    template <typename T>
    inline bool RBTree<T>::remove(const T& x) {
        if (root_ == nullptr) {
            std::cout << "\nEmpty RBTree.";

            return false;
        }

        auto* p = root_;
        auto found = 0;

        while (p != nullptr && found == 0) {
            if (p->key == x) found = 1;
            if (found == 0) {
                if (p->key < x) p = p->right;
                else p = p->left;
            }
        }

        if (found == 0) return false;
        else {
            //std::cout << "Deleted Element: " << p->key << " Colour: " << (p->color == black ? "Black" : "Red" ) << "   SIZE: " << size_-1 << std::endl;

            algo::ds::rbt::node_impl::RBNode<T>* y = nullptr;
            algo::ds::rbt::node_impl::RBNode<T>* q = nullptr;

            if (p->left == nullptr || p->right == nullptr) y = p;
            else y = p->node_Successor();

            if (y->left != nullptr) q = y->left;
            else {
                if (y->right != nullptr) q = y->right;
                else q = nullptr;
            }

            if (q != nullptr) q->father = y->father;

            if (y->father == nullptr) root_ = q;
            else {
                if (y == y->father->left) y->father->left = q;
                else y->father->right = q;
            }

            if (y != p) {
                p->color = y->color;
                p->key = y->key;
            }

            if (y->color == algo::ds::rbt::node_impl::black) Delete_fix(q);

            size_--;

            return true;
        }
    }

    template <typename T>
    inline void RBTree<T>::Delete_fix(algo::ds::rbt::node_impl::RBNode<T>* p) {
        if (p != nullptr) {
            algo::ds::rbt::node_impl::RBNode<T>* s;

            while (p != root_ && p->color == algo::ds::rbt::node_impl::black) {
                if (p->father->left == p) {
                    s = p->father->right;

                    if (s->color == algo::ds::rbt::node_impl::red) {
                        s->color = algo::ds::rbt::node_impl::black;
                        p->father->color = algo::ds::rbt::node_impl::red;
                        Rotate_left(p->father);
                        s = p->father->right;
                    }
                    if (s->right->color == algo::ds::rbt::node_impl::black && s->left->color == algo::ds::rbt::node_impl::black) {
                        s->color = algo::ds::rbt::node_impl::red;
                        p = p->father;
                    }
                    else {
                        if (s->right->color == algo::ds::rbt::node_impl::black) {
                            s->left->color = algo::ds::rbt::node_impl::black;
                            s->color = algo::ds::rbt::node_impl::red;
                            Rotate_right(s);
                            s = p->father->right;
                        }

                        s->color = p->father->color;
                        p->father->color = algo::ds::rbt::node_impl::black;
                        s->right->color = algo::ds::rbt::node_impl::black;
                        Rotate_left(p->father);
                        p = root_;
                    }
                }
                else {
                    s = p->father->left;

                    if (s->color == algo::ds::rbt::node_impl::red) {
                        s->color = algo::ds::rbt::node_impl::red;
                        p->father->color = algo::ds::rbt::node_impl::red;
                        Rotate_right(p->father);
                        s = p->father->left;
                    }
                    if (s->left->color == algo::ds::rbt::node_impl::black && s->right->color == algo::ds::rbt::node_impl::black) {
                        s->color = algo::ds::rbt::node_impl::red;
                        p = p->father;
                    }
                    else {
                        if (s->left->color == algo::ds::rbt::node_impl::black) {
                            s->right->color = algo::ds::rbt::node_impl::black;
                            s->color = algo::ds::rbt::node_impl::red;
                            Rotate_left(s);
                            s = p->father->left;
                        }

                        s->color = p->father->color;
                        p->father->color = algo::ds::rbt::node_impl::black;
                        s->left->color = algo::ds::rbt::node_impl::black;
                        Rotate_right(p->father);
                        p = root_;
                    }
                }

                p->color = algo::ds::rbt::node_impl::black;
                root_->color = algo::ds::rbt::node_impl::black;
            }
        }
    }

    template<typename T>
    inline std::pair<algo::ds::rbt::iterators::Iterator<T>, algo::ds::rbt::iterators::Iterator<T>> RBTree<T>::bounded_range(const T& from, const T& to) {
        if (from <= to) {
            algo::ds::rbt::iterators::Iterator<T> f_;
            algo::ds::rbt::iterators::Iterator<T> t_;

            for (auto it = begin(); it != end(); ++it) {
                if (!f_ && *it == from) {
                    f_ = it;
                }
                if (!t_ && *it == to) {
                    t_ = it;
                }
                if (f_ && t_) {
                    break;
                }
            }

            return { f_ ? f_ : end(), t_ ? t_ : end() };
        }
        else {
            return { end(), end() };
        }
    }

    template<typename T>
    inline std::pair<algo::ds::rbt::iterators::ConstIterator<T>, algo::ds::rbt::iterators::ConstIterator<T>> RBTree<T>::bounded_range(const T& from, const T& to) const {
        if (from <= to) {
            algo::ds::rbt::iterators::ConstIterator<T> f_;
            algo::ds::rbt::iterators::ConstIterator<T> t_;

            for (const auto it = cbegin(); it != cend(); ++it) {
                if (!f_ && *it == from) {
                    f_ = it;
                }
                if (!t_ && *it == to) {
                    t_ = it;
                }
                if (f_ && t_) {
                    break;
                }
            }

            return { f_ ? f_ : cend(), t_ ? t_ : cend() };
        }
        else {
            return { cend(), cend() };
        }
    }

    template<typename T>
    inline std::pair<algo::ds::rbt::iterators::Iterator<T>, algo::ds::rbt::iterators::Iterator<T>> RBTree<T>::equal_range(const T& x) {
        return { lower_bound(x), upper_bound(x) };
    }

    template<typename T>
    inline std::pair<algo::ds::rbt::iterators::ConstIterator<T>, algo::ds::rbt::iterators::ConstIterator<T>> RBTree<T>::equal_range(const T& x) const {
        return { lower_bound(x), upper_bound(x) };
    }

    template<typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::lower_bound(const T& x) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it >= x) {
                return it;
            }
        }

        return end();
    }

    template<typename T>
    inline algo::ds::rbt::iterators::ConstIterator<T> RBTree<T>::lower_bound(const T& x) const {
        for (const auto it = cbegin(); it != cend(); ++it) {
            if (*it >= x) {
                return it;
            }
        }

        return cend();
    }

    template<typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::upper_bound(const T& x) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it > x) {
                return it;
            }
        }

        return end();
    }

    template<typename T>
    inline algo::ds::rbt::iterators::ConstIterator<T> RBTree<T>::upper_bound(const T& x) const {
        for (const auto it = cbegin(); it != cend(); ++it) {
            if (*it > x) {
                return it;
            }
        }

        return cend();
    }

    template<typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::erase(algo::ds::rbt::iterators::ConstIterator<T> pos) {
        auto ret = algo::ds::rbt::iterators::Iterator<T>(pos.getIter());
        ++ret;
        remove(*pos);

        return ret;
    }

    template<typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::erase(algo::ds::rbt::iterators::Iterator<T> pos) {
        auto ret = pos;
        ++ret;
        remove(*pos);

        return ret;
    }

    template<typename T>
    inline algo::ds::rbt::iterators::Iterator<T> RBTree<T>::erase(algo::ds::rbt::iterators::Iterator<T> first, algo::ds::rbt::iterators::Iterator<T> last) {
        auto ret = last;

        if (ret != end()) {
            ++ret;
        }

        std::vector<T> remover;
        for (auto it = first; it != last; ++it) {
            remover.push_back(*it);
        }

        for (auto& e : remover) {
            remove(e);
        }

        return ret;
    }

    template<typename T>
    inline std::size_t RBTree<T>::erase(const T& key) {
        std::size_t count = 0;

        while (find(key)) {
            remove(key);
            count++;
        }

        return count;
    }

    template<typename T>
    inline void RBTree<T>::swap(RBTree<T>& other) noexcept {
        std::vector<T> swaper;

        for (auto it = other.begin(); it != other.end(); ++it) {
            swaper.push_back(*it);
        }

        other.clear();
        other.insert(begin(), end());
        clear();

        for (auto& e : swaper) {
            insert(e);
        }
    }

    template<typename T>
    inline void RBTree<T>::insert(algo::ds::rbt::iterators::Iterator<T> first, algo::ds::rbt::iterators::Iterator<T> last) {
        for (auto it = first; it != last; ++it) {
            insert(*it);
        }
    }

    template<typename T>
    inline std::size_t RBTree<T>::count(const T& key) {
        std::size_t count = 0;

        for (auto it = begin(); it != end(); ++it) {
            if (*it == key) {
                count++;
            }
        }

        return count;
    }

    template<typename T>
    inline void RBTree<T>::copy_from(const RBTree<T>& src) {
        clear();

        for (auto& e : src) {
            insert(e);
        }
    }

    template<typename T>
    void RBTree<T>::copy_from(RBTree<T>&& src) {
        clear();

        for (auto& e : src) {
            insert(e);
        }
    }

    template<typename T>
    std::pair<algo::ds::rbt::iterators::Iterator<T>, bool> RBTree<T>::insert_unique(const T& val) {
        auto check = size();
        insert(val);

        if (check == size()) {
            return { iterator_to(val), false };
        }
        else {
            for (auto it = begin(); it != end(); ++it) {
                if (*it == val) {
                    return { it, true };
                }
            }

            throw algo::ds::rbt::exception::TreeInsertionFailedException();
        }
    }

    template<typename T>
    void RBTree<T>::replace(const T& replace_this, const T& with_this) {
        auto* check = node_find(replace_this);

        if (check) {
            if (check->father == nullptr) {
                if (check->left != nullptr) {
                    if (with_this <= check->left->key) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right != nullptr) {
                    if (with_this >= check->right) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }
            else if (check->is_left_son()) {
                if (with_this >= check->father->key) {
                    throw algo::ds::rbt::exception::TreeReplaceException();
                }
                if (check->left) {
                    if (with_this <= check->left->key) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right) {
                    if (with_this >= check->left->key) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }
            else {
                if (with_this <= check->father->key) {
                    throw algo::ds::rbt::exception::TreeReplaceException();
                }
                if (check->left) {
                    if (with_this <= check->left->key) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right) {
                    if (with_this >= check->left->key) {
                        throw algo::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }

            check->key = with_this;
        }
    }

}

#endif
