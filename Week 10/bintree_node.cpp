//
// Created by Saxion on 4/10/2021.
//

#include "bintree_node.h"
#include <vector>

// Week 10: updated constructor, initializes height to 1
bintree_node::bintree_node(int value, bintree_node *parent) :
        m_value{value}, m_left{}, m_right{}, m_parent{parent}, m_height{1} {
}

int bintree_node::value() const {
    return m_value;
}

const bintree_node *bintree_node::left() const {
    return m_left;
}

const bintree_node *bintree_node::right() const {
    return m_right;
}

const bintree_node *bintree_node::parent() const {
    return m_parent;
}

bool bintree_node::is_leaf() const {
    return m_left == nullptr && m_right == nullptr;
}

bool bintree_node::has_left_child() const {
    return m_left != nullptr;
}

bool bintree_node::has_right_child() const {
    return m_right != nullptr;
}

void bintree_node::set_left(bintree_node *new_left) {
    m_left = new_left;
    if (m_left != nullptr)
        m_left->m_parent = this;
}

void bintree_node::set_right(bintree_node *new_right) {
    m_right = new_right;
    if (m_right != nullptr)
        m_right->m_parent = this;
}

void bintree_node::replace_child(const bintree_node *child, bintree_node *new_child) {
    if (child == nullptr) {
        throw std::invalid_argument(
                "can't replace non-existing (nullptr) child of node[" + std::to_string(m_value) + "]");
    } else if (m_left == child)
        set_left(new_child);
    else if (m_right == child)
        set_right(new_child);
    else
        throw std::invalid_argument(
                "node[" + std::to_string(child->m_value) + "] is not a child of node[" + std::to_string(m_value) + "]");
}

int bintree_node::height() const {
    return m_height;
}

void bintree_node::rebalance() {
    // find out if tree is unbalanced
    if (balance() == -2) {
        // (sub)tree is left-heavy, fix it
        fix_left_heavy();
    } else if (balance() == 2) {
        fix_right_heavy();
    }
}

/// Activity 2: compute the height of a node given the heights of its child nodes
void bintree_node::update_height() {
    if (m_parent == nullptr)
        return;

    if (has_right_child() && has_left_child()) {
        if (m_left->m_height > m_right->m_height) {
            m_height = m_left->m_height + 1;
        } else {
            m_height = m_right->m_height + 1;
        }
    }
    else if (has_left_child())
        m_height = m_left->m_height + 1;
    else if (has_right_child())
        m_height = m_right->m_height + 1;
    else
        m_height = 1;

    return m_parent->update_height();
}

/// Activity 4: compute & return the balance factor of the tree rooted in this node
int bintree_node::balance() const {
    if (has_left_child() && has_right_child())
        return m_right->height() - m_left->height();
    else if (has_left_child())
        return (-1) * m_left->height();
    else if (has_right_child())
        return m_right->height();
    return 0;
}

/// Activity 6: Left-rotates the tree rooted in this node
void bintree_node::rotate_left() {
    counter++;
    auto parent = m_parent;
    auto r = m_right;
    auto rl = m_right->m_left;

    (void) parent;
    (void) r;
    (void) rl;

    if (rl != nullptr) {
        r->replace_child(rl, this);
        replace_child(r, rl);
    } else {
        r->m_left = this;
        m_right = nullptr;
    }
    parent->replace_child(this, r);
    r->update_height();
}

/// Activity 7: right-rotates the tree rooted in this node
void bintree_node::rotate_right() {
    counter++;
    auto parent = m_parent;
    auto l = m_left;
    auto lr = m_left->m_right;

    (void) parent;
    (void) l;
    (void) lr;

    if (lr != nullptr) {
        l->replace_child(lr, this);
        replace_child(l, lr);
    } else {
        l->m_right = this;
        m_left = nullptr;
    }

    parent->replace_child(this, l);
    l->update_height();
}

/// Activity 12: restores the balance of a left-heavy tree
void bintree_node::fix_left_heavy() {
    switch (m_left->balance()) {
        case 0:
        case -1:
            rotate_right();
            break;
        case +1:
            m_left->rotate_left();
            rotate_right();
            break;
    }
}

/// Activity 12: restores the balance of a right-heavy tree
void bintree_node::fix_right_heavy() {
    switch (m_right->balance()) {
        case 0:
        case +1:
            rotate_left();
            break;
        case -1:
            m_right->rotate_right();
            rotate_left();
            break;
    }
}

bintree_node *bintree_node::find(int value) {
    if (value == m_value) {
        return this;
    } else if (value > m_value) {
        if (has_right_child()) {
            return m_right->find(value);
        } else {
            return nullptr;
        }
    } else {
        if (has_left_child()) {
            return m_left->find(value);
        } else {
            return nullptr;
        }
    }
}

bintree_node* bintree_node::insert(int value) {
    if (value == m_value)
        return nullptr;
    else if (value < m_value) {
        if (has_left_child()) {
            return m_left->insert(value);
        } else {
            auto * node = new bintree_node{value};
            set_left(node);
            return node;
        }
    } else {
        if (has_right_child()) {
            return m_right->insert(value);
        } else {
            auto * node = new bintree_node{value};
            set_right(node);
            return node;
        }
    }
}

bintree_node *bintree_node::remove() {
    if (is_leaf()) {
        m_parent->replace_child(this, nullptr);
        return this;
    } else if (has_right_child() && !has_left_child()) {
        m_parent->replace_child(this, m_right);
        return this;
    } else if (has_left_child() && !has_right_child()) {
        m_parent->replace_child(this, m_left);
        return this;
    } else {
        auto& node = m_right->minimum();

        if (m_right != &node) {
            node.m_parent->m_left = nullptr;
            node.set_right(m_right);
        }
        node.set_left(m_left);

        m_parent->replace_child(this, &node);
        return this;
    }
}

bintree_node &bintree_node::minimum() {
    if (has_left_child()) {
        return m_left->minimum();
    }
    return *this;
}