//
// Created by Saxion on 4/11/2021.
//

#include "bintree_tester.h"
#include "bintree.h"
#include "bintree_writer.h"
#include <iostream>
#include <cassert>

range::range(bool has_lb, bool has_ub, int lb, int ub) :
        m_has_lower{has_lb}, m_has_upper{has_ub}, m_lower_bound{lb}, m_upper_bound{ub} {
}

bool range::has_lower_bound() const {
    return m_has_lower;
}

bool range::has_upper_bound() const {
    return m_has_upper;
}

int range::lower_bound() const {
    return m_lower_bound;
}

int range::upper_bound() const {
    return m_upper_bound;
}

range range::at_least(int lo) {
    return range{true, false, lo, 0};
}

range range::at_most(int hi) {
    return range{false, true, 0, hi};
}

range range::between(int lo, int hi) {
    return range{true, true, lo, hi};
}

range range::open() {
    return range{false, false};
}

range range::from(int lo) const {
    if (m_has_lower)
        return range(true, m_has_upper, std::max(lo, m_lower_bound), m_upper_bound);
    else
        return range(true, m_has_upper, lo, m_upper_bound);
}

range range::to(int hi) const {
    if (m_has_upper)
        return range(m_has_lower, true, m_lower_bound, std::min(hi, m_upper_bound));
    else
        return range(m_has_lower, true, m_lower_bound, hi);
}

bool bintree_tester::validate(const bintree& tree) {
    return validate(tree.root());
}

bool bintree_tester::validate(const bintree_node *node) {
    return validate(*node);
}

bool bintree_tester::validate(const bintree_node &node) {
    bool ranges_ok = validate_range(&node, range::open());
    bool structure_ok = validate_structure(&node);
    if (!ranges_ok) {
        std::cerr << "Order invariant: FAIL" << std::endl;
    }
    else {
        std::cerr << "Order invariant: PASS" << std::endl;
    }
    if (!structure_ok) {
        std::cerr << "Structural integrity: FAIL" << std::endl;
    }
    else {
        std::cerr << "Structural integrity: PASS" << std::endl;
    }
    return ranges_ok && structure_ok;
}

bool bintree_tester::validate_structure(const bintree_node *node) {
    if (node->m_left != nullptr) {
        if (node->m_left->m_parent == nullptr) {
            std::cerr << "Left node (" << node->m_left->m_value
                      << ") of node (" << node->m_value
                      << ") has a parent set to nullptr"
                      << std::endl;
        } else if (node->m_left->m_parent != node) {
            std::cerr << "Left node (" << node->m_left->m_value << ") of node (" << node->m_value
                      << ") has an invalid parent ()" << std::endl;
            std::cerr << "Left node () of node (" << node->m_value << ") has a bad parent ";
            return false;
        }
        if (!validate_structure(node->m_left))
            return false;
    }
    if (node->m_right != nullptr) {
        if (node->m_right->m_parent == nullptr) {
            std::cerr << "Right child (" << node->m_right->m_value
                      << ") of node (" << node->m_value
                      << ") has a parent set to nullptr"
                      << std::endl;
        } else if (node->m_right->m_parent != node) {
            std::cerr << "Right child (" << node->m_right->m_value << ") of node (" << node->m_value
                      << ") has an invalid parent (" << node->m_right->m_parent->m_value << ")" << std::endl;
            return false;
        }
        if (!validate_structure(node->m_right))
            return false;
    }
    return true;
}

bool bintree_tester::validate_range(const bintree_node *node, const range &range) {
    if (range.has_lower_bound() && node->m_value < range.lower_bound()) {
        std::cerr << "invariant does not hold: "
                  << node->m_value << " is smaller than " << range.lower_bound()
                  << ", so it can't be in the right subtree of " << range.lower_bound() << std::endl;
        return false;
    }
    if (range.has_upper_bound() && node->m_value > range.upper_bound()) {
        std::cerr << "invariant does not hold: "
                  << node->m_value << " is greater than " << range.upper_bound()
                  << ", so it can't be in the left subtree of " << range.upper_bound() << std::endl;
        return false;
    }
    if (node->m_left != nullptr && !validate_range(node->m_left, range.to(node->m_value))) {
        return false;
    }
    if (node->m_right != nullptr && !validate_range(node->m_right, range.from(node->m_value))) {
        return false;
    }
    return true;
}

int bintree_tester::smallest_value(const bintree_node &node) {
    int minval = node.m_value;

    if (node.m_left != nullptr)
        minval = std::min(minval, smallest_value(*node.m_left));

    if (node.m_right != nullptr)
        minval = std::min(minval, smallest_value(*node.m_right));

    return minval;
}

void bintree_tester::test_find_value() {
    // construct a binary search tree with five nodes
    bintree_node l{2}, lr{3}, root{5}, rll{7}, rl{11}, rlr{13}, r{17};
    root.set_left(&l);
    root.set_right(&r);
    l.set_right(&lr);
    r.set_left(&rl);
    rl.set_left(&rll);
    rl.set_right(&rlr);

    assert(root.find(5) == &root);
    assert(root.find(2) == &l);
    assert(root.find(3) == &lr);
    assert(root.find(17) == &r);
    assert(root.find(11) == &rl);
    assert(root.find(7) == &rll);
    assert(root.find(13) == &rlr);
    assert(root.find(1) == nullptr);
    assert(root.find(19) == nullptr);
    assert(root.find(15) == nullptr);

    std::cerr << "bintree_tester::test_find_value() PASS" << std::endl;
}

