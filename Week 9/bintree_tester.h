//
// Created by Saxion on 4/11/2021.
//

#ifndef BSTS_BINTREE_TESTER_H
#define BSTS_BINTREE_TESTER_H

#include "bintree_node.h"

class range {
private:
    range(bool has_lb, bool has_ub, int lb = 0, int ub = 0 );
public:
    bool has_lower_bound() const;
    bool has_upper_bound() const;
    int lower_bound() const;
    int upper_bound() const;
    range from(int lo) const;
    range to(int hi) const;
    static range at_least(int lo);
    static range at_most(int hi);
    static range between(int lo, int hi);
    static range open();
private:
    bool m_has_lower, m_has_upper;
    int m_lower_bound, m_upper_bound;
};

class bintree_tester {
public:
    static void test_find_value();
    static void test_insert();
    static void test_find_minimum();
    static void test_remove_leaf();
    static void test_remove_nonfull_node();
    static void test_remove_full_node();

    static bool validate(const bintree& tree);
    static bool validate(const bintree_node* node);
    static bool validate(const bintree_node& node);
    static bool validate_structure(const bintree_node* node);
    static bool validate_heights(const bintree_node* node);
    static bool validate_range(const bintree_node* node, const range& range);
    static int smallest_value(const bintree_node& node);

};


#endif //BSTS_BINTREE_TESTER_H
