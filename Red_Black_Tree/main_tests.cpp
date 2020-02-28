#include "rb_tree.hpp"
#include <vector>
#define BOOST_TEST_MODULE RBTree_Test

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(general_test_suite)
    BOOST_AUTO_TEST_CASE(constructor_tests){
        RBTree<int> t1;
        BOOST_CHECK(t1.isEmpty());
        BOOST_CHECK_EQUAL(t1.size(), 0);

        t1.insert(1);
        t1.insert(2);
        t1.insert(3);

        RBTree<int> t2 = t1;
        BOOST_CHECK_EQUAL(t2.isEmpty(), false);
        BOOST_CHECK_EQUAL(t2.size(), t1.size());
        t2.remove(3);

        RBTree<int> t3;
        t3 = t2;
        BOOST_CHECK_EQUAL(t3.isEmpty(), false);
        BOOST_CHECK_EQUAL(t3 == t2, false);
        BOOST_CHECK_EQUAL(t3 == t1, false);
        BOOST_CHECK_EQUAL(t3 != t1, true);
        BOOST_CHECK_EQUAL(t3.size() != t1.size(), true);
    }

    BOOST_AUTO_TEST_CASE(insert_remove_find_test){
        RBTree<int> tree;
        BOOST_CHECK(tree.isEmpty());

        for(auto i = 0; i < 10; ++i){
            tree.insert(i);
        }

        BOOST_CHECK_EQUAL(tree.isEmpty(), false);
        BOOST_CHECK_EQUAL(tree.size(), 10);

        BOOST_CHECK_EQUAL(tree.find(3), true);
        BOOST_CHECK_EQUAL(tree.find(11), false);
        BOOST_CHECK_EQUAL(tree.find(7), true);
        BOOST_CHECK_EQUAL(tree.find(0), true);
        BOOST_CHECK_EQUAL(tree.find(20), false);

        tree.remove(3);
        tree.remove(5);

        BOOST_CHECK_EQUAL(tree.size(), 8);
        BOOST_CHECK_EQUAL(tree.find(0), true);
        BOOST_CHECK_EQUAL(tree.find(3), false);
        BOOST_CHECK_EQUAL(tree.find(5), false);
        BOOST_CHECK_EQUAL(tree.find(4), true);

        tree.clear();
        BOOST_CHECK(tree.isEmpty());
        BOOST_CHECK_EQUAL(tree.size(), 0);
        BOOST_CHECK_EQUAL(tree.find(4), false);
        BOOST_CHECK_EQUAL(tree.find(8), false);
        BOOST_CHECK_EQUAL(tree.find(9), false);
    }

    BOOST_AUTO_TEST_CASE(iterators_test){
        RBTree<int> t;
        for(auto i = 0; i < 10; ++i){
            t.insert(i);
        }

        BOOST_CHECK_EQUAL(t.size(), 10);
        std::vector<int> normal = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> reverse = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::vector<int> checker;

        for(auto &node : t){
            checker.push_back(node);
        }

        BOOST_CHECK(checker == normal);

        checker.clear();

        for(auto rit = t.rbegin(); rit != t.rend(); ++rit){
            checker.push_back(*rit);
        }

        BOOST_CHECK(checker == reverse);

    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(typical_use)
    BOOST_AUTO_TEST_CASE(test_10000){
        RBTree<int> t;
        const auto number_of_elements = 10000;
        for(auto i = 0; i < number_of_elements; ++i){
            t.insert(i);
        }
        BOOST_CHECK_EQUAL(t.size(), 10000);
        BOOST_CHECK_EQUAL(t.find(2), true);
        BOOST_CHECK_EQUAL(t.find(123), true);
        BOOST_CHECK_EQUAL(t.find(2578), true);
        BOOST_CHECK_EQUAL(t.find(65), true);
        BOOST_CHECK_EQUAL(t.find(98), true);
        BOOST_CHECK_EQUAL(t.find(1000), true);
        BOOST_CHECK_EQUAL(t.find(9999), true);
        BOOST_CHECK_EQUAL(t.find(555), true);
        BOOST_CHECK_EQUAL(t.find(0), true);
        BOOST_CHECK_EQUAL(t.find(7655), true);

        t.clear();
        BOOST_CHECK(t.isEmpty());
        BOOST_CHECK_EQUAL(t.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(test_100000){
        RBTree<int> t;
        const auto number_of_elements = 100000;
        for(auto i = 0; i < number_of_elements; ++i){
            t.insert(i);
        }
        BOOST_CHECK_EQUAL(t.size(), 100000);
        BOOST_CHECK_EQUAL(t.find(2), true);
        BOOST_CHECK_EQUAL(t.find(123), true);
        BOOST_CHECK_EQUAL(t.find(2578), true);
        BOOST_CHECK_EQUAL(t.find(657), true);
        BOOST_CHECK_EQUAL(t.find(938), true);
        BOOST_CHECK_EQUAL(t.find(1000), true);
        BOOST_CHECK_EQUAL(t.find(99999), true);
        BOOST_CHECK_EQUAL(t.find(555), true);
        BOOST_CHECK_EQUAL(t.find(10), true);
        BOOST_CHECK_EQUAL(t.find(76455), true);

        t.clear();
        BOOST_CHECK(t.isEmpty());
        BOOST_CHECK_EQUAL(t.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(test_1000000){
        RBTree<int> t;
        const auto number_of_elements = 1000000;
        for(auto i = 0; i < number_of_elements; ++i){
            t.insert(i);
        }
        BOOST_CHECK_EQUAL(t.size(), 1000000);
        BOOST_CHECK_EQUAL(t.find(2), true);
        BOOST_CHECK_EQUAL(t.find(3123), true);
        BOOST_CHECK_EQUAL(t.find(2578), true);
        BOOST_CHECK_EQUAL(t.find(6576), true);
        BOOST_CHECK_EQUAL(t.find(9812), true);
        BOOST_CHECK_EQUAL(t.find(10300), true);
        BOOST_CHECK_EQUAL(t.find(999999), true);
        BOOST_CHECK_EQUAL(t.find(555), true);
        BOOST_CHECK_EQUAL(t.find(0), true);
        BOOST_CHECK_EQUAL(t.find(7655), true);

        t.clear();
        BOOST_CHECK(t.isEmpty());
        BOOST_CHECK_EQUAL(t.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(test_10000000){
        RBTree<int> t;
        const auto number_of_elements = 10000000;
        for(auto i = 0; i < number_of_elements; ++i){
            t.insert(i);
        }
        BOOST_CHECK_EQUAL(t.size(), 10000000);
        BOOST_CHECK_EQUAL(t.find(2), true);
        BOOST_CHECK_EQUAL(t.find(123), true);
        BOOST_CHECK_EQUAL(t.find(2578), true);
        BOOST_CHECK_EQUAL(t.find(6501), true);
        BOOST_CHECK_EQUAL(t.find(983), true);
        BOOST_CHECK_EQUAL(t.find(16000), true);
        BOOST_CHECK_EQUAL(t.find(9999999), true);
        BOOST_CHECK_EQUAL(t.find(555), true);
        BOOST_CHECK_EQUAL(t.find(0), true);
        BOOST_CHECK_EQUAL(t.find(7655), true);

        t.clear();
        BOOST_CHECK(t.isEmpty());
        BOOST_CHECK_EQUAL(t.size(), 0);
    }
BOOST_AUTO_TEST_SUITE_END()