//
// Created by rgr24 on 12/05/2021.
//

#include <stdexcept>
#include <iostream>
#include "maxheap.h"

maxheap::maxheap(const std::vector<task> &values)
    : m_values{values} {
    heapify();
}

maxheap::operator bool() const {
    return !m_values.empty();
}

maxheap &maxheap::operator<<(int priority) {
    return operator<<(task{.priority = priority, .description = "unspecified"});
}

maxheap &maxheap::operator<<(const task &task) {
    insert(task);
    return *this;
}

size_t maxheap::size() const {
    return m_values.size();
}

const task &maxheap::maximum() const {
    return m_values[0];
}

void maxheap::delete_max() {
    std::swap(m_values[0], m_values.back());
    m_values.pop_back();
    bubble_down(0);
}

void maxheap::insert(const task &value) {
    m_values.push_back(value);
    bubble_up(m_values.size() - 1);
}

void maxheap::swap(size_t first_index, size_t second_index) {
    std::swap(m_values[first_index], m_values[second_index]);
}

size_t maxheap::parent_index(size_t index) {
    if (index == 0)
        return npos;
    return (index - 1) / 2;
}

size_t maxheap::left_child_index(size_t index) {
    size_t left_index = 2 * index + 1;

    if (left_index < size())
        return left_index;

    return npos;
}

size_t maxheap::right_child_index(size_t index) {
    size_t right_index = 2 * index + 2;

    if (right_index < size())
        return right_index;

    return npos;
}

size_t maxheap::bubble_up(size_t index) {
    size_t swaps = 0;
    size_t parent = parent_index(index);

    while (parent != npos && m_values[index] > m_values[parent]) {
        swap(index, parent);
        swaps++;
        index = parent;
        parent = parent_index(index);
    }

    return swaps;
}

size_t maxheap::bubble_down(size_t index) {
    size_t swaps = 0;

    size_t left = left_child_index(index);
    size_t right = right_child_index(index);

    while (true) {
        if (right == npos && left == npos)
            return swaps;

        if (left != npos && right != npos && (m_values[index] < m_values[right] || m_values[index] < m_values[left])) {
            if (m_values[left] > m_values[right]) {
                swap(index, left);
                index = left;
                swaps++;
            } else {
                swap(index, right);
                index = right;
                swaps++;
            }
        } else if (left == npos && m_values[index] < m_values[right]) {
            swap(index, right);
            index = right;
            swaps++;
        } else if (right == npos && m_values[index] < m_values[left]) {
            swap(index, left);
            index = left;
            swaps++;
        } else {
            return swaps;
        }

        left = left_child_index(index);
        right = right_child_index(index);
    }
}

size_t maxheap::heapify() {
    size_t swaps = 0;

    for (int i = 2 * (int) size() - 1; i >= 0; i--) {
        swaps += bubble_down(i);
    }

    return swaps;
}

