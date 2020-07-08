#ifndef RBTREE_RB_TREE_HPP
#define RBTREE_RB_TREE_HPP

#pragma once

#include "rbt_iterator.hpp"
#include "rbt_reverse_iterator.hpp"
#include "rbt_const_iterator.hpp"
#include "rbt_const_reverse_iterator.hpp"
#include <initializer_list>
#include <vector>

namespace ads::ds::rbt {

    template <typename T>
    class RBTree {
    public:
        typedef T                                                key_t;
        typedef T&                                               key_ref_t;
        typedef ads::ds::rbt::node_impl::RBNode<T>               node_t;
        typedef ads::ds::rbt::node_impl::RBNode<T>*              node_ptr_t;
        typedef ads::ds::rbt::node_impl::RBNode<T>&              node_ref_t;
        typedef ads::ds::rbt::node_impl::RBNode<T>&&             node_rval_t;
        typedef RBTree<T>                                        self_type;
        typedef RBTree<T>*                                       pointer_t;
        typedef RBTree<T>&                                       reference_t;
        typedef RBTree<T>&&                                      rvalue_t;
        typedef ads::ds::rbt::iterators::Iterator<T>             iterator;
        typedef ads::ds::rbt::iterators::ConstIterator<T>        const_iterator;
        typedef ads::ds::rbt::iterators::ReverseIterator<T>      reverse_iterator;
        typedef ads::ds::rbt::iterators::ConstReverseIterator<T> creverse_iterator;

    private:
        /**
            * Helper functions
        */
        size_t Size(node_ptr_t);
        void   Display(node_ptr_t, size_t);
        void   Rotate_left(node_ptr_t);
        void   Rotate_right(node_ptr_t);
        void   Insert_fix(node_ptr_t);
        void   Merge(node_ptr_t);
        void   Split(node_ptr_t);
        void   Delete_fix(node_ptr_t);
        void   Copy(node_ptr_t);
        void   Chop(node_ptr_t);

    public:
        /**
        * Constructors
        */
        RBTree()                              : size_{ 0 }, root_{ nullptr } {};
        RBTree(const reference_t t)           : size_{ 0 }, root_{ nullptr } { Copy(t.root_); };
        RBTree(rvalue_t t) noexcept           : size_{ 0 }, root_{ nullptr } { Copy(t.root_); };
        RBTree(std::initializer_list<T> init) : size_{ 0 } { for (auto& e : init) { insert(e); } };
        template<typename InputIt>
        RBTree(InputIt first, InputIt last)   : size_{ 0 } { for (auto it = first; it != last; it++) { insert(*it); } };

        /**
            * Utility functions
        */
        node_ptr_t                                getRoot() const { return root_; };
        iterator                                  root() { return iterator(root_); };
        const_iterator                            root()    const { return const_iterator(root_); };
        const_iterator                            croot()   const { return const_iterator(root_); };
        size_t                                    size() { return size_; };
        [[nodiscard]] bool                        isEmpty() const { return (root_ == nullptr && size_ == 0); };
        void                                      display() { Display(root_, 0); };
        void                                      clear() { size_ = 0; Chop(root_); root_ = nullptr; };
        node_ptr_t                                maxIt()   const { return (isEmpty() ? nullptr : root_->max_node()); };
        iterator                                  maxIter() { return iterator(maxIt()); };
        node_ptr_t                                minIt()   const { return (isEmpty() ? nullptr : root_->min_node()); };
        iterator                                  minIter() { return iterator(minIt()); };
        iterator                                  insert(const key_ref_t);
        void                                      insert(iterator first, iterator last);
        std::pair<iterator, bool>                 insert_unique(const key_ref_t);
        bool                                      find(const key_ref_t);
        std::size_t                               count(const key_ref_t);
        iterator                                  iterator_to(const key_ref_t);
        const_iterator                            iterator_to(const key_ref_t) const;
        node_ptr_t                                node_find(const key_ref_t);
        size_t                                    Black_hight();
        void                                      replace(const key_ref_t, const key_ref_t);
        bool                                      remove(const key_ref_t);
        iterator                                  erase(const_iterator pos);
        iterator                                  erase(iterator pos);
        iterator                                  erase(iterator first, iterator last);
        std::size_t                               erase(const key_ref_t);
        void                                      swap(reference_t) noexcept;
        void                                      copy_from(const reference_t src);
        void                                      copy_from(rvalue_t src);
        std::pair<iterator, iterator>             bounded_range(const key_ref_t from, const key_ref_t to);
        std::pair<const_iterator, const_iterator> bounded_range(const key_ref_t from, const key_ref_t to) const;
        std::pair<iterator, iterator>             equal_range(const key_ref_t x);
        std::pair<const_iterator, const_iterator> equal_range(const key_ref_t x) const;
        iterator                                  lower_bound(const key_ref_t x);
        const_iterator                            lower_bound(const key_ref_t x) const;
        iterator                                  upper_bound(const key_ref_t x);
        const_iterator                            upper_bound(const key_ref_t x) const;

