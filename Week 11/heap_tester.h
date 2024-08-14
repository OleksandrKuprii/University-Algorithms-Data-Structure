//
// Created by rgr24 on 14/05/2021.
//

#ifndef HEAP_FULL_HEAP_TESTER_H
#define HEAP_FULL_HEAP_TESTER_H

#include "maxheap.h"

class heap_tester {
public:
    static bool test_left_child_index();
    static bool test_right_child_index();
    static bool test_parent_index();
    static bool test_find_max();
    static bool test_bubble_up();
    static bool test_bubble_down();
    static bool test_heapify();
};


#endif //HEAP_FULL_HEAP_TESTER_H
