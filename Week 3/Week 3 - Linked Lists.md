# Week 3 - Linked Lists

## Team

Team name: Encoder
Date: 15-03-2022

Members:
Oleksandr Kuprii
Illia Kara

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Oleksandr     |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Illia     |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Illia     |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Set up a project in CLion to write the small programs needed in some of the activities.

### Activity 1: Pointers to pointers

The value of the variable `ppptr` represents the address to the `pptr` variable.

| Variable    | Address               | Value       |
| ----------- | --------------------- | ----------- |
| value       | 0x16b827758           | 42          |
| ptr         | 0x16b827750           | 0x16b827758 |
| pptr        | 0x16b827748           | 0x16b827750 |
| ppptr       | 0x16b827740           | 0x16b827748 |

### Activity 2: Chaining pointers

```c
typedef struct node_t {
	int value;
	struct node_t * next;
} node;

int main(void) {
	node fourth = {.value = 42, .next = NULL};
	node third = {.value = 7, .next = &fourth};
	node second = {.value = 3, .next = &third};
	node first = {.value = 2, .next = &second};
	
    printf("first: %d\n", first.value);
    printf("second: %d\n", first.next->value);
    printf("third: %d\n", first.next->next->value);
    printf("fourth: %d\n", first.next->next->next->value);
}
```

### Activity 3: Traversal

```c
int main(void) {
	node fourth = {.value = 42, .next = NULL};
	node third = {.value = 7, .next = &fourth};
	node second = {.value = 3, .next = &third};
	node first = {.value = 2, .next = &second};
	
    for (node * i = &first; i != NULL; i = i->next) {
        printf("%d\n", i->value);
    }
}
```


### Activity 4: Linked list deallocation

```c
void list_free(list ** plist) {
    node * next;
    for (node * i = (*plist)->head; i != NULL; ) {
        next = i->next;
        free(i);
        i = next;
    }

    free(*plist);
	*plist = NULL;
}
```

### Activity 5: Prepending


```c
void list_prepend(list * plist, int value) {
    if (plist->head == NULL) {
        node_init(&plist->head, value);
        plist->tail = plist->head;
    } else {
        node * n;
        node_init(&n, value);
        n->next = plist->head;
        plist->head = n;
    }
}
```

### Activity 6: Time complexity of prepend and append

The time complexity of appending a new element is `O(1)` because only a new node is created and the `next` attribute of the previous node is changed to point to the current one.

The time complexity of appending if we would not keep track of the tail in the list structure would be `O(n)`. The reason for it is that we need to traverse through the whole list to find the last node.

### Activity 7: Access by index

```c
// returns the node at index 'index' in the list referred to by pList
const node *list_at(const list *plist, int index) {
    int current_index = 0;
    for (node *i = plist->head; i != NULL; i = i->next) {
        if (index == current_index) {
            return i;
        }
        current_index++;
    }
    return NULL;
}
```

**Test 1 - Empty list**
```c
list * l;
list_init(&l);
printf("%d", list_at(l, 0) == NULL);
```
Output: 1
<hr>

**Test 2 - Legit index**
```c
list * l;
list_init(&l);

list_append(l, 11);
list_append(l, 22);
list_append(l, 33);

printf("%d ", list_at(l, 0)->value);
printf("%d ", list_at(l, 1)->value);
printf("%d ", list_at(l, 2)->value);
```
Ouput: 11 22 33
<hr>

**Test 3 - Index out of the range**
```c
list * l;
list_init(&l);

list_append(l, 11);
list_append(l, 22);
list_append(l, 33);

printf("%d", list_at(l, 4) == NULL);
```
Output: 1

### Activity 8: Time complexity of accessing by index

The time complexity of the `look_at` function is `O(n)`. The reason for is that we need to traverse through the whole list to find the node at the required index.

### Activity 9: A bad for-loop

Time complexity of this loop `O(n^2)` which is not efficient at all. 

### Activity 10: Removal in a singly-linked list

```c
void list_remove_last(list * plist) {
    for (node * i = plist->head; i->next != NULL; i = i->next) {
        plist->tail = i;
    }

    free(plist->tail->next);
    plist->tail->next = NULL;
}
```

### Activity 11: Code update - I

```c
void list_append(list * plist, int value) {
    if (plist->head == NULL) {
        node_init(&plist->head, value);
        plist->tail = plist->head;
    } else {
        node_init(&plist->tail->next, value);
        if (plist->tail->next != NULL) {
            plist->tail->next->prev = plist->tail;
            plist->tail = plist->tail->next;
        }
    }
}
```

### Activity 12: Code update - II
```c
void list_prepend(list * plist, int value) {
    if (plist->head == NULL) {
        node_init(&plist->head, value);
        plist->tail = plist->head;
    } else {
        node * n;
        node_init(&n, value);
        n->next = plist->head;
        plist->head = n;
        n->next->prev = plist->head;
    }
}
```
### Activity 13: Implementation of removal


```c
void list_remove(list *plist, node *pnode) {
    if (pnode == plist->head) {
        pnode->next->prev = NULL;
        plist->head = pnode->next;
    } else if (pnode == plist->tail) {
        pnode->prev->next = NULL;
        plist->tail = pnode->prev;
    } else {
        pnode->prev->next = pnode->next;
        pnode->next->prev = pnode->prev;
        pnode->next = pnode->prev = NULL;
    }
    free(pnode);
}
```

### Activity 14: Implementing insertion

```c
void list_insert(list *plist, node *pbefore, node *pnode) {
    if (pbefore == plist->head) {
        pbefore->prev = pnode;
        pnode->next = pbefore;
        plist->head = pnode;
    } else {
        pnode->next = pbefore;
        pnode->prev = pbefore->prev;
        pnode->prev->next = pnode;
        pbefore->prev = pnode;
    }
}
```

### Activity 15: Time complexities


| Operation | Array | Linked List |
| --------- |:-----:|:-----------:|
| Access    | O(1)  |    O(n)     |
| Append    | O(1)  |  O(1)       |
| Insert    |  O(n) |  O(1)       |
| Remove    |O(n)   |  O(1)       |


## Looking back

### What we've learnt

We have learnt how to implement linked lists. We have compared the time complexity of the operations on a linked list and on an array. Besides, we have improved the standart linked list to doubly linked list.

### What were the surprises

The behaviour of the "->" operator.

### What problems we've encountered

Understand the behaviour of the "->" operator.

### What was or still is unclear

... pointers

### How did the group perform?

According to the situation, pretty good






> Written with [StackEdit](https://stackedit.io/).
