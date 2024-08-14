#include "vertex_heap.h"
#include <algorithm>

bool vertex_heap::empty() const {
    return m_data.empty();
}

std::string vertex_heap::min() const {
    if (m_data.empty()) throw std::logic_error("min: heap is empty");
    return m_data[0].second;
}

void vertex_heap::insert(const std::string &vertex, int distance) {
    // m_data is treated as a max-heap, so negate distances so that shortest ones
    // come first
    m_data.push_back(std::make_pair(-distance, vertex));
    std::push_heap(m_data.begin(), m_data.end());
}

void vertex_heap::delete_min() {
    if (m_data.empty()) throw std::logic_error("delete_min: heap is empty");
    std::pop_heap(m_data.begin(), m_data.end());
    m_data.pop_back();
}