        /*
        * Ostream overloading
        */
        friend std::ostream& operator<<(std::ostream& ofs, const RBTree<T>& tree) {
            for (auto it = tree.cbegin(); it != tree.cend(); ++it) {
                ofs << *it << ", ";
            }

            ofs << "\n";

            return ofs;
        }

        friend std::ostream& operator<<(std::ostream& ofs, const pointer_t tree) {
            for (auto it = tree->cbegin(); it != tree->cend(); ++it) {
                ofs << *it << ", ";
            }

            ofs << "\n";

            return ofs;
        }

        /**
            * Operators
        */
        void        operator+ (const reference_t in)         { Merge(in.root_); };
        void        operator- (const reference_t in)         { Split(in.root_); };
        reference_t operator+=(const key_ref_t x)            { insert(x); return *this; };
        reference_t operator-=(const key_ref_t x)            { remove(x); return *this; };
        key_t       operator[](const size_t& id);
        const key_t operator[](const size_t& id)       const;
        reference_t operator= (const reference_t);
        reference_t operator= (rvalue_t)               noexcept;
        bool        operator==(const reference_t)      const;
        bool        operator!=(const reference_t tree) const { return !(*this == tree); };
        bool        operator< (const reference_t tree) const;
        bool        operator> (const reference_t tree) const { return tree < *this; };
        bool        operator<=(const reference_t tree) const { return !(*this > tree); };
        bool        operator>=(const reference_t tree) const { return !(*this < tree); };
        explicit    operator bool()                    const { return !isEmpty(); };

        /**
            * Iterators
            * Begin/End functions
        */
        iterator          begin()         noexcept { return iterator(minIt()); };
        iterator          end()           noexcept { return iterator(); };
        const_iterator    begin()   const noexcept { return const_iterator(minIt()); };
        const_iterator    end()     const noexcept { return const_iterator(); };
        reverse_iterator  rbegin()        noexcept { return reverse_iterator(maxIt()); };
        reverse_iterator  rend()          noexcept { return reverse_iterator(); };
        creverse_iterator rbegin()  const noexcept { return creverse_iterator(maxIt()); };
        creverse_iterator rend()    const noexcept { return creverse_iterator(); };
        const_iterator    cbegin()  const noexcept { return const_iterator(minIt()); };
        const_iterator    cend()    const noexcept { return const_iterator(); };
        creverse_iterator crbegin() const noexcept { return creverse_iterator(maxIt()); };
        creverse_iterator crend()   const noexcept { return creverse_iterator(); };

    private:
        size_t                               size_;
        node_ptr_t root_;
    };

    template <typename T>
    inline void RBTree<T>::Copy(node_ptr_t in) {
        if (in) {
            insert(in->key);
            Copy(in->left);
            Copy(in->right);
        }
    }

    template <typename T>
    inline void RBTree<T>::Chop(node_ptr_t in) {
        if (in) {
            Chop(in->left);
            Chop(in->right);

            delete in;
        }
    }

    template <typename T>
    inline typename RBTree<T>::reference_t RBTree<T>::operator=(const reference_t tree) {
        if (this != &tree) {
            Chop(root_);
            root_ = nullptr;
            Copy(tree.root_);
        }

        return *this;
    }

