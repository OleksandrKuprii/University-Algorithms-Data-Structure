//
// Created by Saxion on 4/10/2021.
//
#ifndef BSTS_BINTREE_H
#define BSTS_BINTREE_H

#include "bintree_node.h"
#include <ostream>
#include <map>
#include <set>

class bintree {
public:
    // constructor
    bintree(const bintree_node* root = nullptr);

    // destructor - releases memory of all the nodes in the tree
    ~bintree();

    // copy constructor - makes a deep copy of the tree
    bintree(const bintree&);

    // move constructor
    bintree(bintree&&);

    // copy assignment operator - releases memory & makes a deep copy of the other tree
    bintree& operator=(bintree);

    // returns the root of the tree
    const bintree_node* root() const;

    // Returns true if the value is contained in the tree, false otherwise
    bool contains(int value) const;

    // If the tree does not yet contain the value, then insert the value into the tree & return true.
    // Returns false if the tree already contains the value
    bool insert(int value);

    // overload of insert to insert multiple values (in the order given by the list)
    void insert(std::initializer_list<int> values);

    // Removes the value from the tree. Returns true if the value was indeed present and is now removed, false
    // otherwise
    bool remove(int value);

    // Returns a pointer to the node that contains the minimum value, or nullptr if there are no nodes in the tree.
    const bintree_node* minimum() const;

    // Returns true if the tree contains at least one node, false otherwise
    operator bool() const;

    // Inserts the value into the tree, delegates to bintree::insert(int)
    bintree& operator<<(int value);
private:
    // Used to ensure that the sentinel node is the parent of the root node
    void update_root();

    // performs a deep copy of the subtree rooted in node
    static bintree_node* deep_copy(const bintree_node* node);

    // recursively deallocates all the nodes in the tree
    static void deallocate(const bintree_node* node);

    // The true root of the tree
    bintree_node* m_root;

    // An auxiliary node to make sure that every node (including the root) has a parent node
    bintree_node* m_sentinel;
};

// stream output operator
std::ostream& operator<<(std::ostream& os, const bintree& tree);

#endif //BSTS_BINTREE_H
