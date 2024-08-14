//
// Created by rgr24 on 28/05/2021.
//

#include "path_data.h"
#include <algorithm>

path_data::path_data(int distance, const std::string &via)
        : m_distance{distance},
          m_via{via} {
}

int path_data::distance() const {
    return m_distance;
}

const std::string &path_data::via() const {
    return m_via;
}

void path_data::set_distance(const std::string &via_vertex, int distance) {
    m_distance = distance;
    m_via = via_vertex;
}

