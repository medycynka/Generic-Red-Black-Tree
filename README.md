# Generic Red-Black-Tree by Szymon Peszek
A generic implementation of red-black tree with iterators

# Red–Black Tree
It is a kind of self-balancing binary search tree in computer science. Each node of the binary tree has an extra bit, and that bit is often interpreted as the color (red or black) of the node. These color bits are used to ensure the tree remains approximately balanced during insertions and deletions.
Balance is preserved by painting each node of the tree with one of two colors in a way that satisfies certain properties, which collectively constrain how unbalanced the tree can become in the worst case. When the tree is modified, the new tree is subsequently rearranged and repainted to restore the coloring properties. The properties are designed in such a way that this rearranging and recoloring can be performed efficiently.
The balancing of the tree is not perfect, but it is good enough to allow it to guarantee searching in **O(log n)** time, where n is the total number of elements in the tree. The insertion and deletion operations, along with the tree rearrangement and recoloring, are also performed in **O(log n)** time.
Tracking the color of each node requires only 1 bit of information per node because there are only two colors. The tree does not contain any other data specific to its being a red–black tree so its memory footprint is almost identical to a classic (uncolored) binary search tree. In many cases, the additional bit of information can be stored at no additional memory cost.

## Time complexity
| **Method** | **Averge** | **Worst** |
|------------|------------|-----------|
| **_Space_**  | O(n) | O(n) |
| **_Search_** | O(log n) | O(log n) |
| **_Insert_** | O(log n) | O(log n) |
| **_Delete_** | O(log n) | O(log n) |

## Properties
In addition to the requirements imposed on a _binary search tree_ the following must be satisfied by a red–black tree:
1. Each node is either red or black.
2. The root is black. This rule is sometimes omitted. Since the root can always be changed from red to black, but not necessarily vice versa, this rule has little effect on analysis.
3. All leaves (NIL) are black.
4. If a node is red, then both its children are black.
5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
6. Some definitions: the number of black nodes from the root to a node is the node's black depth; the uniform number of black nodes in all paths from root to the leaves is called the black-height of the red–black tree.

These constraints enforce a critical property of red–black trees: the path from the root to the farthest leaf is no more than twice as long as the path from the root to the nearest leaf. The result is that the tree is roughly height-balanced. Since operations such as inserting, deleting, and finding values require worst-case time proportional to the height of the tree, this theoretical upper bound on the height allows red–black trees to be efficient in the worst case, unlike ordinary binary search trees.
To see why this is guaranteed, it suffices to consider the effect of properties 4 and 5 together. For a red–black tree T, let B be the number of black nodes in property 5. Let the shortest possible path from the root of T to any leaf consist of B black nodes. Longer possible paths may be constructed by inserting red nodes. However, property 4 makes it impossible to insert more than one consecutive red node. Therefore, ignoring any black NIL leaves, the longest possible path consists of 2*B nodes, alternating black and red (this is the worst case). Counting the black NIL leaves, the longest possible path consists of 2*B-1 nodes.
The shortest possible path has all black nodes, and the longest possible path alternates between red and black nodes. Since all maximal paths have the same number of black nodes, by property 5, this shows that no path is more than twice as long as any other path.

# Implementation
## _class_ node
Class **RBNode** is a representation of a **Red-Black Tree** node
1. **Fields:**
   * <b>T key</b> - value of the node
   * <b>node *father</b> - a pointer to a father of the node
   * <b>node *left</b> - a pointer to a left son of the node
   * <b>node *right</b> - a pointer to a right son of the node
   * <b>int color</b> - color of the node
2. **Methods:**
   * <b>RBNode()</b>, <b>RBNode(T input)</b>, <b>RBNode(const node &s)</b>, <b>RBNode(T input, node* father_)</b>, <b>RBNode(T input, node* father_, int new_color)</b> - constructors
   * <b>inline void print_node()</b> - printing a value of the node, father's key, left son's key and a right son's key
   * <b>all operators</b> (=, ==, !=, >, <, >=, <=) - operators to compare node's key and nodes between themselves
   * <b>inline bool is_left_son()</b> - returns **true** if the node is a left son, otherwise returns **false**
   * <b>inline bool is_right_son()</b> - returns **true** if the node is a right son, otherwise returns **false**
   * <b>inline RBNode* max_node()</b> - returns a node with **maximal key**
   * <b>inline RBNode* min_node()</b> - returns a node with **minimal key**
   * <b>inline RBNode* node_Successor()</b> - returns a **succesor** of the node or **nullptr** if the node doesn't havy a succesor
   * <b>inline RBNode* node_Predecessor()</b> - returns a **predecessor** of the node or **nullptr** if the node doesn't havy a predecessor
   * <b>inline RBNode* node_Sibling()</b> - returns, a **sibling** of the node or **nullptr** if node doesn't have a sibling or is a root of the tree
   
## _class_ RBTree
Class **RBTree** is a main class representing **Red-Black Tree** structure
1. **Fields:**
   * <b>RBNode<T> *root</b> - root of the tree
   * <b>std::size_t size_</b> - number of elements in tree
