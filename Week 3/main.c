#include <printf.h>
#include <stdlib.h>

typedef struct node_t {
    int value;
    struct node_t * next;
} node;


typedef struct {
    node * head;
    node * tail;
} list;

void list_init(list ** plist) {
    list * ptr = malloc(sizeof(list));

    if (ptr != NULL) {
        ptr->head = ptr->tail = NULL;
    }

    *plist = ptr;
}

void node_init(node ** ptr, int value) {
    node *p = (node*) malloc(sizeof(node));
    if (p != NULL) {
        p->next = NULL;
        p->value = value;
    }
    *ptr = p;
}

void list_free(list ** plist) {
    free(*plist);
    *plist = NULL;

    node * next;
    for (node * i = (*plist)->head; i != NULL; ) {
        next = i->next;
        free(i);
        i = next;
    }
}

void list_append(list * plist, int value) {
    if (plist->head == NULL) {
        node_init(&plist->head, value);
        plist->tail = plist->head;
    } else {
        node_init(&plist->tail->next, value);
        if (plist->tail->next != NULL) {
            plist->tail = plist->tail->next;
        }
    }
}

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

int main(void) {
    list * l;
    list_init(&l);

    list_append(l, 11);
    list_append(l, 22);
    list_append(l, 33);

    printf("%d", list_at(l, 4) == NULL);
//    for (node * i = l->head; i != NULL; i = i->next) {
//        printf("%d ", i->value);
//    }
}