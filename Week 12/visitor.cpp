//
// Created by rgr24 on 18/05/2022.
//

#include "visitor.h"
#include <algorithm>
#include <vector>

visitor::visitor(const graph &graph, traversal_t traversal) : m_graph{graph}, m_traversal_type{traversal} {

}

bool visitor::find_recursive(const std::string &start_vertex, const string &goal) {
    // append start_vertex to pre order
    pre_visit(start_vertex);

    // get vertex ref from name
    auto& vertex = m_graph[start_vertex];

    if (vertex.name() == goal) {
        return true;
    }

    // go over the outgoing edges of the vertex
    for (auto& edge : vertex.edges()) {
        if (is_visited(edge.target()))
            continue;

        // continue traversal from the neighbour
        if (find_recursive(edge.target(), goal))
            return true;
    }
    // append start_vertex to post order
    post_visit(start_vertex);

    return false;
}

bool visitor::find_iterative(const string &start_vertex, const string &goal) {
    plan_vertex_visit(start_vertex);
    while (visits_planned()) {
        auto v = peek_next_visit();

        if (m_visited[v] == 0) {
            pre_visit(v);

            if (v == goal) {
                return true;
            }

            for (auto & edge : m_graph[v].edges()) {
                auto &target = edge.target();
                if (num_visits(target) == 1) {
                    cycle_detected(target);
                } else if (num_visits(target) == 0) {
                    plan_vertex_visit(target);
                    break;
                }
            }
        } else if (num_visits(v) == 1) {
            post_visit(v);
            pop_next_visit();
        }
    }

    return false;
}

const std::vector<string> &visitor::path() const {
    return m_path;
}

const std::vector<string> &visitor::pre_order() const {
    return m_pre_order;
}

const std::vector<string> &visitor::post_order() const {
    return m_post_order;
}

bool visitor::cycle_found() const {
    return m_cycle_found;
}

void visitor::reset() {
    m_visited.clear();
    m_pre_order.clear();
    m_post_order.clear();
    m_path.clear();
    m_cycle.clear();
    m_cycle_found = false;
}

void visitor::pre_visit(const string &vertex) {
    m_pre_order.push_back(vertex);
    m_path.push_back(vertex);
    inc_visits(vertex);
}

void visitor::post_visit(const string &vertex) {
    m_post_order.push_back(vertex);
    if (!m_path.empty()) m_path.pop_back();
}

bool visitor::is_visited(const string &vertex) const {
    return m_visited.contains(vertex);
}

void visitor::inc_visits(const string &vertex) {
    m_visited[vertex]++;
}

int visitor::num_visits(const string &vertex) const {
    if (auto it = m_visited.find(vertex); it != m_visited.end()) {
        return it->second;
    }
    else return 0;
}

void visitor::plan_vertex_visit(const string &to_vertex) {
    if (m_traversal_type == traversal_t::depth_first)
        m_planned_visits.push_back(to_vertex);
    else
        m_planned_visits.push_front(to_vertex);
}

bool visitor::visits_planned() const {
    return !m_planned_visits.empty();
}

const string &visitor::peek_next_visit() const {
    return m_planned_visits.back();
}

void visitor::pop_next_visit() {
    if (m_planned_visits.empty()) throw std::logic_error("pop_next_visit: there is no planned visit to cancel");
    m_planned_visits.pop_back();
}

void visitor::cycle_detected(const string &vertex) {
    m_cycle_found = true;
    m_cycle.clear();

    m_cycle.insert(vertex);
    for (auto it = m_path.rbegin(); it != m_path.rend(); ++it) {
        auto &v = *it;
        if (v == vertex) break;
        m_cycle.insert(v);
    }
}

std::unordered_set<string> visitor::cycle() {
    return m_cycle;
}

