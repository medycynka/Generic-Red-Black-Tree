#ifndef _SIMPLE_RED_BLACK_TREE_HPP_
#define _SIMPLE_RED_BLACK_TREE_HPP_

#include <iostream>

enum colors { red, black };

template <typename T>
class node{
    public:
        T    key;
        node *father;
        node *left;
        node *right;
        int  color;

        node()                                      : father(NULL), left(NULL), right(NULL), color(black)                   {};
        node(T input)                               : key(input), father(NULL), left(NULL), right(NULL), color(red)         {};
        node(const node &s)                         { (*this) = s; };
        node(T input, node* father_)                : key(input), father(father_), left(NULL), right(NULL), color(red)      {};
        node(T input, node* father_, int new_color) : key(input), father(father_), left(NULL), right(NULL), color(new_color){};
        inline void print_node();

        T &  operator= ( const T & input )              { key = input; };
        bool operator==( const T & input )     const	{ return key == input; };
        bool operator!=( const T & input )     const	{ return key != input; };
        bool operator> ( const T & input )     const	{ return key > input; };
        bool operator< ( const T & input )     const	{ return key < input; };
        bool operator>=( const T & input )     const	{ return key >= input; };
        bool operator<=( const T & input )     const	{ return key <= input; };
        bool operator==( const node & source ) const	{ return ( (key == source.key) && (father == source.father) ); };
        bool operator!=( const node & source)  const	{ return ( (key != source.key) || (father != source.father) ); };
        bool operator> ( const node & source)  const	{ return key > source.key; };
        bool operator< ( const node & source)  const	{ return key < source.key; };
        bool operator>=( const node & source)  const	{ return key >= source.key; };
        bool operator<=( const node & source)  const	{ return key <= source.key; };

        inline bool    is_left_son()  const { return ( (father != NULL) && father->left == this ); };
        inline bool    is_right_son() const { return ( (father != NULL) && father->right == this ); };
        inline node*   max_node()           { return ( (right == NULL) ? this : right->max_node() ); };
        inline node*   min_node()           { return ( (left == NULL) ? this : left->min_node() ); };
        inline node*   node_Successor();
        inline node*   node_Predecessor();
        inline node*   node_Sibling();
};

template <typename T>
inline void node<T>::print_node(){
    std::cout << "Key: " << key << ", color: ";
    if(color == black) std::cout << "B" << std::endl;
    else std::cout << "R" << std::endl;

    if(father != NULL ){
        std::cout << "(Father) key: " << father->key << ", color: ";

        if(father->color == black) std::cout << "B" << std::endl;
        else std::cout << "R" << std::endl;
    }
    else{
        std::cout << "No father (root)" << std::endl;
    }
    if(left != NULL){
        std::cout << "(Left son) key: " << left->key << ", color: ";

        if(left->color == black) std::cout << "B" << std::endl;
        else std::cout << "R" << std::endl;
    }
    else{
        std::cout << "(No left son)" << std::endl;
    }
    if(right != NULL){
        std::cout << "(Right son) key: " << right->key << ", color: ";

        if(right->color == black) std::cout << "B" << std::endl;
        else std::cout << "R" << std::endl;
    }
    else{
        std::cout << "(No right son)" << std::endl;
    }

    std::cout << std::endl;
}

template <typename T>
inline node<T>* node<T>::node_Successor(){
    if(this != NULL){
        if(right != NULL) return right->min_node();
        else if(is_left_son()) return father;

        node* successor = this;

        do{
            successor->father;
        }while( (successor != NULL) && (successor->is_right_son()) );

        if(successor != NULL) return successor->father;
        else return NULL;
    }

    return NULL;
}

template <typename T>
inline node<T>* node<T>::node_Predecessor(){
    if(this != NULL){
        if(left != NULL) return left->max_node();
        else if(is_right_son()) return father;

        node* predeccesor = this;

        do{
            predeccesor->left;
        }while( (predeccesor != NULL) && (predeccesor->is_left_son()) );

        if(predeccesor != NULL) return predeccesor->father;
        else return NULL;
    }

    return NULL;
}

template <typename T>
inline node<T>* node<T>::node_Sibling(){
    if(this != NULL){
        if(father == NULL) return NULL;

        return ( is_left_son() ? father->right : father->left );
    }

    return NULL;
}

template <typename T>
class RBTree{
        inline int      Size(node<T>*);
        inline void     Display(node<T>*, int);
        inline void     Rotate_left(node<T>*);
        inline void     Rotate_right(node<T>*);
        inline void     Insert_fix(node<T>*);
        RBTree(node<T>*);
        inline void     Merge(node<T>*);
        inline void     Split(node<T>*);
        node<T>         *root;
        node<T>*        Successor(node<T>*);
        inline void     Delete_fix(node<T>*);

    public:
        class Iterator{
            protected:
                node<T> * Iter;

            public:
                friend class RBTree<T>;

                typedef T *       pointer;
                typedef T const * const_pointer;
                typedef T &       memory_ref;
                typedef T const & const_memory_ref;

                Iterator()                  : Iter(NULL){};
                Iterator(node<T>* ptr)      : Iter(ptr){};
                Iterator(const Iterator &s) : Iter(s.Iter){};
				
