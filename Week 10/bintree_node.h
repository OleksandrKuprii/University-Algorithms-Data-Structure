//
// Created by Saxion on 4/10/2021.
//
#ifndef BSTS_BINTREE_NODE_H
#define BSTS_BINTREE_NODE_H

#include <ostream>
#include <vector>

class bintree;
class bintree_tester;

class bintree_node {
    friend class bintree;
    friend class bintree_tester;
public:
    int counter = 0;
    bintree_node(int value, bintree_node* parent = nullptr);

    // copy ctor and copy assignment operator deleted
    bintree_node(const bintree_node& node) = delete;
    bintree_node& operator=(const bintree_node& node) = delete;

    int value() const;
    const bintree_node* left() const;
    const bintree_node* right() const;
    const bintree_node* parent() const;

    bool is_leaf() const;
    bool has_left_child() const;
    bool has_right_child() const;

    // FIXME: copy the implementation of week 9 for find, insert, remove
    bintree_node* find(int value);
    bintree_node* insert(int value);
    bintree_node* remove();

    // replaces the given (left or right) child node with the new_child node
    void replace_child(const bintree_node* child, bintree_node* new_child);
    void set_left(bintree_node* new_left);
    void set_right(bintree_node* new_right);

    int height() const;

    // Activity 2: return the height of a node
    void update_height();

    // Activity 4: return the balance factor of a node
    int balance() const;

    // Activities 6 and 7: left and right rotate a tree
    void rotate_left();
    void rotate_right();

    void rebalance();

    // Activity 12: rebalance a tree
    void fix_left_heavy();
    void fix_right_heavy();
private:
    // FIXME: copy the implementation from week 9
    bintree_node& minimum();

    int m_value;
    bintree_node* m_left;
    bintree_node* m_right;
    bintree_node* m_parent;

    // Week 10 member variables
    int m_height;
};


#endif //BSTS_BINTREE_NODE_H
