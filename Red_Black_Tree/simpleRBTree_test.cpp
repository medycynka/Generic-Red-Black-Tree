#include <iostream>
#include <iterator>
#include "simple_red_black_tree.hpp"

using namespace std;

int main(int argc, char* argv[]){
    RBTree<int> tree;

    if(tree.isEmpty()) cout << "Tree is empty" << endl << endl;

    for(auto i = 0; i< 20; i++){
        tree.Insert(i);
    }

    tree.Display();

    cout << endl;

    cout << "Number of nodes: " << tree.Size() << endl;

    cout << endl;

    for(auto it = tree.begin(); it != tree.end(); it++){
        cout << *it << ", ";
    }

    cout << endl;

    for(auto it = tree.begin(); it != tree.end(); ++it){
        cout << *it << ", ";
    }

    cout << endl;

    for(auto &e : tree){
        cout<< e << ", ";
    }

    cout << endl;

	return 0;
}