    template <typename T>
    inline typename RBTree<T>::reference_t RBTree<T>::operator=(rvalue_t tree) noexcept {
        if (this != &tree) {
            Chop(root_);
            root_ = nullptr;
            Copy(tree.root_);
        }

        return *this;
    }

    template<typename T>
    inline bool RBTree<T>::operator==(const reference_t tree) const {
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
    inline bool RBTree<T>::operator<(const reference_t tree) const {
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
        if (id < 0 || id >= size_) throw ads::ds::rbt::exception::TreeIndexOutOfBoundException();
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
        if (id < 0 || id >= size_) throw ads::ds::rbt::exception::TreeIndexOutOfBoundException();
        else {
            if (id == 0) return minIt()->key;

            auto count = 1;
            auto* n = minIt()->node_Successor();

            while (count++ != id) n = n->node_Successor();

            return n->key;
        }
    }

    template <typename T>
    inline typename RBTree<T>::iterator RBTree<T>::insert(const key_ref_t input) {
        node_ptr_t q;
        auto* create = new ads::ds::rbt::node_impl::RBNode<T>(input);
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
    inline void RBTree<T>::Insert_fix(node_ptr_t create) {
        auto* x = create;

        while (x != root_ && x->father->color == ads::ds::rbt::node_impl::red) {
            if (x->father == x->father->father->left) {
                auto* y = x->father->father->right;

                if ((y != nullptr) && (y->color == ads::ds::rbt::node_impl::red)) {
                    x->father->color = ads::ds::rbt::node_impl::black;
                    y->color = ads::ds::rbt::node_impl::black;
                    x->father->father->color = ads::ds::rbt::node_impl::red;
                    x = x->father->father;
                }
                else {
                    if (x->father->right == x) {
                        x = x->father;
                        Rotate_left(x);
                    }

                    x->father->color = ads::ds::rbt::node_impl::black;
                    x->father->father->color = ads::ds::rbt::node_impl::red;
                    Rotate_right(x->father->father);
                }
            }
            else {
                auto* y = x->father->father->left;

                if ((y != nullptr) && (y->color == ads::ds::rbt::node_impl::red)) {
                    x->father->color = ads::ds::rbt::node_impl::black;
                    y->color = ads::ds::rbt::node_impl::black;
                    x->father->father->color = ads::ds::rbt::node_impl::red;
                    x = x->father->father;
                }
                else {
                    if (x->father->left == x) {
                        x = x->father;
                        Rotate_right(x);
                    }

                    x->father->color = ads::ds::rbt::node_impl::black;
                    x->father->father->color = ads::ds::rbt::node_impl::red;
                    Rotate_left(x->father->father);
                }
            }
        }

        root_->color = ads::ds::rbt::node_impl::black;
    }

    template<typename T>
    inline void RBTree<T>::Rotate_right(node_ptr_t in) {
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
    inline void RBTree<T>::Rotate_left(node_ptr_t x) {
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
    inline bool RBTree<T>::find(const key_ref_t in) {
        auto* t = root_;

        while (t != nullptr) {
            if (t->key == in) return true;
            if (in > t->key) t = t->right;
            else if (in < t->key) t = t->left;
        }

        return false;
    }

    template <typename T>
    inline typename RBTree<T>::iterator RBTree<T>::iterator_to(const key_ref_t x) {
        return iterator(node_find(x));
    }

    template <typename T>
    inline typename RBTree<T>::const_iterator RBTree<T>::iterator_to(const key_ref_t x) const {
        return const_iterator(node_find(x));
    }

    template<typename T>
    typename RBTree<T>::node_ptr_t RBTree<T>::node_find(const key_ref_t in) {
        auto* t = root_;

        while (t != nullptr) {
            if (t->key == in) return t;
            if (in > t->key) t = t->right;
            else if (in < t->key) t = t->left;
        }

        return nullptr;
    }

    template<typename T>
    inline void RBTree<T>::Merge(node_ptr_t p) {
        if (p != nullptr) {
            if (p->left) Merge(p->left);
            if (p->right) Merge(p->right);

            insert(p->key);
        }
    }

    template<typename T>
    inline void RBTree<T>::Split(node_ptr_t p) {
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
            if (p->color == ads::ds::rbt::node_impl::black) num++;

            p = p->left;
        }

        return num;
    }

    template<typename T>
    inline size_t RBTree<T>::Size(node_ptr_t in) {
        if (in == nullptr) return 0;
        else {
            auto ls = Size(in->left);
            auto rs = Size(in->right);

            return (ls + rs + 1);
        }
    }

    template<typename T>
    inline void RBTree<T>::Display(node_ptr_t in, size_t level) {
        if (in == nullptr) return;

        std::cout << "level: " << level << std::endl;
        std::cout << in;

        Display(in->left, level + 1);
        Display(in->right, level + 1);
    }

    template <typename T>
    inline bool RBTree<T>::remove(const key_ref_t x) {
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

            node_ptr_t y = nullptr;
            node_ptr_t q = nullptr;

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

            if (y->color == ads::ds::rbt::node_impl::black) Delete_fix(q);

            size_--;

            return true;
        }
    }

    template <typename T>
    inline void RBTree<T>::Delete_fix(node_ptr_t p) {
        if (p != nullptr) {
            node_ptr_t s;

            while (p != root_ && p->color == ads::ds::rbt::node_impl::black) {
                if (p->father->left == p) {
                    s = p->father->right;

                    if (s->color == ads::ds::rbt::node_impl::red) {
                        s->color = ads::ds::rbt::node_impl::black;
                        p->father->color = ads::ds::rbt::node_impl::red;
                        Rotate_left(p->father);
                        s = p->father->right;
                    }
                    if (s->right->color == ads::ds::rbt::node_impl::black && s->left->color == ads::ds::rbt::node_impl::black) {
                        s->color = ads::ds::rbt::node_impl::red;
                        p = p->father;
                    }
                    else {
                        if (s->right->color == ads::ds::rbt::node_impl::black) {
                            s->left->color = ads::ds::rbt::node_impl::black;
                            s->color = ads::ds::rbt::node_impl::red;
                            Rotate_right(s);
                            s = p->father->right;
                        }

                        s->color = p->father->color;
                        p->father->color = ads::ds::rbt::node_impl::black;
                        s->right->color = ads::ds::rbt::node_impl::black;
                        Rotate_left(p->father);
                        p = root_;
                    }
                }
                else {
                    s = p->father->left;

                    if (s->color == ads::ds::rbt::node_impl::red) {
                        s->color = ads::ds::rbt::node_impl::red;
                        p->father->color = ads::ds::rbt::node_impl::red;
                        Rotate_right(p->father);
                        s = p->father->left;
                    }
                    if (s->left->color == ads::ds::rbt::node_impl::black && s->right->color == ads::ds::rbt::node_impl::black) {
                        s->color = ads::ds::rbt::node_impl::red;
                        p = p->father;
                    }
                    else {
                        if (s->left->color == ads::ds::rbt::node_impl::black) {
                            s->right->color = ads::ds::rbt::node_impl::black;
                            s->color = ads::ds::rbt::node_impl::red;
                            Rotate_left(s);
                            s = p->father->left;
                        }

                        s->color = p->father->color;
                        p->father->color = ads::ds::rbt::node_impl::black;
                        s->left->color = ads::ds::rbt::node_impl::black;
                        Rotate_right(p->father);
                        p = root_;
                    }
                }

                p->color = ads::ds::rbt::node_impl::black;
                root_->color = ads::ds::rbt::node_impl::black;
            }
        }
    }

    template<typename T>
    inline std::pair<typename RBTree<T>::iterator, typename RBTree<T>::iterator> RBTree<T>::bounded_range(const key_ref_t from, const key_ref_t to) {
        if (from <= to) {
            iterator f_;
            iterator t_;

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
    inline std::pair<typename RBTree<T>::const_iterator, typename RBTree<T>::const_iterator> RBTree<T>::bounded_range(const key_ref_t from, const key_ref_t to) const {
        if (from <= to) {
            const_iterator f_;
            const_iterator t_;

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
    inline std::pair<typename RBTree<T>::iterator, typename RBTree<T>::iterator> RBTree<T>::equal_range(const key_ref_t x) {
        return { lower_bound(x), upper_bound(x) };
    }

    template<typename T>
    inline std::pair<typename RBTree<T>::const_iterator, typename RBTree<T>::const_iterator> RBTree<T>::equal_range(const key_ref_t x) const {
        return { lower_bound(x), upper_bound(x) };
    }

    template<typename T>
    inline typename RBTree<T>::iterator RBTree<T>::lower_bound(const key_ref_t x) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it >= x) {
                return it;
            }
        }

        return end();
    }

    template<typename T>
    inline typename RBTree<T>::const_iterator RBTree<T>::lower_bound(const key_ref_t x) const {
        for (const auto it = cbegin(); it != cend(); ++it) {
            if (*it >= x) {
                return it;
            }
        }

        return cend();
    }

    template<typename T>
    inline typename RBTree<T>::iterator RBTree<T>::upper_bound(const key_ref_t x) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it > x) {
                return it;
            }
        }

        return end();
    }

