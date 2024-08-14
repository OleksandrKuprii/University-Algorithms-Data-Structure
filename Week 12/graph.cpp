#include "graph.h"
#include <exception>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "colours.h"

bool graph::is_directed() const {
    return m_directed;
}

size_t graph::num_vertices() const {
    return m_vertices.size();
}

size_t graph::num_edges() const {
    return m_num_edges;
}

size_t graph::add_vertex(const std::string &name) {
    if (std::all_of(name.begin(), name.end(), [&](const auto &item) { return std::iswspace(item); }))
        throw std::invalid_argument("add_vertex: illegal vertex name");

    if (m_name_to_id.find(name) != m_name_to_id.end())
        throw std::invalid_argument("add_vertex: Vertex with name \"" + name + "\" already exists");

    size_t result = m_name_to_id[name] = m_vertices.size();
    m_vertices.push_back(graph::vertex{name, m_vertices.size()});

    return result;
}

void graph::add_edge(const std::string &from, const std::string &to) {
    // lookup source
    auto it = m_name_to_id.find(from);
    auto source_id = it != m_name_to_id.end() ? it->second : add_vertex(from);

    // lookup target
    it = m_name_to_id.find(to);
    auto target_id = it != m_name_to_id.end() ? it->second : add_vertex(to);

    // add edge (source -> to)
    m_vertices[source_id].m_edges.push_back(graph::edge{*this, target_id});

    if (!m_directed) {
        // add an edge from 'to' to from
        m_vertices[target_id].m_edges.push_back(graph::edge{*this, source_id});
    }
    m_num_edges++;
}

const std::vector<graph::vertex> &graph::vertices() const {
    return m_vertices;
}

size_t graph::find_id(const std::string &label) const {
    auto entry = m_name_to_id.find(label);
    if (entry == m_name_to_id.end())
        throw std::invalid_argument("No vertex with name " + label + " present");

    return entry->second;
}

const graph::vertex &graph::find_vertex(const std::string &name) const {
    return m_vertices[find_id(name)];
}

const graph::vertex &graph::operator[](const std::string &name) const {
    return m_vertices[find_id(name)];
}

bool graph::to_dot(const std::string &filename) const {
    std::ofstream file{filename};
    if (file.is_open()) {
        file << "digraph g {" << std::endl
             << "\trankdir = LR;"
             << "\tnode[shape=oval style=filled];" << std::endl;

        // go over vertices, emit their name and colour
        for (const auto &v: m_vertices) {
            file << "\t" << v.name() << "[name=" << std::quoted(v.name());
            if (!v.label().empty()) {
                file << ", label=\"" << v.name() << "\\n" << v.label() << "\"";
            }
            file << ", fillcolor=" << std::quoted(v.colour()) << "];" << std::endl;
        }

        // go over edges
        file << std::endl << "\tedge[dir = " << (m_directed ? "forward" : "none") << "];" << std::endl;
        for (const auto &v: m_vertices) {
            for (const auto &edge: v.m_edges) {
                if (m_directed || v.name() < edge.target().name())
                    file << "\t" << v.name() << " -> " << edge.target().name() << ";" << std::endl;
            }
        }
        file << "}" << std::endl;
        return true;
    } else
        return false;
}

void graph::colour_vertex(const std::string &name, const std::string &colour) {
    m_vertices[find_id(name)].m_colour = colour;
}

void graph::colour_vertices(const std::vector<std::string> &names, const std::string &colour) {
    for (auto &v: names) colour_vertex(v, colour);
}

void graph::colour_vertices(const std::unordered_set<std::string> &names, const std::string &colour) {
    for (auto &v: names) colour_vertex(v, colour);
}

graph::graph(bool is_directed)
        : m_directed{is_directed}, m_num_edges{0} {
    m_vertices.reserve(50);
}

graph graph::load(const std::string &filename) {
    std::ifstream input{filename};
    if (!input) throw std::invalid_argument{"Could not open file"};
    std::string line;
    std::getline(input, line);
    bool directed;
    if ("directed" == line) directed = true;
    else if ("undirected" == line) directed = false;
    else throw std::logic_error{"first line in file must be directed/undirected"};

    graph result{directed};
    while (std::getline(input, line)) {
        std::istringstream iss{line};
        if (std::string from, to; iss >> from >> to) {
            if (!result.m_name_to_id.contains(from)) result.add_vertex(from);
            if (!result.m_name_to_id.contains(to)) result.add_vertex(to);
            result.add_edge(from, to);
        }
    }
    return result;
}

graph graph::chain(size_t length) {
    graph result{true};
    result.add_vertex("a1");
    for (size_t i = 0; i < length; ++i) {
        result.add_vertex("a" + std::to_string(i + 2));
        result.add_edge("a" + std::to_string(i + 1), "a" + std::to_string(i + 2));
    }
    return result;
}

graph graph::grid(size_t size) {
    graph result{true};
    auto name = [](size_t r, size_t c) {
        return "a" + std::to_string(r + 1) + "_" + std::to_string(c + 1);
    };

    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            result.add_vertex(name(row, col));
        }
    }
    if (size > 0) {
        for (size_t row = 0; row < size; ++row) {
            // horizontal edges
            for (size_t col = 1; col < size; ++col) result.add_edge(name(row, col - 1), name(row, col));
        }

        for (size_t col = 0; col < size; ++col) {
            // vertical edges
            for (size_t row = 1; row < size; ++row) result.add_edge(name(row - 1, col), name(row, col));
        }
    }
    return result;
}

void graph::label_vertex(const std::string &name, const std::string &lbl) {
    m_vertices[find_id(name)].label(lbl);
}

void graph::label_vertex(const std::string &name, long long int lbl) {
    m_vertices[find_id(name)].label(std::to_string(lbl));
}

graph::graph(graph &&other)
        : m_directed{other.m_directed},
          m_num_edges{other.m_num_edges},
          m_vertices(std::move(other.m_vertices)),
          m_name_to_id(std::move(other.m_name_to_id)) {
    for (auto &v: m_vertices) {
        for (auto &vw: v.m_edges) {
            vw.m_graph = this;
        }
    }
}

graph &graph::operator=(const graph &other) {
    m_vertices.clear();
    m_name_to_id.clear();
    m_directed = other.m_directed;
    m_num_edges = 0;

    for (auto &v: other.m_vertices) {
        for (auto &vw: v.m_edges) {
            add_edge(v.name(), vw.target().name());
        }
        auto &thisv = m_vertices[find_id(v.name())];
        thisv.m_colour = v.m_colour;
        thisv.m_label = v.m_label;
    }
    return *this;
}

const graph::vertex &graph::edge::target() const {
    return m_graph->m_vertices[m_target];
}

graph::edge::edge(const graph &g, size_t adjacent_vertex)
        : m_graph{&g},
          m_target{adjacent_vertex} {

}

graph::vertex::vertex(const std::string &name, size_t id)
        : m_name{name},
          m_id{id},
          m_colour{colour::white} {

}

const std::string &graph::vertex::name() const {
    return m_name;
}

const std::vector<graph::edge> &graph::vertex::edges() const {
    return m_edges;
}

const std::string &graph::vertex::colour() const {
    return m_colour;
}

graph::vertex::operator const std::string &() const {
    return m_name;
}

void graph::vertex::label(const std::string &value) {
    m_label = value;
}

const std::string &graph::vertex::label() const {
    return m_label;
}
