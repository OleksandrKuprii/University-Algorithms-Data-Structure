//
// Created by rgr24 on 16/05/2021.
//

#ifndef HEAP_FULL_TASK_H
#define HEAP_FULL_TASK_H

#include <string>

struct task {
    int priority;   // priority: lower number indicate higher priority
    std::string description;

    bool operator <(const task& other) const;
    bool operator >(const task& other) const;
};


#endif //HEAP_FULL_TASK_H
