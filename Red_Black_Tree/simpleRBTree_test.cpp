#include <iostream>
#include <iterator>
#include <chrono>
#include "simple_red_black_tree.hpp"

using namespace std;

const int test1 = 10000;        // 10^4
const int test2 = 100000;       // 10^5
const int test3 = 1000000;      // 10^6
const int test4 = 10000000;     // 10^7

int main(int argc, char* argv[]){
    RBTree<int> tree;

    if(tree.isEmpty()) std::cout << "Tree is empty" << std::endl << std::endl;

    for(auto i = 0; i < 20; i++){
        tree.Insert(i);
    }

    tree.Display();
    std::cout << std::endl;
    std::cout << (tree.T_find(3) ? "Found 3" : "Couldn't find 3") << std::endl;
    tree.Delete(3);
    std::cout << (tree.T_find(3) ? "Found 3" : "Couldn't find 3") << std::endl;
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

    for(auto it = tree.rbegin(); it != tree.rend(); ++it){
        std::cout << *it << ", ";
    }

    RBTree<int> tree2 = tree;
    std::cout << std::endl;

    for(auto it = tree2.rbegin(); it != tree2.rend(); ++it){
        std::cout << *it << ", ";
    }

    std::cout << std::endl;
    std::cout << std::endl << std::endl << std::endl;

    /**
     * Test for 10000 elements
     */
    RBTree<size_t> t1;
    std::cout << "Insert and search test for " << test1 << " elements" << std::endl;
    auto start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        t1.Insert(i);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i){
        t1.T_find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test1 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;


    /**
     * Test for 100000 elements
     */
    RBTree<size_t> t2;
    std::cout << "Insert and search test for " << test2 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        t2.Insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i){
        t2.T_find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test2 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;


    /**
     * Test for 1000000 elements
     */
    RBTree<size_t> t3;
    std::cout << "Insert and search test for " << test3 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        t3.Insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i){
        t3.T_find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test3 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;


    /**
     * Test for 10000000 elements
     */
    RBTree<size_t> t4;
    std::cout << "Insert and search test for " << test4 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        t4.Insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i){
        t4.T_find(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Found all of " << test4 << " elements in " << elapsed_seconds.count() << "s" << std::endl << std::endl;

    return 0;
}
