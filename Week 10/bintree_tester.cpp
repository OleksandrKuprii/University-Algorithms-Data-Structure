//
// Created by Saxion on 4/11/2021.
//

#include "bintree_tester.h"
#include "bintree.h"
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
#ifdef __WEEK_9__
    bool heights_ok = validate_heights(&node);
#endif
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
#ifdef __WEEK_9__
    if (!heights_ok) {
        std::cerr << "Heights: FAIL" << std::endl;
    }
    else {
        std::cerr << "Heights: PASS" << std::endl;
    }
#endif
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

#ifdef __WEEK_9__
bool bintree_tester::validate_heights(const bintree_node *node) {
    if (node == nullptr)
        return true;

    if (!validate_heights(node->left()) || !validate_heights(node->right()))
        return false;

    if (node->m_height != height(node)) {
        std::cerr << "Value " << node->m_value << " has height " << height(node) << ", but its m_height member says height is " << node->m_height << std::endl;
        return false;
    }

    return true;
}
#endif

int bintree_tester::smallest_value(const bintree_node &node) {
    int minval = node.m_value;

    if (node.m_left != nullptr)
        minval = std::min(minval, smallest_value(*node.m_left));

    if (node.m_right != nullptr)
        minval = std::min(minval, smallest_value(*node.m_right));

    return minval;
}

#ifdef __WEEK_9__
int bintree_tester::height(const bintree_node *node) {
    if (node == nullptr)
        return -1;
    else
        return std::max(height(node->left()), height(node->right())) + 1;
}
#endif

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

void bintree_tester::test_update_height() {
    bintree tree{};
    tree << 42;
    assert(tree.root()->height() == 1);

    tree << 30;
    assert(tree.root()->height() == 2);
    assert(tree.root()->left()->height() == 1);

    tree << 142;
    assert(tree.root()->height() == 2);
    assert(tree.root()->right()->height() == 1);

    tree << 36;
    assert(tree.root()->height() == 3);
    assert(tree.root()->left()->height() == 2);
    assert(tree.root()->left()->right()->height() == 1);

    tree << 84;
    assert(tree.root()->height() == 3);
    assert(tree.root()->right()->height() == 2);
    assert(tree.root()->right()->left()->height() == 1);

    tree << 24;
    assert(tree.root()->height() == 3);
    assert(tree.root()->left()->height() == 2);
    assert(tree.root()->left()->left()->height() == 1);
    assert(tree.root()->left()->right()->height() == 1);

    tree << 39;
    assert(tree.root()->height() == 4);
    assert(tree.root()->left()->height() == 3);
    assert(tree.root()->left()->left()->height() == 1);
    assert(tree.root()->left()->right()->height() == 2);
    assert(tree.root()->left()->right()->right()->height() == 1);

    std::cerr << "bintree_tester::test_update_height() PASS" << std::endl;
}

void bintree_tester::test_compute_balance() {
    bintree tree{};
    tree << 42;
    assert(tree.root()->balance() == 0);

    tree << 30;
    assert(tree.root()->balance() == -1);
    assert(tree.root()->left()->balance() == 0);

    tree << 142;
    assert(tree.root()->balance() == 0);
    assert(tree.root()->right()->balance() == 0);

    tree << 36;
    assert(tree.root()->balance() == -1);
    assert(tree.root()->left()->balance() == 1);
    assert(tree.root()->left()->right()->balance() == 0);

    tree << 84;
    assert(tree.root()->balance() == 0);
    assert(tree.root()->right()->balance() == -1);
    assert(tree.root()->right()->left()->balance() == 0);

    tree << 24;
    assert(tree.root()->balance() == 0);
    assert(tree.root()->left()->balance() == 0);
    assert(tree.root()->left()->left()->balance() == 0);
    assert(tree.root()->left()->right()->balance() == 0);

    tree << 39;
    assert(tree.root()->balance() == -1);
    assert(tree.root()->left()->balance() == 1);
    assert(tree.root()->left()->left()->balance() == 0);
    assert(tree.root()->left()->right()->balance() == 1);
    assert(tree.root()->left()->right()->right()->balance() == 0);

    std::cerr << "bintree_tester::test_compute_balance() PASS" << std::endl;
}