2. **Methods:**
   * <b>public:</b>
     * <b>RBTree()</b>, <b>RBTree(const RBTree<T> &)</b>, <b>RBTree(RBTree<T> &&)</b> - constructors
     * <b>inline node<T>* getRoot()</b> - returns root of the tree
     * <b>inline std::size_t size()</b> - returns number of elements in tree
     * <b>inline void insert(T input)</b> - inserting _input_ to the tree
     * <b>inline bool find(T)</b> - returns **true**  if the value of the search item belongs to the tree, otherwise returns **false**
     * <b>RBNode<T>* node_find(T)</b> - returns **node** with the key of the search item, if it belongs to the tree, otherwise returns **nullptr**
     * <b>inline void display()</b> - printing elements of the tree
     * <b> inline void clear()</b> - deleting all elements from tree
     * <b>operators</b> - operator **+ (merging trees)**, **- (spliting tree)**
     * <b>operator=/b> - move and assignment operators
     * <b>operator[]</b> - returns element with given index (elements are order in "pre-order")
     * <b>inline int Black_hight()</b> - returns the height of black nodes
     * <b>inline int Size()</b> - returns number of elements in the tree
     * <b>inline void remove(T)</b> - deleting node with _input_ key
     * <b>inline bool isEmpty()</b> - returns **true** if the tree is empty, otherwise returns **false**
     * <b>RBNode<T>* maxIt()</b> - returns node with **maximal key** or **nullptr** if tree is empty
     * <b>RBNode<T>* minIt()</b> - returns node with **minimal key** or **nullptr** if tree is empty
     * <b>Iterator begin()</b> - returns **iterator** to the starting node (basic, with minimal key)
     * <b>Iterator end()</b> - returns **iterator** after the last node (basic, with maximal key)
     * <b>ReverseIterator rbegin()</b> - returns **reverse_iterator** to the starting node (basic, with maximal key)
     * <b>ReverseIterator rend()</b> - returns **reverse_iterator** after the last node (basic, with minimal key)
     * <b>ConstIterator cbegin()</b> - returns **const_iterator** to the starting node (basic, with minimal key)
     * <b>ConstIterator cend()</b> - returns **const_iterator** after the last node (basic, with maximal key)
     * <b>ConstReverseIterator cbegin()</b> - returns **const_reverse_iterator** to the starting node (basic, with maximal key)
     * <b>ConstReverseIterator cend()</b> - returns **const_reverse_iterator** after the last node (basic, with minimal key)
   * <b>private:</b>
     * <b>inline int Size(RBNode<T>*)</b> - helper method, that allows to count number of nodes below the _input node_
     * <b>inline void Display(RBNode<T>*, int)</b> - helper function displaying elements of the tree with a level of the nodes
     * <b>inline void Rotate_left(RBNode<T>*)</b> - a left rotation in regard to _input node_
     * <b>inline void Rotate_right(RBNode<T>*)</b> - a right rotation in regard to _input node_
     * <b>inline void Insert_fix(RBNode<T>*)</b> - fixing the balance of the tree and adjusting colors of the nodes after insertion
     * <b>RBTree(RBNode<T>*)</b> making **root** with _input node_
     * <b>inline void Merge(RBNode<T>*)</b> - merging trees
     * <b>inline void Split(RBNode<T>*)</b> - splitting trees
     * <b>node<T>* Successor(RBNode<T>*)</b> - returns a **succesor** of the _input node_ or **NULL** if the node doesn't havy a succesor
     * <b>inline void Delete_fix(RBNode<T>*)</b> - fixing the balance of the tree and adjusting colors of the nodes after deletion
     * <b>inline void Copy(RBNode<T>*)</b> - copy elements starting from given RBNode
     * <b> inline void Chop(RBNode<T>*)</b> - deleting elements from given RBNode
## _class_ Iterator, ReverseIterator and ConstIterator
**_Iterators_** represents iterator, reverse_iterator and cons_iterator class for **Red-Black Tree**
1. **Fields:**
   * <b>RBNode<T> * Iter</b> - representation of the Red-Black Tree node for iterator
2. **Methods:**
   * <b>Iterator()</b>, <b>Iterator(node<T>* ptr)</b>, <b>Iterator(const Iterator &s)</b> - constructors
   * <b>Iterator operator++()</b> - post incrementation
   * <b>Iterator operator++(int)</b> - pre incrementation
   * <b>Iterator operator--()</b> - post decrementation
   * <b>Iterator operator--(int)</b> - pre decrementation
   * <b>operators (=, ==, !=)</b> - (needed) operators for general use
   * <b>operator RBNode<T>&()</b> and <b>operator const node<T>& ()</b> - returns a pointer to the _Iter_ field
   * <b>memory_ref operator*()</b> - returns key of the iterator
   * <b>pointer operator->()</b> - returns _Iter_ field
   * <b>operator bool()</b> - returns **true** if the iterator is not a nullptr, otherwise returns **false**
  
# General use
1. Impleneting other structures like **_std::set_** or **_std::map_**
2. Simple test is in the _main_tests.cpp_ 
3 Example of usage is in the _example.hpp_
