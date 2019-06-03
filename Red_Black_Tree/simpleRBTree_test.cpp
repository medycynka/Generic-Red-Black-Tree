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

    if(tree.isEmpty()) cout << "Tree is empty" << endl << endl;

    for(auto i = 0; i < 20; i++){
        tree.Insert(i);
    }

    tree.Display();
    cout << endl;
    cout << (tree.T_find(3) ? "Found 3" : "Couldn't find 3") << endl;
    tree.Delete(3);
    cout << (tree.T_find(3) ? "Found 3" : "Couldn't find 3") << endl;
    cout << endl;

    cout << "Number of nodes: " << tree.Size() << endl;

    cout << "Testing iterators:" << endl;
    cout << "******************" << endl;
    cout << "Normal iterator:" << endl;

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
    cout << "Const iterator:" << endl;

    for(const auto &e : tree){
        cout<< e << ", ";
    }

    cout << endl;
    cout << "Reverse iterator:" << endl;

    for(auto it = tree.rbegin(); it != tree.rend(); it++){
        cout << *it << ", ";
    }

    cout << endl;

    for(auto it = tree.rbegin(); it != tree.rend(); ++it){
        cout << *it << ", ";
    }

    RBTree<int> tree2 = tree;
    cout << endl;

    for(auto it = tree2.rbegin(); it != tree2.rend(); ++it){
        cout << *it << ", ";
    }

    cout << endl << endl << endl;

    cout << "Insert and search test for " << test1 << " elements" << endl;
    auto start1_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        tree.Insert(i);
    }
    auto end1_1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end1_1 - start1_1;
    cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << endl;

    auto start1_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i){
        tree.T_find(i);
    }
    auto end1_2 = std::chrono::system_clock::now();
    elapsed_seconds = end1_2 - start1_2;
    cout << "Found all of " << test1 << " elements in " << elapsed_seconds.count() << "s" << endl << endl;

    cout << "Insert and search test for " << test2 << " elements" << endl;
    auto start2_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        tree.Insert(i);
    }
    auto end2_1 = std::chrono::system_clock::now();
    elapsed_seconds = end2_1 - start2_1;
    cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count() << endl;

    auto start2_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i){
        tree.T_find(i);
    }
    auto end2_2 = std::chrono::system_clock::now();
    elapsed_seconds = end2_2 - start2_2;
    cout << "Found all of " << test2 << " elements in " << elapsed_seconds.count() << "s" << endl << endl;

    cout << "Insert and search test for " << test3 << " elements" << endl;
    auto start3_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        tree.Insert(i);
    }
    auto end3_1 = std::chrono::system_clock::now();
    elapsed_seconds = end3_1 - start3_1;
    cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << endl;

    auto start3_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i){
        tree.T_find(i);
    }
    auto end3_2 = std::chrono::system_clock::now();
    elapsed_seconds = end3_2 - start3_2;
    cout << "Found all of " << test3 << " elements in " << elapsed_seconds.count() << "s" << endl << endl;

    cout << "Insert and search test for " << test4 << " elements" << endl;
    auto start4_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        tree.Insert(i);
    }
    auto end4_1 = std::chrono::system_clock::now();
    elapsed_seconds = end4_1 - start4_1;
    cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << endl;

    auto start4_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i){
        tree.T_find(i);
    }
    auto end4_2 = std::chrono::system_clock::now();
    elapsed_seconds = end4_2 - start4_2;
    cout << "Found all of " << test4 << " elements in " << elapsed_seconds.count() << "s" << endl << endl;

    return 0;
}
