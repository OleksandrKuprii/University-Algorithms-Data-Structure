//
// Created by rgr24 on 03/06/2021.
//

#ifndef GRAPHS_FULL_HEAP_DATA_H
#define GRAPHS_FULL_HEAP_DATA_H

#include "path_data.h"

/// A heap that orders vertices by their (current known) shortest distance
class vertex_heap {
public:
    // returns true if the heap is empty, false otherwise
    bool empty() const;

    // returns the vertex that lies at the shortest distance
    std::string min() const;

    // inserts a vertex and its associated distance
    void insert(const std::string& vertex, int distance);

    // removes the vertex that lies at the shortest distance
    void delete_min();

private:
    std::vector<std::pair<int, std::string>> m_data;
};

#endif //GRAPHS_FULL_HEAP_DATA_H