                Iterator   operator++      ();
                Iterator   operator++      (int);
                Iterator&  operator=       (const_memory_ref source);
                bool       operator==      (const Iterator& source) const { return (Iter == source.Iter); };
                bool       operator!=      (const Iterator& source) const { return (Iter != source.Iter); };
                operator node<T>&          ()                             { return (*Iter); };
                operator const node<T>&    ()                       const { return (*Iter); };
                const_memory_ref operator* ()                       const { return (Iter->key); };
                pointer    operator->      ()                       const { return Iter; };
                operator bool              ()                       const { return (Iter != NULL); };
        };

        RBTree():root(NULL){};
        RBTree(const RBTree<T> &);
        RBTree(const RBTree<T> &&);
        node<T>*        getRoot(){ return root; };
        inline void     Insert(T input);
        inline bool     T_find(T);
        node<T>*        T_node_find(T);
        inline void     Display();
        void            operator+(const RBTree<T>&);
        void            operator-(const RBTree<T>&);
        void            operator=(const RBTree<T> &);
        void            operator=(const RBTree<T> &&);
        inline int      Black_hight();
        inline int      Size();
        inline void     Delete(T);

        inline bool     isEmpty() const { return root == NULL; };
        Iterator        maxIt()   const { return ( isEmpty() ? end() : Iterator(root->max_node()) ); };
        Iterator        minIt()   const { return ( isEmpty() ? end() : Iterator(root->min_node()) ); };
        Iterator        begin()   const { return minIt(); };
        Iterator        end()     const { return EMPTY_ITERATOR; };

        private:
        	Iterator iterator;
        	static Iterator EMPTY_ITERATOR;
};

template <typename T>
typename RBTree<T>::Iterator RBTree<T>::EMPTY_ITERATOR = Iterator();

// POST-ORDER
/*template <typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(){
    node<T>* node_ = this->Iter;
    if(node_->father == NULL){
        this->Iter = NULL;
        return *this;
    }
    if(node_ == node_->father->left && node_->father->right != NULL){
        node_ = node_->father->right;
    }
    else{
        this->Iter = node_->father;
        return *this;
    }
    while(true){
        if(node_->left != NULL){
            node_ = node_->left;
        }
        else if(node_->right != NULL){
            node_ = node_->right;
        }
        else{
            this->Iter = node_;
            return *this;
        }
    }
}
*/

// IN-ORDER
template <typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(){
    if(this->Iter != NULL){
        node<T>* node_ = this->Iter;

        if(node_->right != NULL){
            this->Iter = node_->right->min_node();

            return *this;
        }
        else if(node_->is_left_son()){
            this->Iter = node_->father;

            return *this;
        }

        do{
            node_ = node_->father;
        }while(node_ != NULL && node_->is_right_son());

        if(node_ != NULL){
            this->Iter = node_->father;

            return *this;
        }
        else{
            this->Iter = NULL;

            return *this;
        }
    }
    else{
        return *this;
    }
}

template <typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(int){
    Iterator pom = *this;
    ++(*this);

    return pom;
}

template <typename T>
typename RBTree<T>::Iterator& RBTree<T>::Iterator::operator=(const_memory_ref source){
    this->Iter->key = source;

    return (*this);
}

template <typename T>
RBTree<T>::RBTree(const RBTree<T> &tree){
    if(tree.root == NULL) root = NULL;
    else{
        root = new node<T>(tree.root->key);
        root->color = tree.root->color;
        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }
}

template <typename T>
RBTree<T>::RBTree(const RBTree<T> &&tree){
    if(tree.root == NULL) root = NULL;
    else{
        root = new node<T>(tree.root->key);
        root->color = tree.root->color;
        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }
}

template <typename T>
void RBTree<T>::operator=(const RBTree<T> &tree){
    if(tree.root == NULL) root = NULL;
    else{
        root = new node<T>(tree.root->key);
        root->color = tree.root->color;
        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }
}

template <typename T>
void RBTree<T>::operator=(const RBTree<T> &&tree){
    if(tree.root == NULL) root = NULL;
    else{
        root = new node<T>(tree.root->key);
        root->color = tree.root->color;
        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }
}

template<typename T>
RBTree<T>::RBTree(node<T> * in){
    root = in;
}

template <typename T>
inline void RBTree<T>::Insert(T input){
    node<T> *p, *q;
    node<T> *create = new node<T>(input);
    p = root;
    q = NULL;

    if(root == NULL ){
        root = create;
        create->father = NULL;
    }
    else{
        while ( p != NULL){
            q = p;

            if(p->key > create->key) p = p->left;
            else if(p->key < create->key) p = p->right;
            else return;
        }

        create->father = q;

        if(q->key < create->key) q->right=create;
        else if(q->key > create->key) q->left=create;
        else return;
    }

    Insert_fix(create);
}


