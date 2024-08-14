#include <iostream>
#include <cassert>
#include "bintree.h"
#include "bintree_writer.h"
#include "bintree_tester.h"

int main() {
    bintree_writer writer{};
    bintree tree;
    for (int i = 1; i <= 15; i++) {
        tree << i;
        writer.add_tree(tree, "Inserted " + std::to_string(i));
        }

    int c = 0;
    c += tree.root()->counter;
    c += tree.root()->left()->counter;
    c += tree.root()->left()->left()->counter;
    c += tree.root()->left()->left()->left()->counter;
    c += tree.root()->left()->left()->right()->counter;
    c += tree.root()->left()->right()->counter;
    c += tree.root()->left()->right()->left()->counter;
    c += tree.root()->left()->right()->right()->counter;
    c += tree.root()->right()->counter;
    c += tree.root()->right()->left()->counter;
    c += tree.root()->right()->left()->left()->counter;
    c += tree.root()->right()->left()->right()->counter;
    c += tree.root()->right()->right()->counter;
    c += tree.root()->right()->right()->left()->counter;
    c += tree.root()->right()->right()->right()->counter;

    std::cout << c;
    writer.write_dot("activity-13.dot");
}
