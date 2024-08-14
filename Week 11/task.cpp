//
// Created by rgr24 on 16/05/2021.
//

#include "task.h"

bool task::operator<(const task &other) const {
    return priority < other.priority;
}

bool task::operator>(const task &other) const {
    return priority > other.priority;
}
