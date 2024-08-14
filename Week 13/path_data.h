//
// Created by rgr24 on 28/05/2021.
//

#ifndef GRAPHS_FULL_SHORTEST_PATH_DATA_H
#define GRAPHS_FULL_SHORTEST_PATH_DATA_H

#include "graph.h"
#include <limits>

class path_data {
public:
    path_data(int distance = VERY_FAR, const std::string &via = "");

    void set_distance(const std::string &via_vertex, int distance);

    int distance() const;
    const std::string &via() const;

    static const int VERY_FAR = std::numeric_limits<int>::max() / 4;
private:
    int m_distance;
    std::string m_via;
};


#endif //GRAPHS_FULL_SHORTEST_PATH_DATA_H
