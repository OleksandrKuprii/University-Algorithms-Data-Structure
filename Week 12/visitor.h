//
// Created by rgr24 on 18/05/2022.
//

#ifndef GRAPHS_FULL_VISITOR_H
#define GRAPHS_FULL_VISITOR_H

#include <deque>
#include <unordered_set>
#include "graph.h"

enum class traversal_t { depth_first, breadth_first };

using std::string;

class visitor {
public:
    visitor(const graph& graph, traversal_t traversal = traversal_t::depth_first);
    bool find_recursive(const string &start_vertex, const string &goal = "");
    bool find_iterative(const string &start_vertex, const string &goal = "");

    const std::vector<string>& path() const;

    const std::vector<string>& pre_order() const;

    const std::vector<string>& post_order() const;

    bool cycle_found() const;
    std::unordered_set<string> cycle();

    void reset();
    bool is_visited(const string& vertex) const;
    int num_visits(const string& vertex) const;

private:

    void pre_visit(const string& vertex);

    void post_visit(const string& vertex);

    void inc_visits(const string& vertex);

    void plan_vertex_visit(const string &to_vertex);

    bool visits_planned() const;

    const string& peek_next_visit() const;

    void pop_next_visit();

    void cycle_detected(const std::string& vertex);

    const graph& m_graph;
    traversal_t m_traversal_type;
    std::deque<string> m_planned_visits;
    std::vector<string> m_pre_order;
    std::vector<string> m_post_order;

    bool m_cycle_found{false};
    std::vector<string> m_path;
    std::unordered_set<string> m_cycle;

    // Add a field 'm_visited' here that is used to check which vertices have been visited already
    std::unordered_map<string, int> m_visited;
};

#endif //GRAPHS_FULL_VISITOR_H
