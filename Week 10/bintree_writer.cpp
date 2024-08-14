//
// Created by Saxion on 4/14/2021.
//

#include "bintree_writer.h"
#include <fstream>
#include <cmath>
#include <iomanip>

void bintree_writer::add_tree(bintree tree, const std::string& title) {
    m_trees.push_back(titled_tree{ .tree = std::move(tree), .title = title} );
}

void bintree_writer::write_dot(std::ostream &os, bintree_node& root) {
    bintree_writer writer{};
    writer.add_tree( bintree{ &root }, "" );
    writer.write_dot(os);
}

void bintree_writer::write_dot(std::ostream &os, const bintree& tree) {
    bintree_writer writer{};
    writer.add_tree(tree, "");
    writer.write_dot(os);
}

bool bintree_writer::write_dot(const char *filename, bintree_node& root) {
    bintree_writer writer{};
    writer.add_tree( bintree{ &root }, "" );
    return writer.write_dot(filename);
}

bool bintree_writer::write_dot(const char *filename, const bintree& tree) {
    bintree_writer writer{};
    writer.add_tree(tree, "");
    return writer.write_dot(filename);
}

int bintree_writer::write_dot(std::ostream &os) const {
    os << "digraph G {" << std::endl;
    os << "\tnode [shape = record,height=.1];" << std::endl;
    std::set<const bintree_node*> visited;
    int idx = 1;
    for (auto& titledTree : m_trees) {
        os << "\tsubgraph cluster" << idx << " {" << std::endl;
        os << "\t\tlabel = " << std::quoted(titledTree.title) << std::endl;
        os << "\t\tfontsize = 18" << std::endl;
        os << "\t\tfontcolor = blue" << std::endl;
        if (titledTree.tree.root() != nullptr) {
            write_nodes(os, titledTree.tree.root(), idx, visited);
            idx = write_edges(os, titledTree.tree.root(), idx);
        }
        os << "\t}" << std::endl;
    }
    os << "}" << std::endl;
    return idx;
}

bool bintree_writer::write_dot(const char *filename) const {
    std::ofstream ofs{ filename };
    if (ofs.is_open()) {
        write_dot(ofs);
        return true;
    }
    return false;
}

void bintree_writer::clear() {
    m_trees.clear();
}

int bintree_writer::write_nodes(std::ostream& os, const bintree_node* root, int idx, std::set<const bintree_node*>& visited) const {
    if (visited.find(root) != visited.end())
        throw std::logic_error("ERROR! The tree contains a cycle!");

    visited.insert(root);
    os << "\t\ta" << idx << " [label=\"<l> | {<c> " << root->value();
#ifdef __WEEK_9__
    os << " | height: " << root->height() << " | balance: " << root->balance();
#endif
    os << "} | <r> \"]" << std::endl;
    idx++;
    if (root->left() != nullptr)
        idx = write_nodes(os, root->left(), idx, visited);
    if (root->right() != nullptr)
        idx = write_nodes(os, root->right(), idx, visited);
    return idx;
}

int bintree_writer::write_edges(std::ostream& os, const bintree_node* root, int idx) const {
    auto next_idx = idx + 1;
    if (root->left() != nullptr) {
        os << "\t\ta" << idx << ":l -> a" << next_idx << ":c" << std::endl;

        // write edges for left subtree
        next_idx = write_edges(os, root->left(), next_idx);
    }
    if (root->right() != nullptr) {
        os << "\t\ta" << idx << ":r -> a" << next_idx << ":c" << std::endl;
        next_idx = write_edges(os, root->right(), next_idx);
    }
    return next_idx;
}

