//
// Created by rgr24 on 31/05/2021.
//

#include <iostream>
#include <iomanip>
#include "shortest_paths_tester.h"
#include "graph.h"
#include "shortest_paths.h"

bool shortest_paths_tester::test_relax() {
    bool result = true;
    // create a directed graph
    graph g{true};
    g.add_edge("a", "b", 3);
    g.add_edge("a", "c", 5);
    g.add_edge("b", "c", 1);

    shortest_paths sp{g, "a"};

    // scan (a, b) and verify distance to b has decreased to 3
    // scan (a, c) and verify distance to c has decreased to 5
    for (auto &edge: g["a"].edges()) {
        bool relaxed = sp.relax("a", edge);
        if (!relaxed) {
            std::cerr << "Relaxing edge (a, " << edge.target().name() << ") must return true" << std::endl;
            result = false;
        }
        if (int dist = sp.get_distance(edge.target()); dist != edge.weight()) {
            std::cerr << "After relaxing edge (a, " + edge.target().name() + "), "
                      << "distance to " << edge.target().name() << " must be "
                      << edge.weight() << ", but it is " << dist << std::endl;
            result = false;
        }
        relaxed = sp.relax("a", edge);
        if (relaxed) {
            std::cerr << "Second relaxation of edge (a, " << edge.target().name() << ") must return false" << std::endl;
            result = false;
        }
    }

    bool relaxed = sp.relax("b", g["b"].edges()[0]);
    if (!relaxed) {
        std::cerr << "Relaxing edge (b, c) must return true" << std::endl;
        result = false;
    }
    if (int dist = sp.get_distance("c"); dist != 4) {
        std::cerr << "After relaxing edges (a, b) and (b, c), distance to c must be 4, but it is " << dist << std::endl;
        result = false;
    }

    if (result) std::cerr << "text_relax PASS" << std::endl;
    return result;
}

bool shortest_paths_tester::test_scan_all() {
    bool result = true;
    // create a directed graph
    graph g{true};
    g.add_edge("a", "b", 3);
    g.add_edge("b", "c", 2);
    g.add_edge("c", "d", 1);

    std::vector<std::string> vec = {"a", "b", "c"};
    shortest_paths sp{g, "a"};
    sp.scan_all(vec, true);
    if (auto dist = sp.get_distance("a"); dist != 0) {
        std::cerr << "scan_all in reverse should result in distance of 0 to vertex \"a\", not " << dist << std::endl;
        result = false;
    }
    if (auto dist = sp.get_distance("b"); dist != 3) {
        std::cerr << "scan_all in reverse should result in distance of 3 to vertex \"b\", not " << dist
                  << std::endl;
        result = false;
    }
    if (auto dist = sp.get_distance("c"); dist != path_data::VERY_FAR) {
        std::cerr << "scan_all in reverse should result in distance of VERY_FAR to vertex \"c\", not " << dist
                  << std::endl;
        result = false;
    }
    if (auto dist = sp.get_distance("d"); dist != path_data::VERY_FAR) {
        std::cerr << "scan_all in reverse should result in distance of VERY_FAR to vertex \"d\", not " << dist
                  << std::endl;
        result = false;
    }

    shortest_paths sp2{g, "a"};
    sp2.scan_all(vec, false);

    if (auto dist = sp2.get_distance("a"); dist != 0) {
        std::cerr << "scan_all should result in distance of 0 to vertex \"a\", not " << dist << std::endl;
        result = false;
    }
    if (auto dist = sp2.get_distance("b"); dist != 3) {
        std::cerr << "scan_all should result in distance of 3 to vertex \"b\", not " << dist << std::endl;
        result = false;
    }
    if (auto dist = sp2.get_distance("c"); dist != 5) {
        std::cerr << "scan_all should result in distance of 5 to vertex \"c\", not " << dist << std::endl;
        result = false;
    }
    if (auto dist = sp2.get_distance("d"); dist != 6) {
        std::cerr << "scan_all should result in distance of 6 to vertex \"d\", not " << dist << std::endl;
        result = false;
    }

    if (result) std::cerr << "test_scan_all PASS" << std::endl;

    return true;
}

