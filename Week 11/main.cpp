#include <iostream>
#include <cassert>
#include "maxheap.h"
#include "heap_tester.h"

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

int main() {
    std::vector<int> numbers{2, 9, 5, 3, 7, 6, 0, 4, 1};

    heap_sort(numbers);

    for (size_t i = 1; i < numbers.size(); ++i)
        assert(!(numbers[i - 1] > numbers[i]));


    std::vector<char> letters{'z', 't', 'x', 'y', 'a', 'f', 'q', 'c', 's'};

    heap_sort(letters);

    for (size_t i = 1; i < letters.size(); ++i)
        assert(!(letters[i - 1] > letters[i]));


    std::vector<std::string> strings{"foo", "bar", "bob", "ham", "bacon"};

    heap_sort(strings);

    for (size_t i = 1; i < strings.size(); ++i)
        assert(!(strings[i - 1] > strings[i]));
}
