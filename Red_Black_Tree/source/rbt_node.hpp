#ifndef RBTREE_RBT_NODE_HPP
#define RBTREE_RBT_NODE_HPP

#pragma once

#include <iostream>
#include <iterator>
#include <utility>
#include "exceptions.hpp"

namespace algo::ds::rbt::node_impl {

    enum colors { red, black };

    template <typename T>
    class RBNode {
    public:
        T     key;
        RBNode* father;
        RBNode* left;
        RBNode* right;
        int   color;

        RBNode() : father{ nullptr }, left{ nullptr }, right{ nullptr }, color{ black } {};
        explicit RBNode(T input) : key{ input }, father{ nullptr }, left{ nullptr }, right{ nullptr }, color{ red } {};
        RBNode(const RBNode& s) : key{ s.key }, father{ s.father }, left{ s.left }, right{ s.right }, color{ s.color } {};
        RBNode(RBNode&& s) noexcept : key{ s.key }, father{ s.father }, left{ s.left }, right{ s.right }, color{ s.color } {};
        RBNode(T input, RBNode* father_) : key{ input }, father{ father_ }, left{ nullptr }, right{ nullptr }, color{ red } {};
        RBNode(T input, RBNode* father_, int new_color) : key{ input }, father{ father_ }, left{ nullptr }, right{ nullptr }, color{ new_color } {};
        ~RBNode() = default;

        RBNode& operator= (const T& input)             { key = input; return *this; };
        RBNode& operator= (const RBNode<T>& input);
        RBNode& operator= (RBNode<T>&& input) noexcept;
        bool    operator==(const T& input)       const { return key == input; };
        bool    operator!=(const T& input)       const { return key != input; };
        bool    operator> (const T& input)       const { return key > input; };
        bool    operator< (const T& input)       const { return key < input; };
        bool    operator>=(const T& input)       const { return key >= input; };
        bool    operator<=(const T& input)       const { return key <= input; };
        bool    operator==(const RBNode& source) const { return ((key == source.key) && (father == source.father)); };
        bool    operator!=(const RBNode& source) const { return (!(*this == source)); };
        bool    operator> (const RBNode& source) const { return key > source.key; };
        bool    operator< (const RBNode& source) const { return key < source.key; };
        bool    operator>=(const RBNode& source) const { return key >= source.key; };
        bool    operator<=(const RBNode& source) const { return key <= source.key; };
        explicit operator bool()                 const { return (father != nullptr ? true : (left != nullptr ? true : right != nullptr)); };
        T       operator[](const size_t& id);
        T       operator[](const size_t& id) const;

        friend std::ostream& operator<<(std::ostream& ofs, const RBNode<T>* pt) {
            ofs << "Key: " << pt->key << ", color: " << (pt->color == black ? "B" : "R") << "\n";
            if (pt->father != nullptr) ofs << "(Father) key: " << pt->father->key << ", color: " << (pt->father->color == black ? "B" : "R") << "\n";
            else ofs << "No father (root)" << "\n";
            if (pt->left != nullptr) ofs << "(Left son) key: " << pt->left->key << ", color: " << (pt->left->color == black ? "B" : "R") << "\n";
            else ofs << "(No left son)" << "\n";
            if (pt->right != nullptr) ofs << "(Right son) key: " << pt->right->key << ", color: " << (pt->right->color == black ? "B" : "R") << "\n\n";
            else ofs << "(No right son)" << "\n\n";

            return ofs;
        };

        friend std::ostream& operator<<(std::ostream& ofs, const RBNode<T>& pt) {
            ofs << "Key: " << pt.key << ", color: " << (pt.color == black ? "B" : "R") << "\n";
            if (pt.father != nullptr) ofs << "(Father) key: " << pt.father.key << ", color: " << (pt.father.color == black ? "B" : "R") << "\n";
            else ofs << "No father (root)" << "\n";
            if (pt.left != nullptr) ofs << "(Left son) key: " << pt.left.key << ", color: " << (pt.left.color == black ? "B" : "R") << "\n";
            else ofs << "(No left son)" << "\n";
            if (pt.right != nullptr) ofs << "(Right son) key: " << pt.right.key << ", color: " << (pt.right.color == black ? "B" : "R") << "\n\n";
            else ofs << "(No right son)" << "\n\n";

            return ofs;
        };