void bintree_tester::test_insert() {
    bintree tree{};
    tree.insert(3);
    assert(tree.root() != nullptr);
    assert(tree.root()->value() == 3);
    assert(tree.root()->left() == nullptr);
    assert(tree.root()->right() == nullptr);

    tree.insert(2);
    assert(tree.root()->value() == 3);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 2);
    assert(tree.root()->right() == nullptr);

    tree.insert(5);
    assert(tree.root()->value() == 3);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 2);
    assert(tree.root()->right() != nullptr);
    assert(tree.root()->right()->value() == 5);

    tree.insert(7);
    assert(tree.root()->value() == 3);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 2);
    assert(tree.root()->right() != nullptr);
    assert(tree.root()->right()->value() == 5);
    assert(tree.root()->right()->left() == nullptr);
    assert(tree.root()->right()->right() != nullptr);
    assert(tree.root()->right()->right()->value() == 7);

    tree.insert(1);
    assert(tree.root()->value() == 3);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 2);
    assert(tree.root()->left()->right() == nullptr);
    assert(tree.root()->left()->left() != nullptr);
    assert(tree.root()->left()->left()->value() == 1);

    std::cerr << "bintree_tester::test_insert() PASS" << std::endl;
}

void bintree_tester::test_find_minimum() {
    bintree tree{};
    assert(tree.minimum() == nullptr);

    tree << 42;
    assert(tree.minimum() != nullptr);
    assert(tree.minimum()->value() == 42);

    tree << 23 << 31;
    assert(tree.minimum() != nullptr);
    assert(tree.minimum()->value() == 23);

    tree << 17 << 67;
    assert(tree.minimum()->value() == 17);

    tree << 15 << 62 << 61 << 71 << 68 << 79;
    assert(tree.minimum()->value() == 15);

    std::cerr << "bintree_tester::test_find_minimum() PASS" << std::endl;
}

void bintree_tester::test_remove_leaf() {
    bintree tree{};
    assert(!tree.remove(42));

    tree << 42;
    assert(tree.remove(42));
    assert(!tree.contains(42));
    assert(tree.root() == nullptr);

    tree << 42 << 23 << 67;
    assert(tree.remove(23));
    assert(!tree.contains(23));
    assert(tree.root() != nullptr);
    assert(tree.root()->left() == nullptr);
    assert(tree.root()->right() != nullptr);
    assert(tree.root()->right()->value() == 67);

    assert(tree.remove(67));
    assert(!tree.contains(67));
    assert(tree.root() != nullptr);
    assert(tree.root()->left() == nullptr);
    assert(tree.root()->right() == nullptr);

    assert(tree.remove(42));
    assert(!tree.contains(42));
    assert(tree.root() == nullptr);

    std::cerr << "bintree_tester::test_remove_leaf() PASS" << std::endl;
}

void bintree_tester::test_remove_nonfull_node() {
    bintree tree{};
    tree << 42 << 23 << 31 << 67 << 62;
    assert(tree.remove(23));
    assert(!tree.contains(23));

    assert(tree.root() != nullptr);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 31);
    assert(tree.root()->left()->left() == nullptr);
    assert(tree.root()->left()->right() == nullptr);

    assert(tree.remove(67));
    assert(!tree.contains(67));
    assert(tree.root() != nullptr);
    assert(tree.root()->right() != nullptr);
    assert(tree.root()->right()->value() == 62);
    assert(tree.root()->right()->left() == nullptr);
    assert(tree.root()->right()->right() == nullptr);

    assert(tree.contains(42));
    assert(tree.contains(31));
    assert(tree.contains(62));

    std::cerr << "bintree_tester::test_remove_nonfull_node() PASS" << std::endl;
}

void bintree_tester::test_remove_full_node() {
    bintree tree{};
    tree << 42 << 23 << 31 << 67 << 62 << 17 << 71 << 61 << 68 << 79;
    bintree_writer::write_dot("a.dot", tree);
    assert(tree.remove(67));
    assert(!tree.contains(67));
    assert(tree.root() != nullptr);
    assert(tree.root()->right() != nullptr);
    assert(tree.root()->right()->value() == 68);
    assert(tree.root()->right()->right() != nullptr);
    assert(tree.root()->right()->right()->value() == 71);
    assert(tree.root()->right()->right()->left() == nullptr);

    assert(tree.remove(23));
    assert(!tree.contains(23));
    assert(tree.root() != nullptr);
    assert(tree.root()->left() != nullptr);
    assert(tree.root()->left()->value() == 31);
    assert(tree.root()->left()->right() == nullptr);

    assert(tree.contains(42));
    assert(tree.contains(31));
    assert(tree.contains(62));
    assert(tree.contains(17));
    assert(tree.contains(71));
    assert(tree.contains(61));
    assert(tree.contains(68));
    assert(tree.contains(79));

    std::cerr << "bintree_tester::test_remove_full_node() PASS" << std::endl;
}

