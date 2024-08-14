//
// Created by rgr24 on 18/05/2021.
//

#ifndef GRAPHS_FULL_GRAPH_H
#define GRAPHS_FULL_GRAPH_H

#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

template<typename T0, typename ... Tn>
auto make_vector(T0&& first, Tn&& ... args) {
    return std::vector<std::decay_t<T0>>{std::forward<T0>(first), std::forward<Tn>(args)...};
}

template<typename T0, typename ... Tn>
auto make_set(T0&& first, Tn&& ... args) {
    return std::unordered_set<std::decay_t<T0>>{std::forward<T0>(first), std::forward<Tn>(args)...};
}

class graph {
public:
    class vertex;

    class edge {
        friend class graph;
    public:
        const graph::vertex &target() const;
        edge(edge &&) = default;
        int weight() const;
    private:
        edge(edge &) = delete;
        edge(const graph &g, size_t adjacent_vertex, int weight);

        const graph *m_graph;
        size_t m_target;
        int m_weight;
    };

    class vertex {
        friend class graph;
    public:
        vertex(vertex &&) = default;
        operator const std::string &() const;
        void label(const std::string &value);
        const std::string &label() const;
        const std::string &name() const;
        const std::string &colour() const;
        const std::vector<edge> &edges() const;
    private:
        vertex(const std::string &name, size_t id);
        vertex(const vertex &) = delete; //default;

        std::string m_name;
        size_t m_id;
        std::string m_label;
        std::string m_colour{"white"};
        std::vector<edge> m_edges;
    };

    // constructor - constructs a directed or undirected graph
    graph(bool is_directed);

    // creates an acyclic graph that consists of a chain of vertices, connected by <length> edges
    static graph chain(size_t length);

    // creates an acyclic graph that consists of <size> * <size> vertices, arranged in a grid
    static graph grid(size_t size);

    // loads a graph from file
    static graph load(const std::string &filename);

    // move constructor - constructs a new graph from a temporary graph
    graph(graph &&other);

    // copy assignment
    graph& operator=(const graph& other);

    // returns true if the graph is directed, false otherwise
    bool is_directed() const;

    // returns the number of vertices
    size_t num_vertices() const;

    // returns the number of edges
    size_t num_edges() const;

    // adds a new vertex to the graph, returns its index in the m_vertices vector
    // throws an exception if a vertex with that name already exists
    size_t add_vertex(const std::string &name);

    // connects two vertices with an edge from <from> to <to>
    // if the graph is undirected, <to> will have an edge to <from> as well
    void add_edge(const std::string &from, const std::string &to, int weight);

    // returns the vertices of the graph
    const std::vector<vertex> &vertices() const;

    // looks up the vertex with the given name
    const vertex &find_vertex(const std::string &name) const;

    // looks up the vertex with the given name
    const vertex &operator[](const std::string &name) const;

    // applies a colour to a vertex, which will appear in the .dot file
    void colour_vertex(const std::string &name, const std::string &colour = "red");

    // applies a colour to all vertices of the vector
    void colour_vertices(const std::vector<std::string> &names, const std::string &colour = "red");

    // applies a colour to all vertices of the set
    void colour_vertices(const std::unordered_set<std::string> &names, const std::string &colour = "red");

    // add a label to a vertex
    void label_vertex(const std::string &name, const std::string &lbl);

    // add a numeric label to a vertex
    void label_vertex(const std::string &name, long long lbl);

    // writes the graph to a .dot file, which can be visualized online
    bool to_dot(const std::string &filename) const;

private:
    size_t find_id(const std::string &label) const;

    bool m_directed;
    size_t m_num_edges{};

    std::vector<vertex> m_vertices;
    std::unordered_map<std::string, size_t> m_name_to_id;
};

#endif //GRAPHS_FULL_GRAPH_H
