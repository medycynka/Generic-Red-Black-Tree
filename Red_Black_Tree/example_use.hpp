#include <iostream>
#include <chrono>
#include "rb_tree.hpp"


const int test1 = 10000;        // 10^4
const int test2 = 100000;       // 10^5
const int test3 = 1000000;      // 10^6
const int test4 = 10000000;     // 10^7

int example(){
    RBTree<int> tree;

    if(tree.isEmpty()) std::cout << "Tree is empty" << std::endl << std::endl;

    for(auto i = 0; i < 20; i++){
        tree.insert(i);
    }

    tree.display();
    std::cout << std::endl;
    std::cout << (tree.find(3) ? "Found 3" : "Couldn't find 3") << std::endl;
    tree.remove(3);
    std::cout << (tree.find(3) ? "Found 3" : "Couldn't find 3") << std::endl;

    std::cout << std::endl;

    std::cout << "Number of nodes: " << tree.size() << std::endl;

    std::cout << "Testing iterators:" << std::endl;
    std::cout << "******************" << std::endl;
    std::cout << "Normal iterator:" << std::endl;

    for(auto it = tree.begin(); it != tree.end(); it++){
        std::cout << *it << ", ";
    }

    std::cout << std::endl;

    for(auto it = tree.begin(); it != tree.end(); ++it){
        std::cout << *it << ", ";
    }

    std::cout << std::endl;

    for(auto &e : tree){
        std::cout<< e << ", ";
    }

    std::cout << std::endl;
    std::cout << "Const iterator:" << std::endl;

    for(const auto &e : tree){
        std::cout<< e << ", ";
    }

    std::cout << std::endl;
    std::cout << "Reverse iterator:" << std::endl;

    for(auto it = tree.rbegin(); it != tree.rend(); it++){
        std::cout << *it << ", ";
    }

    std::cout << std::endl;

    for(auto it = tree.crbegin(); it != tree.crend(); ++it){
        std::cout << *it << ", ";
    }

    std::cout << std::endl << std::endl << "Testing operator[] (and node operator[]):" << std::endl;
    std::cout << "for i = 1 key value = " << tree[1] << std::endl;
    std::cout << "for i = 7 key value = " << tree[7] << std::endl << std::endl;
    RBNode<int> r(5);
    r.father = new RBNode<int>(1);
    r.left = new RBNode<int>(3);
    r.right = new RBNode<int>(8);
    std::cout << "test node: " << std::endl;
    r.print_node();
    std::cout << "in node for i = 0 (self) key value = " << r[0] << std::endl;
    std::cout << "in node for i = 1 (father) key value = " << r[1] << std::endl;
    std::cout << "in node for i = 2 (left) key value = " << r[2] << std::endl;
    std::cout << "in node for i = 3 (right) key value = " << r[3] << std::endl;

    std::cout << std::endl << std::endl << std::endl << std::endl;
    RBTree<int> tree2 = tree;
    tree.remove(2);
    tree2.insert(42);
    std::cout << std::endl;

    for(auto it = tree.rbegin(); it != tree.rend(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
    for(auto it = tree2.rbegin(); it != tree2.rend(); ++it){
        std::cout << *it << ", ";
    }

    std::cout << std::endl << std::endl << std::endl << std::endl;

    RBTree<int> t;
    for(auto i = 0; i < 5; i++) t.insert(i);
    t.clear();
    t.display();
    std::cout << std::endl << t.size() << std::endl;
    t.insert(2);
    t.insert(7);
    for(auto it = t.rbegin(); it != t.rend(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << std::endl << std::endl << std::endl;
    t.clear();

    /**
     * Test for 10000 elements
     */
    std::cout << "insert and search test for " << test1 << " elements" << std::endl;
    auto start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        t.insert(i);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i){
        t.find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test1 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;
    t.clear();


    /**
     * Test for 100000 elements
     */
    std::cout << "insert and search test for " << test2 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        t.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i){
        t.find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test2 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;
    t.clear();


    /**
     * Test for 1000000 elements
     */
    std::cout << "insert and search test for " << test3 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        t.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i){
        t.find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test3 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;
    t.clear();


    /**
     * Test for 10000000 elements
     */
    std::cout << "insert and search test for " << test4 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        t.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i){
        t.find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test4 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;
    t.clear();
    std::cout << t.size() << std::endl;

    return 0;
}