#include <iostream>
#include <cassert>
#include "graph.h"
#include "shortest_paths.h"
#include "shortest_paths_tester.h"

int main() {
    auto g = graph::load("negative.graph");
    shortest_paths sps{g, "a"};
    sps.compute();
    sps.to_dot("negative.dot");
}
