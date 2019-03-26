# Generic-Red-Black-Tree
A generic implementation of red-black tree with iterators

# Red–Black Tree
It is a kind of self-balancing binary search tree in computer science. Each node of the binary tree has an extra bit, and that bit is often interpreted as the color (red or black) of the node. These color bits are used to ensure the tree remains approximately balanced during insertions and deletions.
Balance is preserved by painting each node of the tree with one of two colors in a way that satisfies certain properties, which collectively constrain how unbalanced the tree can become in the worst case. When the tree is modified, the new tree is subsequently rearranged and repainted to restore the coloring properties. The properties are designed in such a way that this rearranging and recoloring can be performed efficiently.
The balancing of the tree is not perfect, but it is good enough to allow it to guarantee searching in **O(log n)** time, where n is the total number of elements in the tree. The insertion and deletion operations, along with the tree rearrangement and recoloring, are also performed in **O(log n)** time.
Tracking the color of each node requires only 1 bit of information per node because there are only two colors. The tree does not contain any other data specific to its being a red–black tree so its memory footprint is almost identical to a classic (uncolored) binary search tree. In many cases, the additional bit of information can be stored at no additional memory cost.



# Classes
## node
Class **node** is a representation of a tree node
1. **Fields:**
   * <b>T key</b> - value of the node
   * <b>node *father</b> - a pointer to a father of the node
   * <b>node *left</b> - a pointer to a left son of the node
   * <b>node *right</b> - a pointer to a right son of the node
   * <b>int color</b> - color of the node
2. **Methods:**
   * <b>node()</b>, <b>node(T input)</b>, <b>node(const node &s)</b>, <b>node(T input, node* father_)</b>, <b>node(T input, node* father_, int new_color)</b> - constructors
   * <b>inline void print_node()</b> - printing a value of the node, father's key, left son's key and a right son's key
   * <b>all operators</b> (=, ==, !=, >, <, >=, <=) - operators to compare node's key and nodes between themselves
   * <b>inline bool is_left_son()</b> - returns **true** if the node is a left son, otherwise returns **false**
   * <b>inline bool is_right_son()</b> - returns **true** if the node is a right son, otherwise returns **false**
   * <b>inline node* max_node()</b> - returns a node with **maximal key**
   * <b>inline node* min_node()</b> - returns a node with **minimal key**
   * <b>inline node* node_Successor()</b> - returns a **succesor** of the node or **NULL** if the node doesn't havy a succesor
   * <b>inline node* node_Predecessor()</b> - returns a **predecessor** of the node or **NULL** if the node doesn't havy a predecessor
   * <b>inline node* node_Sibling()</b> - returns, a **sibling** of the node or **NULL** if node doesn't have a sibling or is a root of the tree
   
## RBTree
Class **RBTree** is a main class representing **Red-Black Tree** structure
1. **Fields:**
   * <b>node<T> *root</b> - root of the tree
   * <b>Iterator iterator</b> - iterator for the tree
   * <b>static Iterator EMPTY_ITERATOR</b> - field that represents the end of the iterator
2. **Methods:**
   * <b>public:</b>
     * <b>RBTree()</b>, <b>RBTree(const RBTree<T> &)</b>, <b>RBTree(const RBTree<T> &&)</b> - constructors
     * <b>node<T>* getRoot()</b> - returns root of the tree
     * <b>inline void Insert(T input)</b> - inserting _input_ to the tree
     * <b>inline bool T_find(T)</b> - returns **true**  if the value of the search item belongs to the tree, otherwise returns **false**
     * <b>node<T>* T_node_find(T)</b> - returns **node** with the key of the search item, if it belongs to the tree, otherwise returns **NULL**
     * <b>inline void Display()</b> - printing elements of the tree
     * <b>operators</b> - operator **+ (merging trees)**, **- (spliting tree)** and **=**
     * <b>inline int Black_hight()</b> - returns the height of black nodes
     * <b>inline int Size()</b> - returns number of elements in the tree
     * <b>inline void Delete(T)</b> - deleting node with _input_ key
     * <b>inline bool isEmpty()</b> - returns **true** if the tree is empty, otherwise returns **false**
     * <b>Iterator maxIt()</b> - returns **iterator** to the node with **maximal key**
     * <b>Iterator minIt()</b> - returns **iterator** to the node with **minimal key**
     * <b>Iterator& begin()</b> - returns **iterator** to the starting node (basic, with minimal key)
     * <b>Iterator& nd()</b> - returns **iterator** after the last node (basic, with maximal key)
   * <b>private:</b>
     * <b>inline int Size(node<T>*)</b> - helper method, that allows to count number of nodes below the _input node_
     * <b>inline void Display(node<T>*, int)</b> - helper function displaying elements of the tree with a level of the nodes
     * <b>inline void Rotate_left(node<T>*)</b> - a left rotation in regard to _input node_
     * <b>inline void Rotate_right(node<T>*)</b> - a right rotation in regard to _input node_
     * <b>inline void Insert_fix(node<T>*)</b> - fixing the balance of the tree and adjusting colors of the nodes after insertion
     * <b>RBTree(node<T>*)</b> making **root** with _input node_
     * <b>inline void Merge(node<T>*)</b> - merging trees
     * <b>inline void Split(node<T>*)</b> - splitting trees
     * <b>node<T>* Successor(node<T>*)</b> - returns a **succesor** of the _input node_ or **NULL** if the node doesn't havy a succesor
     * <b>inline void Delete_fix(node<T>*)</b> - fixing the balance of the tree and adjusting colors of the nodes after deletion
