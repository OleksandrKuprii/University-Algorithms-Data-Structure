//
// Created by rgr24 on 12/05/2021.
//

#ifndef HEAP_FULL_MAXHEAP_H
#define HEAP_FULL_MAXHEAP_H

#include <vector>
#include "task.h"

class maxheap {
    friend class heap_tester;
public:
    // constructor
    maxheap(const std::vector<task>& values = {});

    operator bool() const;
    maxheap& operator<< (int priority);
    maxheap& operator<< (const task& task);

    size_t size() const;
    const std::vector<task>& values() const;

    // Activity 6: return the maximum element
    const task& maximum() const;
    void delete_max();
    void insert(const task& value);

    // A constant to indicate an invalid index
    static inline size_t npos = -1;

private:
    // functions for computing the indices of parent and / left/right child nodes
    size_t parent_index(size_t index); // Activity 5
    size_t left_child_index(size_t index); // Activity 5
    size_t right_child_index(size_t index); // Activity 5

    // Activity 7: restore heap invariant by swapping value upwards
    size_t bubble_up(size_t index);

    // Activity 8: restore heap invariant by swapping value downwards
    size_t bubble_down(size_t index);

    /// Activity 9: build heap from unordered array
    size_t heapify();

    // swaps the two elements in m_values at indices first_index and second_index
    void swap(size_t first_index, size_t second_index);

    // dynamic array with tasks -- the contents of the heap
    std::vector<task> m_values;
};


#endif //HEAP_FULL_MAXHEAP_H
