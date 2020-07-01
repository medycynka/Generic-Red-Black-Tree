#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "rb_tree.hpp"


constexpr int test1{ 10000 };        // 10^4
constexpr int test2{ 100000 };       // 10^5
constexpr int test3{ 1000000 };      // 10^6
constexpr int test4{ 10000000 };     // 10^7

int main() {
    // Simple test
    {
        rbt::RBTree<int> tree;
        if (tree.isEmpty()) std::cout << "Tree is empty" << "\n" << "\n";

        for (auto i = 0; i < 20; i++) {
            tree.insert(i);
        }

        tree.display();
        std::cout << "\n";
        std::cout << (tree.find(3) ? "Found 3" : "Couldn't find 3") << "\n";
        tree.remove(3);
        std::cout << (tree.find(3) ? "Found 3" : "Couldn't find 3") << "\n";

        std::cout << "\n";

        std::cout << "Number of nodes: " << tree.size() << "\n";

        std::cout << "Testing iterators:" << "\n";
        std::cout << "******************" << "\n";
        std::cout << "Normal iterator:" << "\n";

        for (auto it = tree.begin(); it != tree.end(); it++) {
            std::cout << *it << ", ";
        }

        std::cout << "\n";

        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << *it << ", ";
        }

        std::cout << "\n";

        for (auto& e : tree) {
            std::cout << e << ", ";
        }

        std::cout << "\n";
        std::cout << "Const iterator:" << "\n";

        for (const auto& e : tree) {
            std::cout << e << ", ";
        }

        std::cout << "\n";
        std::cout << "Reverse iterator:" << "\n";

        for (auto it = tree.rbegin(); it != tree.rend(); it++) {
            std::cout << *it << ", ";
        }

        std::cout << "\n";

        for (auto it = tree.crbegin(); it != tree.crend(); ++it) {
            std::cout << *it << ", ";
        }

        std::cout << "\n" << "\n" << "Testing operator[] (and node operator[]):" << "\n";
        std::cout << "for i = 1 key value = " << tree[1] << "\n";
        std::cout << "for i = 7 key value = " << tree[7] << "\n" << "\n";
        rbt::node_impl::RBNode<int> r(5);
        r.father = new rbt::node_impl::RBNode<int>(1);
        r.left = new rbt::node_impl::RBNode<int>(3);
        r.right = new rbt::node_impl::RBNode<int>(8);
        std::cout << "test node: " << "\n";
        r.print_node();
        std::cout << "in node for i = 0 (self) key value = " << r[0] << "\n";
        std::cout << "in node for i = 1 (father) key value = " << r[1] << "\n";
        std::cout << "in node for i = 2 (left) key value = " << r[2] << "\n";
        std::cout << "in node for i = 3 (right) key value = " << r[3] << "\n";

        std::cout << "\n" << "\n" << "\n" << "\n";
        rbt::RBTree<int> tree2 = tree;
        tree.remove(2);
        tree2.insert(42);
        std::cout << "\n";

        for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << "\n";
        for (auto it = tree2.rbegin(); it != tree2.rend(); ++it) {
            std::cout << *it << ", ";
        }

        std::cout << "\n" << "\n" << "\n" << "\n";

        rbt::RBTree<int> t;
        for (auto i = 0; i < 5; i++) t.insert(i);
        t.clear();
        t.display();
        std::cout << "\n" << t.size() << "\n";
        t.insert(2);
        t.insert(7);
        for (auto it = t.rbegin(); it != t.rend(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << "\n" << "\n" << "\n";
        t.clear();
    }

    // Performance test
    {
        /*
         * For best performance remove if statement (risking not detecting a bug)
         */
        rbt::RBTree<int> t;
        std::cout << std::setprecision(16) << std::fixed;
        /*
         * Test for 10000 elements
         */
        std::cout << "insert and search test for " << test1 << " elements" << "\n";
        auto start = std::chrono::system_clock::now();
        for (auto i = 0; i < test1; ++i) {
            t.insert(i);
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << "\n";

        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test1; ++i) {
            if (!t.find(i)) {
                std::cerr << "Error during rbt::RBTree<int>::find()" << "\n";
                break;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Found all of " << test1 << " elements in " << elapsed_seconds.count() << "s" << "\n" << "\n";
        t.clear();


        /*
         * Test for 100000 elements
         */
        std::cout << "insert and search test for " << test2 << " elements" << "\n";
        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test2; ++i) {
            t.insert(i);
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count() << "\n";

        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test2; ++i) {
            if (!t.find(i)) {
                std::cerr << "Error during rbt::RBTree<int>::find()" << "\n";
                break;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Found all of " << test2 << " elements in " << elapsed_seconds.count() << "s" << "\n" << "\n";
        t.clear();


        /*
         * Test for 1000000 elements
         */
        std::cout << "insert and search test for " << test3 << " elements" << "\n";
        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test3; ++i) {
            t.insert(i);
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << "\n";

        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test3; ++i) {
            if (!t.find(i)) {
                std::cerr << "Error during rbt::RBTree<int>::find()" << "\n";
                break;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Found all of " << test3 << " elements in " << elapsed_seconds.count() << "s" << "\n" << "\n";
        t.clear();


        /*
         * Test for 10000000 elements
         */
        std::cout << "insert and search test for " << test4 << " elements" << "\n";
        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test4; ++i) {
            t.insert(i);
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << "\n";

        start = std::chrono::system_clock::now();
        for (auto i = 0; i < test4; ++i) {
            if (!t.find(i)) {
                std::cerr << "Error during rbt::RBTree<int>::find()" << "\n";
                break;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Found all of " << test4 << " elements in " << elapsed_seconds.count() << "s" << "\n" << "\n";
        t.clear();

        std::cout << t.size() << "\n";
    }

    _sleep(5000);

	return 0;
}