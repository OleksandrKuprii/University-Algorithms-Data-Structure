#include <iostream>
#include <cassert>
#include "graph.h"
#include "colours.h"
#include "visitor.h"

void label_pre_order(graph& g, const visitor& vis) {
    for (size_t i = 0; i < vis.pre_order().size(); i++) {
        g.label_vertex(vis.pre_order()[i], (long long) i);
    }
}

int main() {
    auto g = graph::load("act11.graph");
    visitor vis{g, traversal_t::depth_first};
    vis.find_iterative("a", "");
    g.colour_vertices(vis.cycle(), colour::red);
    g.to_dot("colouredcycle.dot");
}
