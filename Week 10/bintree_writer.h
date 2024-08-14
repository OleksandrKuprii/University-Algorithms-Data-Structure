//
// Created by Saxion on 4/14/2021.
//

#ifndef BSTS_BINTREE_WRITER_H
#define BSTS_BINTREE_WRITER_H

#include <ostream>
#include <vector>
#include "bintree.h"

struct titled_tree {
    bintree tree;
    std::string title;
};

class bintree_writer {
public:
    void add_tree(bintree tree, const std::string& title);
    int write_dot(std::ostream &os) const;
    bool write_dot(const char* filename) const;
    void clear();

    static void write_dot(std::ostream &os, bintree_node& root);
    static void write_dot(std::ostream &os, const bintree& tree);
    static bool write_dot(const char* filename, bintree_node& tree);
    static bool write_dot(const char* filename, const bintree& tree);
private:
    static int height(const bintree_node* root);
    int write_nodes(std::ostream &os, const bintree_node* root, int idx, std::set<const bintree_node*>& visited) const;
    int write_edges(std::ostream &os, const bintree_node* root, int idx) const;

    std::vector<titled_tree> m_trees;
};

#endif //BSTS_BINTREE_WRITER_H