void bintree_tester::test_rotate_left() {

    bintree_node root{7}, l{3}, ll{2}, lr{5}, r{13}, rl{11}, rr{17}, sentinel{-1};
    sentinel.set_right(&root);
    root.set_left(&l);
    root.set_right(&r);
    r.set_left(&rl);
    r.set_right(&rr);
    l.set_left(&ll);
    l.set_right(&lr);
    for (auto ptr : {&l, &r, &root}) ptr->update_height();

    root.rotate_left();

    assert(root.parent() == &r);
    assert(root.parent()->left() == &root);
    assert(root.parent()->right() == &rr);
    assert(root.parent()->right()->is_leaf());
    assert(root.left() == &l);
    assert(root.right() == &rl);
    assert(root.right()->is_leaf());
    assert(root.left()->left() == &ll);
    assert(root.left()->left()->is_leaf());
    assert(root.left()->right() == &lr);
    assert(root.left()->right()->is_leaf());

    assert(root.left()->left()->value() == 2);
    assert(root.left()->value() == 3);
    assert(root.left()->right()->value() == 5);
    assert(root.value() == 7);
    assert(root.right()->value() == 11);
    assert(root.parent()->value() == 13);
    assert(root.parent()->right()->value() == 17);

    assert(root.left()->left()->height() == 1);
    assert(root.left()->right()->height() == 1);
    assert(root.right()->height() == 1);
    assert(root.left()->height() == 2);
    assert(root.height() == 3);
    assert(root.parent()->height() == 4);
    assert(root.parent()->right()->height() == 1);

    std::cerr << "bintree_tester::test_rotate_left() PASS" << std::endl;
}

void bintree_tester::test_rotate_right() {
    bintree_node root{7}, l{3}, ll{2}, lr{5}, r{13}, rl{11}, rr{17}, sentinel{-1};
    sentinel.set_right(&root);
    root.set_left(&l);
    root.set_right(&r);
    r.set_left(&rl);
    r.set_right(&rr);
    l.set_left(&ll);
    l.set_right(&lr);
    for (auto ptr : {&l, &r, &root}) ptr->update_height();

    root.rotate_right();

    assert(root.parent() == &l);
    assert(root.parent()->left() == &ll);
    assert(root.parent()->right() == &root);
    assert(root.parent()->left()->is_leaf());
    assert(root.right() == &r);
    assert(root.left() == &lr);
    assert(root.left()->is_leaf());
    assert(root.right()->left() == &rl);
    assert(root.right()->right() == &rr);
    assert(root.right()->left()->is_leaf());
    assert(root.right()->right()->is_leaf());

    assert(root.parent()->left()->value() == 2);
    assert(root.parent()->value() == 3);
    assert(root.left()->value() == 5);
    assert(root.value() == 7);
    assert(root.right()->left()->value() == 11);
    assert(root.right()->value() == 13);
    assert(root.right()->right()->value() == 17);

    assert(root.right()->right()->height() == 1);
    assert(root.right()->left()->height() == 1);
    assert(root.left()->height() == 1);
    assert(root.right()->height() == 2);
    assert(root.height() == 3);
    assert(root.parent()->height() == 4);
    assert(root.parent()->left()->height() == 1);

    std::cerr << "bintree_tester::test_rotate_right() PASS" << std::endl;
}

