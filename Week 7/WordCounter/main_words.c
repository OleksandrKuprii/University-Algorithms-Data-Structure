#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Counter.h"
#include "../LetterCounter/LetterCounter.h"

void processLine(counter_t* counter, char* line) {
    // TODO: How does this function work? (Activity 9)
    const char* sep = "\t” (),.;:?!\"\n'";

    char* token = strtok(line, sep);

    while (token) {
        if (strlen(token))
            increment(counter, token);
        token = strtok(NULL, sep);
    }
}

counter_t processFile(const char* fileName) {

    counter_t counter = makeCounter();

    FILE* fp = fopen(fileName, "r");

    if (fp) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            processLine(&counter, buffer);
        }
    }
    return counter;
}


int main() {
    counter_t counter;
    initCounter(&counter, 0);
    insert(&counter, "Bob", 3);
    insert(&counter, "Dave", 4);
    insert(&counter, "Alice", 5);
    insert(&counter, "Eva", 3);
    insert(&counter, "Charlie", 7);
    assert(strcmp(counter.data[0].key, "Alice") == 0);
    assert(counter.data[0].value == 5);
    assert(strcmp(counter.data[1].key, "Bob") == 0);
    assert(counter.data[1].value == 3);
    assert(strcmp(counter.data[2].key, "Charlie") == 0);
    assert(counter.data[2].value == 7);
    assert(strcmp(counter.data[3].key, "Dave") == 0);
    assert(counter.data[3].value == 4);
    assert(strcmp(counter.data[4].key, "Eva") == 0);
    assert(counter.data[4].value == 3);
    assert(counter.size == 5);
    assert(counter.capacity >= counter.size);
    destroyCounter(&counter);
}
