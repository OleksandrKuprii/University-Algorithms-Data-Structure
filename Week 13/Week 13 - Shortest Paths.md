# Week 13 - Shortest Paths

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
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr     |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion. **NOTE**: in this week you will have to reuse the code of last week. Follow the instructions given in the `main.cpp` file.

### Activity 1: Find the shortest distance

The shortest path is abehlpq which distance is 15.
There is no need to go over all paths to find the shortes. It is smarter to use an alogrithm.

### Activity 2: Time to relax

```cpp
bool shortest_paths::relax(const string &vertex, const graph::edge &edge) {
    auto & target = edge.target();
    auto new_distance = m_shortest_distances[vertex].distance() + edge.weight();

    if (new_distance < m_shortest_distances[target].distance()) {
        m_shortest_distances[target].set_distance(vertex, new_distance);
        return true;
    }
    return false;
}
```

### Activity 3: Depth-first traversal

```cpp
void shortest_paths::compute() {
    visitor visitor{m_graph, traversal_t::breadth_first};

    visitor.find_iterative(m_graph.vertices()[0], "");
    m_cyclic_graph = visitor.cycle_found();

    // based on whether a cycle was found, run a specific shortest paths algorithm
    if (!m_cyclic_graph) {
        // TODO Activity 5 - scan all vertices in topological order
        const auto& order = std::vector<std::string>{};
        scan_all(order, false);
    } else {
        // TODO Activity 8, 10 - run Dijkstra's algorithm (linear search or binary heap)
    }
}
```

### Activity 4: Scanning all vertices

```cpp
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
```

### Activity 5: Shortest paths in acyclic graphs

```cpp
void shortest_paths::compute() {
    visitor visitor{m_graph, traversal_t::breadth_first};

    visitor.find_iterative(m_graph.vertices()[0], "");
    m_cyclic_graph = visitor.cycle_found();

    // based on whether a cycle was found, run a specific shortest paths algorithm
    if (!m_cyclic_graph) {
        const auto& order = visitor.post_order();
        scan_all(order, false);
    } else {
        // TODO Activity 8, 10 - run Dijkstra's algorithm (linear search or binary heap)
    }
}
```

### Activity 6: Paying a visit only once

Record your answer here

### Activity 7: Finding the next vertex to be scanned

```cpp
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
```

### Activity 8: Dijkstra using linear search

```cpp
void shortest_paths::dijkstra_lin_search() {
    string next;

    while (find_next_dijkstra(next)) {
        scan(next);
    }
}
```

### Activity 9: Time complexity of Dijkstra - linear search

1. The worst-case time complexity of finding the next vertex to visit is O(n).
2. The worst-case time complexity of updating the distance of a vertex is O(m)
3. The worst-case time complexity of the implementation of Dijkstra that uses linear search is O(n<sup>2</sup> + m)

### Activity 10: Using a vertex heap

```cpp
void shortest_paths::dijkstra_heap() {
    vertex_heap heap;
    heap.insert(m_source, 0);

    while (!heap.empty()) {
        auto vertex = heap.min();
        heap.delete_min();
        if (scan(vertex)) {
            for (auto &edge : m_graph[vertex].edges()) {
                heap.insert(edge.target(), get_distance(edge.target()));
            }
        }
    }
}
```

### Activity 11: Minimizing the number of scans

```cpp
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
```


### Activity 12: Dijkstra's worst-case time complexity - a closer look

A number of edges is equal to the square of a number of vertices, m = n<sup>2</sup>.

For an array-based Dijkstra the time complexity equals to O(n<sup>2</sup> + m) = O(2*n<sup>2</sup>) = O(n<sup>2</sup>).

For a heap-based Dijkstra the time complexity equals to O((n+m)*logn) = O((n+n<sup>2</sup>)*log(n)) = O(n*logn+n<sup>2</sup>*logn) = O(n<sup>2</sup>*logn).

Thus, the array-based Dijkstra is faster.

### Activity 13: Negative edge weights

The distance to a vertex **d** is incorrect. After the algorithm set the value to **c**, its value was the minimum in the heap, so the algorithm update the value of its neighbours (vertex **d**).

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





