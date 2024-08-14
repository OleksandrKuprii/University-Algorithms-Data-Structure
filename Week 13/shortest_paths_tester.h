//
// Created by rgr24 on 31/05/2021.
//

#ifndef GRAPHS_FULL_SHORTEST_PATHS_TESTER_H
#define GRAPHS_FULL_SHORTEST_PATHS_TESTER_H


#include "shortest_paths.h"

class shortest_paths_tester {
public:
    static bool test_relax();
    static bool test_scan_all();
    static bool test_find_next_dijkstra();
    static bool verify_paths(shortest_paths& paths);
};


#endif //GRAPHS_FULL_SHORTEST_PATHS_TESTER_H
