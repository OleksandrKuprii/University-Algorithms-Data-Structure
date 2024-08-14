#include <stdio.h>
#include <stdlib.h>

typedef struct buffer {
    size_t head;
    size_t count;
    size_t capacity;
    char *data;
} buffer_t;

void buffer_destroy(buffer_t *queue) {
    free(queue->data);
    queue->data = NULL;
}

void buffer_init(buffer_t *queue, size_t capacity) {
    queue->head = queue->count = 0;
    queue->data = (char*) malloc(capacity * sizeof(char));
    if (queue->data != NULL) queue->capacity = capacity;
    else queue->capacity = 0;
}

size_t buffer_rear(const buffer_t *queue) {
    return (queue->head + queue->count) % queue->capacity;
}

// 5 3 3

int main() {
    buffer_t queue;
    buffer_init(&queue, 100);
    for (int i = 0; i < 100; i++) queue.data[i] = '?';
    buffer_destroy(&queue);
    return 0;
}
