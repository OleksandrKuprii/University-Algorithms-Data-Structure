//
// Created by Saxion on 4/10/2021.
//
#ifndef BSTS_BINTREE_NODE_H
#define BSTS_BINTREE_NODE_H

#include <ostream>

class bintree;
class bintree_tester;

class bintree_node {
    friend class bintree;
    friend class bintree_tester;
public:
    bintree_node(int value, bintree_node* parent = nullptr);
    //bintree_node(int value, bintree_node* left, bintree_node* right);

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

    // Activity 4
    // searches the tree rooted at this node for the node that contains the given value.
    // returns its address if found, otherwise nullptr
    bintree_node* find(int value);

    // Activity 5
    // returns false if the tree rooted at this node contains the value. Otherwise,
    // inserts the value in the tree rooted at this node, such that the tree's
    // invariant is maintained
    bintree_node* insert(int value);

    // Activities 8, 9 and 11
    // removes the value stored in this node from the tree, which may involve
    // removing the node itself from the tree
    // returns a pointer to the node that is removed from the tree
    bintree_node* remove();

    // replaces the given (left or right) child node with the new_child node
    void replace_child(const bintree_node* child, bintree_node* new_child);
    void set_left(bintree_node* new_left);
    void set_right(bintree_node* new_right);
private:
    // Activity 7: find minimum
    // returns the node that contains the lowest value in the tree rooted at this node
    bintree_node& minimum();

    int m_value;
    bintree_node* m_left;
    bintree_node* m_right;
    bintree_node* m_parent;
};


#endif //BSTS_BINTREE_NODE_H