bool shortest_paths_tester::verify_paths(shortest_paths &paths) {
    for (const auto &pair : paths.m_shortest_distances) {
        auto via = pair.second.via();
        if ("" != via) {
            auto & edges = paths.m_graph.find_vertex(via).edges();
            auto it = std::find_if(edges.begin(), edges.end(), [&](auto &e) {return e.target().name() == pair.first;});
            if (it == edges.end()) {
                std::cerr << "Shortest path to vertex " << std::quoted(pair.first) << " is via " << std::quoted(via) << ", but there is no edge that connects them." << std::endl;
                return false;
            }
            else if (paths.get_distance(via) + it->weight() != paths.get_distance(pair.first)) {
                std::cerr << "Shortest path to vertex " << std::quoted(pair.first) << " supposedly is via " << std::quoted(via) << ", but the distances don't add up." << std::endl;
                return false;
            }
        }
    }
    for (const auto &vertex: paths.m_graph.vertices()) {
        auto distance = paths.get_distance(vertex);
        if (distance == path_data::VERY_FAR)
            std::cerr << "Distance to vertex " << vertex.label() << " is still set to very far" << std::endl;

        for (const auto &edge: vertex.edges()) {
            const auto &target = edge.target();
            auto distance_to_target = paths.get_distance(target);

            if (distance + edge.weight() < distance_to_target) {
                std::cerr << "Reported smallest distance to " << std::quoted(target.label()) << " is " << distance_to_target;
                std::cerr << ", but taking path via " << std::quoted(vertex.label()) << " to " << std::quoted(target.label());
                std::cerr << " is a shorter path!" << std::endl;
                return false;
            }
        }
    }

    std::cerr << "verify_paths PASS" << std::endl;

    return true;
}

bool shortest_paths_tester::test_find_next_dijkstra() {
    // create a directed graph
    graph g{true};
    g.add_edge("a", "b", 3);
    g.add_edge("a", "c", 5);
    g.add_edge("b", "c", 1);

    shortest_paths sp{g, "a"};

    std::string vertex;
    bool has_next = sp.find_next_dijkstra(vertex);
    if (!has_next) {
        std::cerr << "find_next_dijkstra expected to return true, but it returned false" << std::endl;
        return false;
    }
    if (vertex != "a") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("a") <<
                  ", but returned vertex " << std::quoted(vertex) << std::endl;
        return false;
    }
    sp.scan(vertex);
    sp.mark_as_scanned(vertex);

    has_next = sp.find_next_dijkstra(vertex);
    if (!has_next) {
        std::cerr << "find_next_dijkstra expected to return true, but it returned false" << std::endl;
        return false;
    }
    if (vertex != "b") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("b") <<
                  ", but returned vertex " << std::quoted(vertex) << std::endl;
        return false;
    }
    sp.scan(vertex);
    sp.mark_as_scanned(vertex);

    has_next = sp.find_next_dijkstra(vertex);
    if (!has_next) {
        std::cerr << "find_next_dijkstra expected to return true, but it returned false" << std::endl;
        return false;
    }
    if (vertex != "c") {
        std::cerr << "find_next_dijkstra expected to return vertex " << std::quoted("c") <<
                  ", but returned vertex " << std::quoted(vertex) << std::endl;
        return false;
    }
    sp.scan(vertex);
    sp.mark_as_scanned(vertex);

    has_next = sp.find_next_dijkstra(vertex);
    if (has_next) {
        std::cerr << "find_next_dijkstra expected to return false, but it returned true" << std::endl;
        return false;
    }

    std::cerr << "test_find_next_dijkstra PASS" << std::endl;
    return true;
}
