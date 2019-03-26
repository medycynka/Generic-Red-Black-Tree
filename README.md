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
   * <b>inline bool is_left_son()</b> - returns **true** if the node is a left son
   * <b>inline bool is_right_son()</b> - returns **true** if the node is a right son
   * <b>inline node* max_node()</b> - returns a node with **maximal key**
   * <b>inline node* min_node()</b> - returns a node with **minimal key**
   * <b>inline node* node_Successor()</b> - returns a **succesor** of the node
   * <b>inline node* node_Predecessor()</b> - returns a **predecessor** of the node
   * <b>inline node* node_Sibling()</b> - returns, a **sibling** of the node or **NULL** if node doesn't have a sibling or is a root of the tree
   
## RBTree
