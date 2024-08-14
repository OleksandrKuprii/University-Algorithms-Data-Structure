# Week 11 - Heaps

## Team

Team name: Oleksandr
Date: 06-06-2022

Members  
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             |      |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              |      |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. |      |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   |      |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion. **NOTE**: in this week you will have to reuse the code of last week. Follow the instructions given in the `main.cpp` file.

### Activity 1: Comparing different data structures

| Data structure     | Find-max | Delete-Max | Insert |
|--------------------|:--------:|:----------:|:------:|
| Sorted array       |  O(1)    |    O(1)    |   O(n) |
| Sorted linked list |  O(1)    |    O(1)    |   O(n) |
| Balanced BST       |  O(logn) |    O(logn) | O(logn)|

### Activity 2: Identify valid heaps

1. Min-heap
2. This tree is not a heap. Values 29 and 37 break the order invariant.
3. Min-heap

### Activity 3: Do it yourself

Two swaps are needed to restore the order invariant:
1. 12 and 3
2. 12 and 11

### Activity 4: Worst-case time complexities

| Data structure  | Find-max | Delete-Max | Insert | Find |
|-----------------|:--------:|:----------:|:------:|:----:|
| Balanced BST    | O(logn)  | O(logn)    | O(logn)|O(logn)|
| Binary max-heap | O(1)     | O(logn)    | O(logn)| O(n) |

### Activity 5: Index computations

```cpp
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
```

### Activity 6: Implement the find-max operation

```cpp
const task& maxheap::maximum() const {
    return m_values[0];
}
```

### Activity 7: Bubbling up

```c++
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
```

### Activity 8: Bubbling down

```cpp
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
```

### Activity 9: Implement heapify

```cpp
size_t maxheap::heapify() {
    size_t swaps = 0;

    for (int i = 2 * (int) size() - 1; i >= 0; i--) {
        swaps += bubble_down(i);
    }

    return swaps;
}
```

### Activity 10: Heapify - time complexity

| Number of values | Number of swaps  |
|------------------|:----------------:|
| 5                |       3          |
| 10               |      10          |
| 20               |      17          |
| 50               |      47          |
| 100              |      96          |
| 200              |     195          |
| 300              |     295          |
| 400              |     394          |
| 500              |     493          |
| 1000             |     992          |

The worst-case time complexity is O(n).

### Activity 11: Bubbling down vector elements
```cpp
size_t npos = -1;

size_t left_child_index(size_t index, size_t count) {
    size_t left_index = 2 * index + 1;

    if (left_index < count)
        return left_index;

    return npos;
}

size_t right_child_index(size_t index, size_t count) {
    size_t right_index = 2 * index + 2;

    if (right_index < count)
        return right_index;

    return npos;
}

size_t bubble_down(std::vector<int> &values, size_t index, size_t count) {
    size_t swaps = 0;

    size_t left = left_child_index(index, count);
    size_t right = right_child_index(index, count);

    while (true) {
        if (right == npos && left == npos)
            return swaps;

        if (left != npos && right != npos && (values[index] < values[right] || values[index] < values[left])) {
            if (values[left] > values[right]) {
                std::swap(values[index], values[left]);
                index = left;
                swaps++;
            } else {
                std::swap(values[index], values[right]);
                index = right;
                swaps++;
            }
        } else if (left == npos && values[index] < values[right]) {
            std::swap(values[index], values[right]);
            index = right;
            swaps++;
        } else if (right == npos && values[index] < values[left]) {
            std::swap(values[index], values[left]);
            index = left;
            swaps++;
        } else {
            return swaps;
        }

        left = left_child_index(index, count);
        right = right_child_index(index, count);
    }
}

size_t heapify(std::vector<int> &numbers) {
    size_t swaps = 0;

    for (int i = 2 * (int) numbers.size() - 1; i >= 0; i--) {
        swaps += bubble_down(numbers, i, numbers.size());
    }

    return swaps;
}

```


### Activity 12: In-place heap sort

```cpp
void heap_sort(std::vector<int> &numbers) {
    heapify(numbers);
    std::cout << numbers.size();
    for (size_t i = 0; i < numbers.size(); i++) {
        std::swap(numbers[0], numbers[numbers.size() - i - 1]);
        bubble_down(numbers, 0, numbers.size() - i - 1);
    }
}  
```

### Activity 13: General heap sort

```cpp
template<typename T>
size_t bubble_down(std::vector<T> &values, size_t index, size_t count) {
    size_t swaps = 0;

    size_t left = left_child_index(index, count);
    size_t right = right_child_index(index, count);

    while (true) {
        if (right == npos && left == npos)
            return swaps;

        if (left != npos && right != npos && (values[index] < values[right] || values[index] < values[left])) {
            if (values[left] > values[right]) {
                std::swap(values[index], values[left]);
                index = left;
                swaps++;
            } else {
                std::swap(values[index], values[right]);
                index = right;
                swaps++;
            }
        } else if (left == npos && values[index] < values[right]) {
            std::swap(values[index], values[right]);
            index = right;
            swaps++;
        } else if (right == npos && values[index] < values[left]) {
            std::swap(values[index], values[left]);
            index = left;
            swaps++;
        } else {
            return swaps;
        }

        left = left_child_index(index, count);
        right = right_child_index(index, count);
    }
}

template<typename T>
size_t heapify(std::vector<T> &numbers) {
    size_t swaps = 0;

    for (int i = 2 * (int) numbers.size() - 1; i >= 0; i--) {
        swaps += bubble_down(numbers, i, numbers.size());
    }

    return swaps;
}

template<typename T>
void heap_sort(std::vector<T> &numbers) {
    heapify(numbers);
    std::cout << numbers.size();
    for (size_t i = 0; i < numbers.size(); i++) {
        std::swap(numbers[0], numbers[numbers.size() - i - 1]);
        bubble_down(numbers, 0, numbers.size() - i - 1);
    }
}
```

## Looking back

### What we've learnt

A lot about heaps.

### What were the surprises

Nothing surprised

### What problems we've encountered

I have spent some time to make bubble down function.

### What was or still is unclear

Nothing.

### How did the group perform?

Working oneself is sometimes releaving.