void bintree_tester::test_fix_left_heavy() {
    {
        // case 1: left subtree has a balance of -1
        bintree_node root{11}, l{5}, ll{3}, lr{7}, lll{2}, r{13}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_left(&l);
        root.set_right(&r);
        l.set_left(&ll);
        l.set_right(&lr);
        ll.set_left(&lll);
        ll.update_height();
        l.update_height();
        root.update_height();

        assert(root.balance() == -2);
        assert(l.balance() == -1);

        root.fix_left_heavy();

        assert(root.parent() == &l);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &ll);
        assert(root.parent()->left()->left() == &lll);
        assert(!root.parent()->left()->has_right_child());
        assert(root.parent()->left()->left()->is_leaf());
        assert(root.left() == &lr);
        assert(root.left()->is_leaf());
        assert(root.right() == &r);
        assert(root.right()->is_leaf());
    }

    // case 2: left subtree has a balance of 0
    {
        bintree_node root{11}, l{3}, ll{2}, lr{5}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_left(&l);
        l.set_left(&ll);
        l.set_right(&lr);
        l.update_height();
        root.update_height();

        assert(root.balance() == -2);
        assert(l.balance() == 0);

        root.fix_left_heavy();

        assert(root.parent() == &l);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &ll);
        assert(root.parent()->left()->is_leaf());
        assert(!root.left()->has_right_child());
        assert(root.left() == &lr);
        assert(root.left()->is_leaf());
    }

    {
        // case 3: left subtree has a balance of +1
        bintree_node root{11}, l{3}, ll{2}, lr{5}, lrr{7}, r{13}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_left(&l);
        root.set_right(&r);
        l.set_left(&ll);
        l.set_right(&lr);
        lr.set_right(&lrr);
        lr.update_height();
        l.update_height();
        root.update_height();

        assert(root.balance() == -2);
        assert(l.balance() == 1);

        root.fix_left_heavy();

        assert(root.parent() == &lr);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &l);
        assert(!root.parent()->left()->has_right_child());
        assert(root.parent()->left()->left() == &ll);
        assert(root.parent()->left()->left()->is_leaf());
        assert(root.left() == &lrr);
        assert(root.right() == &r);
        assert(root.left()->is_leaf());
        assert(root.right()->is_leaf());
    }
    std::cerr << "bintree_tester::test_fix_left_heavy() PASS" << std::endl;
}

void bintree_tester::test_fix_right_heavy() {
    {
        // case 1: right subtree has a balance of +1
        bintree_node root{3}, l{2}, rl{5}, r{7}, rr{11}, rrr{13}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_left(&l);
        root.set_right(&r);
        r.set_left(&rl);
        r.set_right(&rr);
        rr.set_right(&rrr);
        for (auto ptr : {&rr, &r, &root}) ptr->update_height();

        assert(root.balance() == 2);
        assert(r.balance() == 1);

        root.fix_right_heavy();

        assert(root.parent() == &r);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &root);
        assert(root.parent()->right() == &rr);
        assert(root.parent()->right()->right() == &rrr);
        assert(root.left() == &l);
        assert(root.right() == &rl);
        assert(root.left()->is_leaf());
        assert(root.right()->is_leaf());
        assert(!root.parent()->right()->has_left_child());
        assert(root.parent()->right()->right()->is_leaf());
    }

    {
        // case 2: right subtree has a balance of 0
        bintree_node root{3}, r{7}, rl{5}, rr{11}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_right(&r);
        r.set_left(&rl);
        r.set_right(&rr);
        r.update_height();
        root.update_height();

        assert(root.balance() == 2);
        assert(r.balance() == 0);

        root.fix_right_heavy();

        assert(root.parent() == &r);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &root);
        assert(root.parent()->right() == &rr);
        assert(root.parent()->right()->is_leaf());
        assert(root.left() == nullptr);
        assert(root.right() == &rl);
        assert(root.right()->is_leaf());
    }

    {
        // case 3: right subtree has a balance of -1
        bintree_node root{3}, l{2}, r{11}, rl{7}, rr{13}, rll{5}, sentinel{-1};
        sentinel.set_right(&root);
        root.set_left(&l);
        root.set_right(&r);
        r.set_left(&rl);
        r.set_right(&rr);
        rl.set_left(&rll);
        for (auto ptr : {&rl, &r, &root}) ptr->update_height();

        assert(root.balance() == 2);
        assert(r.balance() == -1);

        root.fix_right_heavy();

        assert(root.parent() == &rl);
        assert(root.parent()->parent() == &sentinel);
        assert(root.parent()->left() == &root);
        assert(root.parent()->right() == &r);
        assert(root.parent()->right()->left() == nullptr);
        assert(root.parent()->right()->right() == &rr);
        assert(root.parent()->right()->right()->is_leaf());
        assert(root.left() == &l);
        assert(root.right() == &rll);
        assert(root.left()->is_leaf());
        assert(root.right()->is_leaf());
    }

    std::cerr << "bintree_tester::test_fix_right_heavy() PASS" << std::endl;
}

