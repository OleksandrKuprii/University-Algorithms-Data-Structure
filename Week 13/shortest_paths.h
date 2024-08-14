//
// Created by rgr24 on 29/05/2021.
//

#ifndef GRAPHS_FULL_SHORTEST_PATHS_H
#define GRAPHS_FULL_SHORTEST_PATHS_H

#include "graph.h"
#include "path_data.h"

class shortest_paths {
    friend class shortest_paths_tester;
public:
    shortest_paths(const graph& graph, const std::string &source);

    bool is_cyclic() const;

    // computes the shortest paths from the source vertex
    void compute();

    // scans a vertex by relaxing all its edges
    bool scan(const std::string &vertex);

    // writes the graph and found shortest paths + distances to a dot file
    bool to_dot(const std::string& filename);

    // returns the total number of vertex scans
    size_t vertex_scans() const;
private:

    // retrieves the path_data element corresponding to the given vertex
    int get_distance(const std::string &vertex) const;

    void set_distance(const std::string &to_vertex, const std::string &via_vertex, int distance);

    // marks a vertex as scanned
    void mark_as_scanned(const std::string &vertex);

    // returns the number of times a vertex has been marked as scanned
    size_t num_scans(const std::string &vertex);

    // finds the next unvisited vertex that has the smallest distance known so far
    bool find_next_dijkstra(std::string &next);

    // relaxes the given (outgoing) edge of the given vertex
    bool relax(const std::string &vertex, const graph::edge& edge);

    // scan all the vertices in the vector
    void scan_all(std::vector<std::string> vector, bool reversed);

    // performs Dijkstra's algorithm by doing a linear search over all vertices
    void dijkstra_lin_search();

    // performs the heap-based Dijkstra algorithm
    void dijkstra_heap();

    // a reference to the graph for which this instance computes the shortest path
    const graph& m_graph;

    // indicates whether the m_graph member is a cyclic graph
    bool m_cyclic_graph;

    // the source vertex
    std::string m_source;

    // a hash map that associates each vertex with the number of times it's been scanned
    std::unordered_map<std::string, size_t> m_vertex_scans;

    // for each vertex, its current known distance from the source vertex,
    // and the vertex through which the current shortest path leads
    using distance_map = std::unordered_map<std::string, path_data>;

    // a hash map that maps each vertex to its shortest distance found so far
    distance_map m_shortest_distances;
};


#endif //GRAPHS_FULL_SHORTEST_PATHS_H
