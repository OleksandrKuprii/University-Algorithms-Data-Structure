# Week 12 - Graphs

## Team

Team name: Oleksandr
Date:

Members
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Oleksandr     |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Oleksandr     |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr      |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion. **NOTE**: in this week you will have to reuse the code of last week. Follow the instructions given in the `main.cpp` file.

### Activity 1: Applications of graphs

1. Designing of circuit connections in Electrical Engineering. Vertices - components, edges - wires. Undirected graph.
2. Atomic structures in Chemistry. Vertices - atoms, edges - connections. Undirected graph.
3. Representing interectaions between people in Social Sciences. Vertices - people, edges - connections between them. Directed graph.
4. A family tree. Vertices - people, edges - their relationship. Directedd graph.
5. A shortest path in road. Vertices - buildings, edges - roads. Directed graph.

### Activity 2: Visualizing graphs

Figure 1
```cpp
graph g{false}; // create an undirected graph
g.add_edge("a", "c");
g.add_edge("b", "c");
g.add_edge("b", "d");
g.add_edge("c", "d");
g.add_edge("c", "f");
g.add_edge("d", "e");
g.add_edge("f", "g");
g.to_dot("../simple.dot");
```

Figure 2
```cpp
graph g{true}; // create an undirected graph
g.add_edge("c", "a");
g.add_edge("a", "b");
g.add_edge("b", "d");
g.add_edge("d", "c");
g.add_edge("d", "e");
g.add_edge("e", "f");
g.add_edge("f", "g");
g.add_edge("g", "e");
g.to_dot("../simple.dot");
```

### Activity 3: Finding a path

The value of variable `found` is 0.
The vertex `d` was visited 3 times.

### Activity 4: Positive reports

```cpp
bool visitor::find_recursive(const std::string &start_vertex, const string &goal) {
    // FIXME Activity 5 - avoid cycles

    // append start_vertex to pre order
    pre_visit(start_vertex);

    // get vertex ref from name
    auto& vertex = m_graph[start_vertex];

    if (vertex.name() == goal) {
        return true;
    }

    // go over the outgoing edges of the vertex
    for (auto& edge : vertex.edges()) {
        // continue traversal from the neighbour
        if (find_recursive(edge.target(), goal))
            return true;
    }
    // append start_vertex to post order
    post_visit(start_vertex);

    return false;
}
```

### Activity 5: Getting lost

```cpp
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
```

### Activity 6: The limits of recursion

87175

### Activity 7: Iterative traversal

```cpp
bool visitor::find_iterative(const string &start_vertex, const string &goal) {
    // FIXME Activity 8 - make visit order consistent with recursive version
    // FIXME Activity 11 - keep track of the path
    // FIXME Activity 12 & 12 - detect cycles
    plan_vertex_visit(start_vertex);
    while (visits_planned()) {
        auto v = peek_next_visit();
        pre_visit(v);
        pop_next_visit();

        if (v == goal) {
            return true;
        }

        for (auto& edge : m_graph[v].edges()) {
            if (!is_visited(edge.target()))
                plan_vertex_visit(edge.target());
        }
    }
    return false;
}
```

### Activity 8: Depth-first search

```cpp
bool visitor::find_iterative(const string &start_vertex, const string &goal) {
    // FIXME Activity 11 - keep track of the path
    // FIXME Activity 12 & 12 - detect cycles
    plan_vertex_visit(start_vertex);
    while (visits_planned()) {
        auto v = peek_next_visit();

        if (is_visited(v)) {
            pop_next_visit();
            continue;
        }

        pre_visit(v);

        if (v == goal) {
            return true;
        }

        const auto & edges = m_graph[v].edges();
        for (int i = edges.size() - 1; i >= 0; i--) {
            auto & target = edges[i].target();
            plan_vertex_visit(target);
        }
    }
    return false;
}
```

```cpp
void label_pre_order(graph& g, const visitor& vis) {
    for (size_t i = 0; i < vis.pre_order().size(); i++) {
        g.label_vertex(vis.pre_order()[i], (long long) i);
    }
}
```

### Activity 9: Breadth-first search

```cpp
void visitor::plan_vertex_visit(const string &to_vertex) {
    if (m_traversal_type == traversal_t::depth_first)
        m_planned_visits.push_back(to_vertex);
    else
        m_planned_visits.push_front(to_vertex);
}
```

### Activity 10: Keeping track of the path (post-visits)

```cpp
bool visitor::find_iterative(const string &start_vertex, const string &goal) {
    // FIXME Activity 12 & 12 - detect cycles
    plan_vertex_visit(start_vertex);
    while (visits_planned()) {
        auto v = peek_next_visit();

        if (is_visited(v)) {
            pop_next_visit();
            continue;
        }

        pre_visit(v);

        if (v == goal) {
            return true;
        }

        const auto & edges = m_graph[v].edges();
        for (int i = edges.size() - 1; i >= 0; i--) {
            auto & target = edges[i].target();
            plan_vertex_visit(target);
        }
    }
    post_visit(start_vertex);

    return false;
}
```

### Activity 11: Detecting cycles

```cpp
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
```


### Activity 12: Colouring cycles

```cpp
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
```

## Looking back

### What we've learnt

Formulate at least one lesson learned.

### What were the surprises

Fill in...

### What problems we've encountered

Fill in...

### What was or still is unclear

Fill in...

### How did the group perform?

How was the collaboration? What were the reasons for hick-ups? What worked well? What can be improved next time?





