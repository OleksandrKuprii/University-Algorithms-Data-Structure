//
// Created by rgr24 on 29/05/2021.
//

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include "shortest_paths.h"
#include "vertex_heap.h"
#include "visitor.h"

using std::string;

shortest_paths::shortest_paths(const graph &graph, const std::string &source)
        : m_graph{graph}, m_source(source) {

    // initialize the shortest paths data
    for (const auto &v : m_graph.vertices()) {
        m_vertex_scans[v.name()] = 0;
        m_shortest_distances.insert(std::make_pair(v.name(), path_data{}));
    }

    // initialize distance to source vertex to zero
    m_shortest_distances.find(m_source)->second.set_distance("", 0);
}

bool shortest_paths::to_dot(const std::string &filename) {
    std::ofstream file{filename};
    if (file.is_open()) {
        file << "digraph {" << std::endl
             << "\trankdir = LR;" << std::endl
             << "\tnode[shape=oval, style=\"filled\", penwidth=2, color=\"darkblue\" fillcolor=\"cornflowerblue\"];" << std::endl;

        // go over vertices, emit their label and colour
        for (const auto &v : m_graph.vertices()) {
            file << "\t" << v.name() << "[label=\"" << v.name();
            if (get_distance(v) < path_data::VERY_FAR)
                file << "\\nd: " << get_distance(v);
            file << "\"];" << std::endl;
        }

        struct pair_hash
        {
            std::size_t operator() (const std::pair<string, string>& pair) const {
                return std::hash<string>()(pair.first + pair.second);
            }
        };

        // find shortest path edges
        std::unordered_set<std::pair<std::string, std::string>, pair_hash> shortest_path_edges;
        std::unordered_map<std::pair<std::string, std::string>, int, pair_hash> all_edges;
        for (const auto& spdata : m_shortest_distances) {
            if (spdata.second.via() != "") {
                auto &from = spdata.second.via();
                auto &to = spdata.first;
                auto pair = std::make_pair(from, to);
                if (!m_graph.is_directed() && to < from) pair = std::make_pair(to, from);
                shortest_path_edges.insert(pair);
            }
        }

        for (const auto &v : m_graph.vertices()) {
            for (const auto &edge: v.edges()) {
                auto &from = v.name();
                auto &to = edge.target().name();
                auto pair = std::make_pair(from, to);
                if (!m_graph.is_directed() && to < from) pair = std::make_pair(to, from);
                all_edges.insert(std::make_pair(pair, edge.weight()));
            }
        }

        // go over edges
        file << std::endl << "\tedge[dir = " << (m_graph.is_directed() ? "forward" : "none") << "];" << std::endl;
        for (const auto &pair : all_edges) {
            auto &edge = pair.first;
            file << "\t" << edge.first << " -> " << edge.second << " [";
            if (!shortest_path_edges.contains(edge))
                file << "penwidth=0.25, fontsize=8"; //style=" << std::quoted("dashed");
            else
                file << "penwidth=2.5";

            file << ", label=\"" << pair.second << "\"];" << std::endl;
        }
        file << "}" << std::endl;
        return true;
    } else
        return false;
}

void shortest_paths::compute() {
    visitor visitor{m_graph, traversal_t::breadth_first};

    visitor.find_iterative(m_graph.vertices()[0], "");
    m_cyclic_graph = visitor.cycle_found();

    // based on whether a cycle was found, run a specific shortest paths algorithm
    if (!m_cyclic_graph) {
        const auto& order = visitor.post_order();
        scan_all(order, false);
    } else {
        dijkstra_heap();
    }
}

int shortest_paths::get_distance(const string &vertex) const {
    auto it = m_shortest_distances.find(vertex);
    if (it == m_shortest_distances.end()) throw std::invalid_argument("get_distance: no data for vertex " + vertex);
    return it->second.distance();
}

void shortest_paths::set_distance(const std::string &to_vertex, const std::string &via_vertex, int distance) {
    auto it = m_shortest_distances.find(to_vertex);
    if (it == m_shortest_distances.end()) throw std::invalid_argument("get_distance: no data for vertex " + to_vertex);
    it->second.set_distance(via_vertex, distance);
}

bool shortest_paths::scan(const string &vertex) {
    bool an_edge_was_relaxed = false;
    for (auto &edge : m_graph[vertex].edges()) {
        if (relax(vertex, edge))
            an_edge_was_relaxed = true;
    }
    mark_as_scanned(vertex);
    return an_edge_was_relaxed;
}

size_t shortest_paths::num_scans(const string &vertex) {
    return m_vertex_scans[vertex];
}

void shortest_paths::mark_as_scanned(const string &vertex) {
    m_vertex_scans[vertex]++;
}

size_t shortest_paths::vertex_scans() const {
    size_t count = 0;
    for (auto& pair : m_vertex_scans) count += pair.second;
    return count;
}

bool shortest_paths::is_cyclic() const {
    return m_cyclic_graph;
}

bool shortest_paths::relax(const string &vertex, const graph::edge &edge) {
    auto & target = edge.target();
    auto new_distance = m_shortest_distances[vertex].distance() + edge.weight();

    if (new_distance < m_shortest_distances[target].distance()) {
        m_shortest_distances[target].set_distance(vertex, new_distance);
        return true;
    }
    return false;
}

void shortest_paths::scan_all(std::vector<std::string> vector, bool reversed) {
    if (reversed) {
        while (!vector.empty()) {
            scan(vector.back());
            vector.pop_back();
        }
    } else {
        for (string & v : vector) {
            scan(v);
        }
    }
}

bool shortest_paths::find_next_dijkstra(std::string &next) {
    int min_distance = INT_MAX;
    for (auto & v : m_graph.vertices()) {
        if (m_vertex_scans[v.name()] != 0)
            continue;
        if (get_distance(v) < min_distance) {
            next = v;
            min_distance = get_distance(v);
        }
    }
    return min_distance != INT_MAX;
}

void shortest_paths::dijkstra_lin_search() {
    string next;

    while (find_next_dijkstra(next)) {
        scan(next);
    }
}

void shortest_paths::dijkstra_heap() {
    vertex_heap heap;
    heap.insert(m_source, 0);

    while (!heap.empty()) {
        auto vertex = heap.min();
        heap.delete_min();
        if (num_scans(vertex) != 0) continue;
        if (scan(vertex)) {
            for (auto &edge : m_graph[vertex].edges()) {
                heap.insert(edge.target(), get_distance(edge.target()));
            }
        }
    }
}

