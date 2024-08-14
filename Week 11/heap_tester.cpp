//
// Created by rgr24 on 14/05/2021.
//

#include "heap_tester.h"
#include <iostream>
#include <cassert>

bool heap_tester::test_left_child_index() {
    maxheap heap;
    heap.m_values.push_back(task{.priority = 10, .description = "root"});
    heap.m_values.push_back(task{.priority = 7, .description = "left"});
    heap.m_values.push_back(task{.priority = 7, .description = "right"});

    // root node has a left child at index 1
    assert(1 == heap.left_child_index(0));

    // bottom left node has no left child
    assert(maxheap::npos == heap.left_child_index(1));

    // bottom right node has no left child
    assert(maxheap::npos == heap.left_child_index(2));

    heap.m_values.push_back(task{.priority = 5, .description = "left-left"});

    // now "left" node has a left child, but node "right" does not
    assert(3 == heap.left_child_index(1));
    assert(maxheap::npos == heap.left_child_index(2));

    std::cerr << "test_left_child_index PASS" << std::endl;

    return true;
}

bool heap_tester::test_right_child_index() {
    maxheap heap{};
    heap.m_values.push_back(task{.priority = 10, .description = "root"});
    heap.m_values.push_back(task{.priority = 7, .description = "left"});
    heap.m_values.push_back(task{.priority = 7, .description = "right"});

    // root node has a right child at index 2
    assert(2 == heap.right_child_index(0));

    // bottom left node has no right child
    assert(maxheap::npos == heap.right_child_index(1));

    // bottom right node has no right child
    assert(maxheap::npos == heap.right_child_index(2));

    heap.m_values.push_back(task{.priority = 5, .description = "left-left"});

    // now "left" node has a left child, but not a right child
    assert(maxheap::npos == heap.right_child_index(1));
    assert(maxheap::npos == heap.right_child_index(2));

    heap.m_values.push_back(task{.priority = 5, .description = "left-right"});

    // now "left" node has a right child, but "right" node does not
    assert(4 == heap.right_child_index(1));
    assert(maxheap::npos == heap.right_child_index(2));

    std::cerr << "test_right_child_index PASS" << std::endl;

    return true;
}

bool heap_tester::test_parent_index() {
    maxheap heap{};
    heap.m_values.push_back({10, "root"});
    heap.m_values.push_back({7, "left"});
    heap.m_values.push_back({7, "right"});
    heap.m_values.push_back({6, "left-left"});
    heap.m_values.push_back({6, "left-right"});
    heap.m_values.push_back({6, "right-left"});
    heap.m_values.push_back({6, "right-right"});

    // root node does not have a parent node
    assert(maxheap::npos == heap.parent_index(0));
    assert(0 == heap.parent_index(1));
    assert(0 == heap.parent_index(2));
    assert(1 == heap.parent_index(3));
    assert(1 == heap.parent_index(4));
    assert(2 == heap.parent_index(5));
    assert(2 == heap.parent_index(6));

    std::cerr << "test_parent_index PASS" << std::endl;
    return true;
}

bool heap_tester::test_find_max() {
    maxheap heap{};
    heap.m_values.push_back({1, "easy"});
    assert(&heap.m_values[0] == &heap.maximum());

    std::cerr << "test_find_max PASS" << std::endl;
    return true;
}

bool heap_tester::test_bubble_up() {
    maxheap heap{};
    heap.m_values.push_back({1, "one"});
    auto swapcount = heap.bubble_up(0);
    assert(0 == swapcount);

    heap.m_values.push_back({2, "two"});
    swapcount = heap.bubble_up(1);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 2);
    assert(heap.m_values[1].priority == 1);

    heap.m_values.push_back({3, "three"});
    swapcount = heap.bubble_up(2);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 1);
    assert(heap.m_values[2].priority == 2);

    // the value 4 must be bubbled up to the root
    heap.m_values.push_back({4, "four"});
    swapcount = heap.bubble_up(3);
    assert(2 == swapcount);
    assert(heap.m_values[0].priority == 4);
    assert(heap.m_values[1].priority == 3);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 1);

    // the value 6 must be bubbled up to the root
    heap.m_values.push_back({6, "six"});
    swapcount = heap.bubble_up(4);
    assert(2 == swapcount);
    assert(heap.m_values[0].priority == 6);
    assert(heap.m_values[1].priority == 4);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 1);
    assert(heap.m_values[4].priority == 3);

    // the value 5 must be bubbled up to level 1
    heap.m_values.push_back({5, "six"});
    swapcount = heap.bubble_up(5);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 6);
    assert(heap.m_values[1].priority == 4);
    assert(heap.m_values[2].priority == 5);
    assert(heap.m_values[3].priority == 1);
    assert(heap.m_values[4].priority == 3);
    assert(heap.m_values[5].priority == 2);

    std::cerr << "test_bubble_up PASS" << std::endl;
    return true;
}

bool heap_tester::test_bubble_down() {
    maxheap heap{};
    heap.m_values.push_back({1, "one"});
    heap.m_values.push_back({2, "two"});
    auto swapcount = heap.bubble_down(0);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 2);
    assert(heap.m_values[1].priority == 1);

    heap.m_values.push_back({3, "three"});
    swapcount = heap.bubble_down(0);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 1);
    assert(heap.m_values[2].priority == 2);

    heap.m_values.push_back({4, "four"});
    swapcount = heap.bubble_down(3); // should have no effect!
    assert(0 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 1);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 4);

    heap.m_values.push_back({5, "five"});
    swapcount = heap.bubble_down(4); // should have no effect!
    assert(0 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 1);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 4);
    assert(heap.m_values[4].priority == 5);

    swapcount = heap.bubble_down(0); // should have no effect!
    assert(0 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 1);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 4);
    assert(heap.m_values[4].priority == 5);

    swapcount = heap.bubble_down(1);
    assert(1 == swapcount);
    assert(heap.m_values[0].priority == 3);
    assert(heap.m_values[1].priority == 5);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 4);
    assert(heap.m_values[4].priority == 1);

    swapcount = heap.bubble_down(0);
    assert(2 == swapcount);
    assert(heap.m_values[0].priority == 5);
    assert(heap.m_values[1].priority == 4);
    assert(heap.m_values[2].priority == 2);
    assert(heap.m_values[3].priority == 3);
    assert(heap.m_values[4].priority == 1);

    std::cerr << "test_bubble_down PASS" << std::endl;
    return true;
}

bool heap_tester::test_heapify() {
    maxheap heap{};
    for (int prio = 1; prio <= 1000; ++prio) {
        heap.m_values.push_back({prio, "dummy"});
    }
    auto swapcount = heap.heapify();
    std::cout << swapcount;
    assert(8 == swapcount);
    assert(10 == heap.m_values[0].priority);
    assert(9 == heap.m_values[1].priority);
    assert(7 == heap.m_values[2].priority);
    assert(8 == heap.m_values[3].priority);
    assert(5 == heap.m_values[4].priority);
    assert(6 == heap.m_values[5].priority);
    assert(3 == heap.m_values[6].priority);
    assert(1 == heap.m_values[7].priority);
    assert(4 == heap.m_values[8].priority);
    assert(2 == heap.m_values[9].priority);

    heap.m_values.clear();
    for (int prio = 10; prio >= 1; --prio) {
        heap.m_values.push_back({prio, "dummy"});
    }
    swapcount = heap.heapify();
    assert(0 == swapcount);

    std::cerr << "test_heapify PASS" << std::endl;
    return true;
}
