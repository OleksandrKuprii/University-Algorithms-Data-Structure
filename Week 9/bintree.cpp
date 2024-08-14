//
// Created by Saxion on 4/10/2021.
//

#include "bintree.h"
#include "bintree_writer.h"

bintree::bintree(const bintree_node *root) :
    m_root{deep_copy(root)},
    m_sentinel{new bintree_node{0}}
{
    m_sentinel->set_right(m_root);
}

bintree::~bintree() {
    deallocate(m_sentinel);
}

bintree::bintree(const bintree &tree) {
    m_sentinel = bintree::deep_copy(tree.m_sentinel);
    update_root();
}

bintree::bintree(bintree &&tree) {
    m_sentinel = tree.m_sentinel;
    m_root = tree.m_root;
    tree.m_root = tree.m_sentinel = nullptr;
}

bintree &bintree::operator=(bintree tree) {
    std::swap(m_sentinel, tree.m_sentinel);
    std::swap(m_root, tree.m_root);
    return *this;
}

const bintree_node *bintree::root() const {
    return m_root;
}

bool bintree::contains(int value) const {
    return m_root == nullptr ? false : m_root->find(value) != nullptr;
}

bool bintree::insert(int value) {
    if (m_root == nullptr) {
        m_sentinel->m_right = m_root = new bintree_node{value, m_sentinel};
        return true;
    } else {
        auto ptr = m_root->insert(value);
        return ptr != nullptr;
    }
}

void bintree::insert(std::initializer_list<int> values) {
    for (auto value : values) insert(value);
}

bool bintree::remove(int value) {
    if (m_root == nullptr) {
        return false;
    } else {
        auto node = m_root->find(value);
        if (node != nullptr) {
            // remove node from tree & save pointer
            auto removed = node->remove();

            // release memory
            if (removed != nullptr) {
                delete removed;
                update_root();
            }

            // indicate that the tree has changed
            return true;
        } else {
            // nothing was deleted
            return false;
        }
    }
}

const bintree_node *bintree::minimum() const {
    if (m_root == nullptr)
        return nullptr; // empty tree, so there is no minimum
    else
        return &m_root->minimum();  // delegate to the bintree_node
}

bintree &bintree::operator<<(int value) {
    insert(value);
    return *this;
}

bintree::operator bool() const {
    return m_root != nullptr;
}

void bintree::update_root() {
    if (m_sentinel->m_left == nullptr)
        m_root = m_sentinel->m_right;
    else
        m_root = m_sentinel->m_left;
}

bintree_node *bintree::deep_copy(const bintree_node *node) {
    if (node == nullptr)
        return nullptr;

    auto root = new bintree_node{node->value()};
    root->set_left(deep_copy(node->left()));
    root->set_right(deep_copy(node->right()));
    return root;
}

void bintree::deallocate(const bintree_node *node) {
    if (node != nullptr) {
        deallocate(node->left());
        deallocate(node->right());
        delete node;
    }
}

std::ostream &operator<<(std::ostream &os, const bintree &tree) {
    bintree_writer::write_dot(os, tree);
    return os;
}