    template<typename T>
    inline typename RBTree<T>::const_iterator RBTree<T>::upper_bound(const key_ref_t x) const {
        for (const auto it = cbegin(); it != cend(); ++it) {
            if (*it > x) {
                return it;
            }
        }

        return cend();
    }

    template<typename T>
    inline typename RBTree<T>::iterator RBTree<T>::erase(const_iterator pos) {
        auto ret = iterator(pos.getIter());
        ++ret;
        remove(*pos);

        return ret;
    }

    template<typename T>
    inline typename RBTree<T>::iterator RBTree<T>::erase(iterator pos) {
        auto ret = pos;
        ++ret;
        remove(*pos);

        return ret;
    }

    template<typename T>
    inline typename RBTree<T>::iterator RBTree<T>::erase(iterator first, iterator last) {
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
    inline std::size_t RBTree<T>::erase(const key_ref_t key) {
        std::size_t count = 0;

        while (find(key)) {
            remove(key);
            count++;
        }

        return count;
    }

    template<typename T>
    inline void RBTree<T>::swap(reference_t other) noexcept {
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
    inline void RBTree<T>::insert(iterator first, iterator last) {
        for (auto it = first; it != last; ++it) {
            insert(*it);
        }
    }

    template<typename T>
    inline std::size_t RBTree<T>::count(const key_ref_t key) {
        std::size_t count = 0;

        for (auto it = begin(); it != end(); ++it) {
            if (*it == key) {
                count++;
            }
        }

        return count;
    }

    template<typename T>
    inline void RBTree<T>::copy_from(const reference_t src) {
        clear();

        for (auto& e : src) {
            insert(e);
        }
    }

    template<typename T>
    inline void RBTree<T>::copy_from(rvalue_t src) {
        clear();

        for (auto& e : src) {
            insert(e);
        }
    }

    template<typename T>
    inline std::pair<typename RBTree<T>::iterator, bool> RBTree<T>::insert_unique(const key_ref_t val) {
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

            throw ads::ds::rbt::exception::TreeInsertionFailedException();
        }
    }

    template<typename T>
    inline void RBTree<T>::replace(const key_ref_t replace_this, const key_ref_t with_this) {
        auto* check = node_find(replace_this);

        if (check) {
            if (check->father == nullptr) {
                if (check->left != nullptr) {
                    if (with_this <= check->left->key) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right != nullptr) {
                    if (with_this >= check->right) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }
            else if (check->is_left_son()) {
                if (with_this >= check->father->key) {
                    throw ads::ds::rbt::exception::TreeReplaceException();
                }
                if (check->left) {
                    if (with_this <= check->left->key) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right) {
                    if (with_this >= check->left->key) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }
            else {
                if (with_this <= check->father->key) {
                    throw ads::ds::rbt::exception::TreeReplaceException();
                }
                if (check->left) {
                    if (with_this <= check->left->key) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
                if (check->right) {
                    if (with_this >= check->left->key) {
                        throw ads::ds::rbt::exception::TreeReplaceException();
                    }
                }
            }

            check->key = with_this;
        }
    }

}

#endif
