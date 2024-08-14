//
// Created by Saxion on 4/10/2021.
//

#include "bintree_node.h"

bintree_node::bintree_node(int value, bintree_node *parent) :
        m_value{value}, m_left{}, m_right{}, m_parent{parent} {
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

/// Searches the subtree rooted at this node for the given value,
/// exploiting the fact that data is sorted.
/// \param value the value searched for
/// \return the node that contains the value, or nullptr if no node was found
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

/// Inserts the given value into the tree if the value is not yet present. Makes sure that the order invariant
/// is kept intact.
/// \param value the value to be inserted
/// \return a pointer to the node that was added, or nullptr if no node was added
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

/// Removes the value contained in this node from the tree. This means that either this
/// node or another node (in case this node is a full node) is removed
/// \return
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

/// Returns a reference to the node containing the smallest value of the subtree rooted at this node
/// \return a reference to the node containing the minimum value
bintree_node &bintree_node::minimum() {
    if (has_left_child()) {
        return m_left->minimum();
    }
    return *this;
}