template<typename T>
inline void RBTree<T>::Insert_fix(node<T> *create){
    node<T> *x = create;

    while(x != root && x->father->color == red){
        if(x->father == x->father->father->left){
            node<T> *y = x->father->father->right;

            if((y != NULL ) && (y->color == red)){
                x->father->color = black;
                y->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else{
                if(x->father->right == x){
                    x  = x->father;
                    Rotate_left(x);
                }

                x->father->color = black;
                x->father->father->color = red;
                Rotate_right(x->father->father);
            }
        }
        else{
            node<T> *y = x->father->father->left;
            if((y != NULL) && (y->color == red)){
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
    if(in->left == NULL) return;
    else{
        node<T> *y = in;
        node<T> *x = y->left;
        node<T> *b = x->right;
        node<T> *f = y->father;

        if(f == NULL){
            x->father = NULL;
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

        if( b != NULL) b->father =y;
    }
}

template <typename T>
inline void RBTree<T>::Rotate_left(node<T>* x){
    if(x->right == NULL) return;
    else{
        node<T> *y = x->right;
        node<T> *b = y->left;
        node<T> *f = x->father;

        if(f == NULL){
            y->father = NULL;
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

        if(b != NULL) b->father = x;
    }
}

template <typename T>
inline bool RBTree<T>::T_find(T in){
    node<T> *t;
    t = root;

    while(t != NULL){
        if(t->key == in) break;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    if(t == NULL) return false;
    else if(t->key == in) return true;

    return true;
}

template<typename T>
node<T>* RBTree<T>::T_node_find(T in){
    node<T> *t;
    t = root;

    while(t != NULL){
        if(t->key == in) break;
        if(in > t->key) t = t->right;
        else if(in < t->key) t = t->left;
    }

    if(t == NULL) return NULL;
    else if(t->key == in) return t;

    return NULL;
}


template<typename T>
inline void RBTree<T>::Merge(node<T> *p ) {
    if(p != NULL){
        if(p->left) Merge(p->left);
        if(p->right) Merge(p->right);

        Insert(p->key);
    }
}

template<typename T>
inline void RBTree<T>::Split(node<T> *p ) {
    if(p != NULL){
        if(p->left) Split(p->left);
        if(p->right) Split(p->right);

        std::cout <<p->key;
        Delete(p->key);
    }
}

template<typename T>
void RBTree<T>::operator+(const RBTree<T> & in){
    std::cout <<"\n\n Dodajemy do siebie drzewa \n";
    Merge(in.root);
}

template<typename T>
void RBTree<T>::operator-(const RBTree<T> & in){
    std::cout <<"\n\n Odejmujemy od siebie drzewa \n";
    Split(in.root);
}

template<typename T>
inline int RBTree<T>::Black_hight(){
    node<T> *p;
    p = root;
    int num = 0;

    while(p != NULL){
        if(p->color == black) num++;

        p = p->left;
    }

    return num;
}

template<typename T>
inline int RBTree<T>::Size(){
    return Size(root);
}

template<typename T>
inline int RBTree<T>::Size(node<T> * in){
    if(in == NULL) return 0;
    else{
        int ls,rs;
        ls = Size(in->left);
        rs = Size(in->right);

        return (ls + rs + 1);
    }
}

template<typename T>
inline void RBTree<T>::Display(){
    Display(root, 0);
}

template<typename T>
inline void RBTree<T>::Display(node<T>* in, int level){
    if(in == NULL){
        //std::cout << "level: " << level << ", NULL\n";

        return;
    }

    std::cout << "level: " << level << std::endl;
    in->print_node();

    Display(in->left, level+1);
    Display(in->right, level+1);
}

template<typename T>
node<T>* RBTree<T>::Successor(node<T> *p){
    node<T> *y = NULL;

    if(p->left != NULL){
        y = p->left;

        while(y->right != NULL) y = y->right;
    }
    else{
        y = p->right;

        while(y->left != NULL) y=y->left;
    }

    return y;
}

template <typename T>
inline void RBTree<T>::Delete(T x){
    if(root == NULL){
        std::cout << "\nEmpty RBTree." ;

        return ;
    }

    node<T> *p;
    p = root;
    node<T> *y = NULL;
    node<T> *q = NULL;
    int found = 0;

    while(p != NULL && found == 0){
        if(p->key == x) found = 1;
        if(found == 0){
            if(p->key < x) p = p->right;
            else p = p->left;
        }
    }

    if(found == 0) return;
    else{
        std::cout << "\nDeleted Element: " << p->key;
        std::cout << "\nColour: ";

        if(p->color == black) std::cout << "Black\n";
        else std::cout << "Red\n";

        if(p->left == NULL || p->right == NULL) y = p;
        else y = Successor(p);

        if(y->left != NULL) q = y->left;
        else{
            if(y->right != NULL) q = y->right;
            else q = NULL;
        }

        if(q != NULL) q->father = y->father;
        if(y->father == NULL) root = q;
        else{
            if(y == y->father->left) y->father->left = q;
            else y->father->right = q;
        }

        if(y != p) {
            p->color=y->color;
            p->key=y->key;
        }
        if(y->color == black) Delete_fix(q);
    }
}

template <typename T>
inline void RBTree<T>::Delete_fix(node<T> *p){
    if(p != NULL){
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

#endif // _SIMPLE_RED_BLACK_TREE_HPP_