        void               print_node();
        [[nodiscard]] bool is_left_son()  const { return ((father != nullptr) && father->left == this); };
        [[nodiscard]] bool is_right_son() const { return ((father != nullptr) && father->right == this); };
        RBNode*            max_node()           { return ((right == nullptr) ? this : right->max_node()); };
        RBNode*            min_node()           { return ((left == nullptr) ? this : left->min_node()); };
        RBNode*            node_Successor();
        RBNode*            node_Predecessor();
        RBNode*            node_Sibling();
    };

    template<typename T>
    RBNode<T>& RBNode<T>::operator=(const RBNode<T>& input) {
        if (this == &input) return *this;

        auto* newFather = RBNode<T>();
        auto* newLeft = RBNode<T>();
        auto* newRight = RBNode<T>();

        try {
            newFather = new RBNode(*input.father);
            newLeft = new RBNode(*input.left);
            newRight = new RBNode(*input.right);
        }
        catch (...) {
            delete newFather;
            delete newLeft;
            delete newRight;

            throw algo::ds::rbt::exception::NodeFailedAllocException();
        }

        key = input.key;
        std::swap(father, newFather);
        std::swap(left, newLeft);
        std::swap(right, newRight);

        delete newFather;
        delete newLeft;
        delete newRight;

        return *this;
    }

    template<typename T>
    RBNode<T>& RBNode<T>::operator=(RBNode<T>&& input) noexcept {
        auto* newFather = RBNode<T>();
        auto* newLeft = RBNode<T>();
        auto* newRight = RBNode<T>();

        try {
            newFather = new RBNode(*input.father);
            newLeft = new RBNode(*input.left);
            newRight = new RBNode(*input.right);
        }
        catch (...) {
            delete newFather;
            delete newLeft;
            delete newRight;

            throw algo::ds::rbt::exception::NodeFailedAllocException();
        }

        key = input.key;
        std::swap(father, newFather);
        std::swap(left, newLeft);
        std::swap(right, newRight);

        delete newFather;
        delete newLeft;
        delete newRight;

        return *this;
    }

    template <typename T>
    inline T RBNode<T>::operator[](const size_t& id) {
        if (id < 0 || id > 3) throw algo::ds::rbt::exception::NodeIndexOutOfBoundException();
        else if (id == 0) return this->key;
        else if (id == 1) return father->key;
        else if (id == 2) return left->key;
        else return right->key;
    }

    template <typename T>
    inline T RBNode<T>::operator[](const size_t& id) const {
        if (id < 0 || id > 3) throw algo::ds::rbt::exception::NodeIndexOutOfBoundException();
        else if (id == 0) return this->key;
        else if (id == 1) return father->key;
        else if (id == 2) return left->key;
        else return right->key;
    }

    template <typename T>
    inline void RBNode<T>::print_node() {
        std::cout << "Key: " << key << ", color: " << (color == black ? "B" : "R") << std::endl;

        if (father != nullptr) std::cout << "(Father) key: " << father->key << ", color: " << (father->color == black ? "B" : "R") << std::endl;
        else std::cout << "No father (root)" << std::endl;

        if (left != nullptr) std::cout << "(Left son) key: " << left->key << ", color: " << (left->color == black ? "B" : "R") << std::endl;
        else std::cout << "(No left son)" << std::endl;

        if (right != nullptr) std::cout << "(Right son) key: " << right->key << ", color: " << (right->color == black ? "B" : "R") << std::endl;
        else std::cout << "(No right son)" << std::endl;

        std::cout << std::endl;
    }

    // For in-oredr walk / increment in iterator
    template <typename T>
    inline RBNode<T>* RBNode<T>::node_Successor() {
        if (this != nullptr) {
            if (right != nullptr) return right->min_node();
            else if (is_left_son()) return father;

            auto successor = this;

            do {
                successor = successor->father;
            } while ((successor != nullptr) && (successor->is_right_son()));

            if (successor != nullptr) return successor->father;
            else return nullptr;
        }

        return nullptr;
    }

    // For reverse in-oredr walk / decrement in iterator
    template <typename T>
    inline RBNode<T>* RBNode<T>::node_Predecessor() {
        if (this != nullptr) {
            if (left != nullptr) return left->max_node();
            else if (is_right_son()) return father;

            auto predeccesor = this;

            do {
                predeccesor = predeccesor->father;
            } while ((predeccesor != nullptr) && (predeccesor->is_left_son()));

            if (predeccesor != nullptr) return predeccesor->father;
            else return nullptr;
        }

        return nullptr;
    }

    template <typename T>
    inline RBNode<T>* RBNode<T>::node_Sibling() {
        if (this != nullptr) return (father == nullptr ? nullptr : (is_left_son() ? father->right : father->left));
        else return nullptr;
    }

}

#endif
