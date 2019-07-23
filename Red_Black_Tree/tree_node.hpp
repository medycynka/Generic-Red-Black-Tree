#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#pragma once
#include <iostream>
#include <iterator>
#include <utility>
#include <exception>

enum colors { red, black };

template <typename T>
class node{
    public:
        T     key;
        node *father;
        node *left;
        node *right;
        int   color;

        node()                                      : father(nullptr), left(nullptr), right(nullptr), color(black){};
        explicit node(T input)                      : key(input), father(nullptr), left(nullptr), right(nullptr), color(red){};
        node(const node &s)                         : key(s.key), father(s.father), left(s.left), right(s.right), color(s.color){};
        node(node &&s) noexcept                     : key(s.key), father(s.father), left(s.left), right(s.right), color(s.color){};
        node(T input, node* father_)                : key(input), father(father_), left(nullptr), right(nullptr), color(red){};
        node(T input, node* father_, int new_color) : key(input), father(father_), left(nullptr), right(nullptr), color(new_color){};
        ~node() = default;

        node& operator= (const T &input)           { key = input; return *this; };
        node& operator= (const node<T> &input);
        node& operator= (node<T> &&input) noexcept;
        bool  operator==(const T &input)     const	{ return key == input; };
        bool  operator!=(const T &input)     const	{ return key != input; };
        bool  operator> (const T &input)     const	{ return key > input; };
        bool  operator< (const T &input)     const	{ return key < input; };
        bool  operator>=(const T &input)     const	{ return key >= input; };
        bool  operator<=(const T &input)     const	{ return key <= input; };
        bool  operator==(const node &source) const	{ return ( (key == source.key) && (father == source.father) ); };
        bool  operator!=(const node &source) const	{ return (!(*this == source)); };
        bool  operator> (const node &source) const	{ return key > source.key; };
        bool  operator< (const node &source) const	{ return key < source.key; };
        bool  operator>=(const node &source) const	{ return key >= source.key; };
        bool  operator<=(const node &source) const	{ return key <= source.key; };

        friend std::ostream& operator<<(std::ostream& ofs, const node<T>* pt){
            ofs << "Key: " << pt->key << ", color: " << ( pt->color == black ? "B" : "R" ) << "\n";
            if(pt->father != nullptr) ofs << "(Father) key: " << pt->father->key << ", color: " << (pt->father->color == black ? "B" : "R") << "\n";
            else ofs << "No father (root)" << "\n";
            if(pt->left != nullptr) ofs << "(Left son) key: " << pt->left->key << ", color: " << (pt->left->color == black ? "B" : "R") << "\n";
            else ofs << "(No left son)" << "\n";
            if(pt->right != nullptr) ofs << "(Right son) key: " << pt->right->key << ", color: " << (pt->right->color == black ? "B" : "R") << "\n\n";
            else ofs << "(No right son)" << "\n\n";

            return ofs;
        };

        inline void    print_node();
        inline bool    is_left_son()  const { return ( (father != nullptr) && father->left == this ); };
        inline bool    is_right_son() const { return ( (father != nullptr) && father->right == this ); };
        inline node*   max_node()           { return ( (right == nullptr) ? this : right->max_node() ); };
        inline node*   min_node()           { return ( (left == nullptr) ? this : left->min_node() ); };
        inline node*   node_Successor();
        inline node*   node_Predecessor();
        inline node*   node_Sibling();
};

template<typename T>
node<T> &node<T>::operator=(const node<T> &input){
    auto *newFather = nullptr;
    auto *newLeft = nullptr;
    auto *newRight = nullptr;

    try{
        newFather = new node(*input.father);
        newLeft = new node(*input.left);
        newRight = new node(*input.right);
    }
    catch(...){
        delete newFather;
        delete newLeft;
        delete newRight;

        throw;
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
node<T> &node<T>::operator=(node<T> &&input) noexcept{
    auto *newFather = nullptr;
    auto *newLeft = nullptr;
    auto *newRight = nullptr;

    try{
        newFather = new node(*input.father);
        newLeft = new node(*input.left);
        newRight = new node(*input.right);
    }
    catch(...){
        delete newFather;
        delete newLeft;
        delete newRight;

        throw;
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
inline void node<T>::print_node(){
    std::cout << "Key: " << key << ", color: " << ( color == black ? "B" : "R" ) << std::endl;

    if(father != nullptr) std::cout << "(Father) key: " << father->key << ", color: " << ( father->color == black ? "B" : "R" ) << std::endl;
    else std::cout << "No father (root)" << std::endl;

    if(left != nullptr) std::cout << "(Left son) key: " << left->key << ", color: " << ( left->color == black ? "B" : "R" ) << std::endl;
    else std::cout << "(No left son)" << std::endl;

    if(right != nullptr) std::cout << "(Right son) key: " << right->key << ", color: " << ( right->color == black ? "B" : "R" ) << std::endl;
    else std::cout << "(No right son)" << std::endl;

    std::cout << std::endl;
}

// For in-oredr walk / increment in iterator
template <typename T>
inline node<T>* node<T>::node_Successor(){
    if(this != nullptr){
        if(right != nullptr) return right->min_node();
        else if(is_left_son()) return father;

        auto successor = this;

        do{
            successor = successor->father;
        }while( (successor != nullptr) && (successor->is_right_son()) );

        if(successor != nullptr) return successor->father;
        else return nullptr;
    }

    return nullptr;
}

// For reverse in-oredr walk / decrement in iterator
template <typename T>
inline node<T>* node<T>::node_Predecessor(){
    if(this != nullptr){
        if(left != nullptr) return left->max_node();
        else if(is_right_son()) return father;

        auto predeccesor = this;

        do{
            predeccesor = predeccesor->father;
        }while( (predeccesor != nullptr) && (predeccesor->is_left_son()) );

        if(predeccesor != nullptr) return predeccesor->father;
        else return nullptr;
    }

    return nullptr;
}

template <typename T>
inline node<T>* node<T>::node_Sibling(){
    if(this != nullptr) return (father == nullptr ? nullptr : ( is_left_son() ? father->right : father->left ));
    else return nullptr;
}

#endif //_TREE_NODE_HPP_
