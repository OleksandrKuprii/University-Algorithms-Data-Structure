# Week 8 - Hashing

## Team

Team name: Oleksandr
Date:

Members
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              |Oleksandr      |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. |  Oleksandr    |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   |  Oleksandr    |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion.

### Activity 1: The costs of maintaining order

The number of **record_pair_t** moved when inserting every item:
8609 - 0 
6348 - 1
4992 - 2
5839 - 2
1622 - 4
5450 - 3
7198 - 1
4827 - 6

**Total: 19**

### Activity 2: Calculate the moduli

| id         | 8609 | 6348 | 4992 | 5839 | 1622 | 5450 | 7198 | 4827 |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| **mod 8**  | 1    | 4     |  0    |  7    | 6     | 2     | 6     | 3     |
| **mod 16** | 1    | 12     | 0     | 16     |6|10|14|11|
| **mod 17** | 7    |7|11|8|7|10|7|16|

Indices produced by the modulus 16 can be used as they are unique for every id.


### Activity 3: Hash functions
A hash function is any function that can be used to map data of arbitrary size to fixed-size values.
A good hash function satisfies two basic properties: 1) it should be very fast to compute; 2) it should minimize duplication of output values (collisions). A good hash function should map the expected inputs as evenly as possible over its output range.

### Activity 4: A simple hash function

**simple_hash** is not a good function because it provides too much duplications of hashes.

### Activity 5: Implement FNV-1a

```c
size_t fnv_hash(const char* key) {
    const size_t FNV_PRIME = 0x00000100000001B3;
    const size_t FNV_OFFSET_BASIS = 0xcbf29ce484222325;

    size_t h = FNV_OFFSET_BASIS;

    for (unsigned long i = 0; i < strlen(key); i++) {
        h ^= key[i];
        h *= FNV_PRIME;
    }

    return h;
}

int main(void) {
	assert(fnv_hash("") == 0xcbf29ce484222325);
	assert(fnv_hash("a") == 0xAF63DC4C8601EC8C);
	assert(fnv_hash("ab") == 0x89C4407B545986A);
	assert(fnv_hash("abc") == 0xE71FA2190541574B);
}
```

### Activity 6: Implement hash-based indexing

```c
// returns the modulo index of a string key based on its FNV-1a hash
size_t hash_index_str(const char* key, size_t size) {
    size_t h = fnv_hash(key);
    return h % size;
}

int main(void) {
	assert(hash_index_str("", 4201) == 2552);
	assert(hash_index_str("a", 4201) == 3432);
	assert(hash_index_str("ab", 4201) == 618);
	assert(hash_index_str("abc", 4201) == 1350);
}
```
| key        | index |
| ---------- | ----- |
| Alice      | 1     |
| in         | 9     |
| Wonderland | 22    |
| potion     | 20    |
| tea        | 6     |
| rabbit     | 24    |



### Activity 7: Function pointers

```c
typedef void (*myfunc)(int);

void foo(int value) {
	printf("The answer is %d\n", value);
}

void bar(myfunc f) {
	f(42);
}

int main(void) {
	myfunc fun = foo;
	bar(fun);
}
```

Variable `fun` represents another function, function `foo` in our case. Then it is passed as an argument to the function `bar`. It calls this argument function (`foo`).

### Activity 8: Hashing and equality testing
```c
bool compare(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

int main(void) {
	hashmap_t map;
	map_init(&map, 7, compare, hash_index_str);
	assert(map.eq_fun("Alice", "Alice"));
	assert(!map.eq_fun("Alice", "alice"));
	assert(map.hash_fun("Alice", 31) == 1);
	assert(map.hash_fun("alice", 31) == 28);
}
```

### Activity 9: Implement lookup

```c
size_t simple_hash(const char* key, size_t size) {
	return strlen(key) % size;
}

int main(void) {
	hashmap_t map;
	map_init(&map, 7, compare, simple_hash);
	list_prepend(&map.slots[5], make_pair("Alice", 42));
	list_prepend(&map.slots[3], make_pair("Bob", 84));
	list_prepend(&map.slots[5], make_pair("Bob Dobalina", 126));
	list_prepend(&map.slots[5], make_pair("Cindy", 6));
	kv_pair_t * p1 = map_lookup(&map, "Joe");
	kv_pair_t * p2 = map_lookup(&map, "Alice");
	kv_pair_t * p3 = map_lookup(&map, "Bob");
	kv_pair_t * p4 = map_lookup(&map, "Bob Dobalina");
	kv_pair_t * p5 = map_lookup(&map, "Cindy");
	assert(p1 == NULL);
	assert(p2 != NULL && p3 != NUlL && p4 != NULL && p5 != NULL);
	assert(strcmp(p2->key, "Alice") == 0);
	assert(p2->value == 42);
	assert(strcmp(p3->key, "Bob") == 0);
	assert(p3->value == 84);
	assert(strcmp(p4->key, "Bob Dobalina") == 0);
	assert(p4->value == 126);
	assert(strcmp(p5->key, "Cindy") == 0);
	assert(p5->value == 6);
}
```


### Activity 10: Implementation time

```c
size_t simple_hash(const char* key, size_t size) {
	return strlen(key) % size;
}

int main(void) {
	map_init(&map, 7, compare, simple_hash);
	map_insert(&map, "Alice", 24);
	assert(map.count == 1);
	map_insert(&map, "Alice", 42);
	assert(map.count == 1);
	map_insert(&map, "Bob", 84);
	map_insert(&map, "Bob Dobalina", 126);
	map_insert(&map, "Cindy", 6);
	assert(map.count == 4);
	kv_pair_t * p2 = map_lookup(&map, "Alice");
	kv_pair_t * p3 = map_lookup(&map, "Bob");
	kv_pair_t * p4 = map_lookup(&map, "Bob Dobalina");
	kv_pair_t * p5 = map_lookup(&map, "Cindy");
	assert(p2 != NULL && p3 != NUlL && p4 != NULL && p5 != NULL);
	assert(strcmp(p2->key, "Alice") == 0);
	assert(p2->value == 42);
	assert(strcmp(p3->key, "Bob") == 0);
	assert(p3->value == 84);
	assert(strcmp(p4->key, "Bob Dobalina") == 0);
	assert(p4->value == 126);
	assert(strcmp(p5->key, "Cindy") == 0);
	assert(p5->value == 6);
}
```

### Activity 11: Word counting

```c
int main(void) {
	hashmap_t map;
	map_init(&map, 31, compare, hash_index_str);
	process_file("short.txt", &map);
	map_print(&map);
	map_destroy(&map);
}
```

| word    | frequency |
| ------- | --------- |
| "ipsum" |           |
| "dolor" |           |
| "sit"   |           |
| "amet"  |           |

### Activity 12: Tracking load statistics

| Capacity                     | 4201 | 6101 | 15149 |
| ---------------------------- | ---- | ---- | ----- |
| Fraction of free slots       | 0.44 |      |       |
| Load factor                  | 0.83 |      |       |
| Slots with more than 1 items |      |      |       |
| Length of longest chain      |      |      |       |
| Keys in longest chain        |      |      |       |

Capacity smaller than 200000 for which no slot has more than one word stored after processing "alice0.txt":

### Activity 13: Time complexity

| Operation | Time complexity |
| --------- | --------------- |
| Lookup    | O(...)          |
| Insert    | O(...)          |
| Remove    | O(...)          |

### Activity 14: Implement rehashing (optional)

```c
bool map_rehash(hashmap_t *original) {
    // if no need to rehash, then do nothing
    if (original->count * 10 < original->capacity * 7) return false;

    // set new capacity so that load factor will become 0.5
    size_t new_capacity = original->count * 2;

    // initialize new dynamic array for storing new slots
    list_t * new_slots = malloc(sizeof(list_t) * new_capacity);
    if (new_slots == NULL) return false;

    // TODO: Activity 14 - implement rehashing


    // Deallocate now-empty array of slots
    free(original->slots);

    // Update hashmap to use new slots and new capacity
    original->slots = new_slots;
    original->capacity = new_capacity;

    return true;
}
```

## Looking back

### What we've learnt

Formulate at least one lesson learned.

### What were the surprises

Fill in...

### What problems we've encountered

Fill in...

### What was or still is unclear

Fill in...

### How did the group perform?

How was the collaboration? What were the reasons for hick-ups? What worked well? What can be improved next time?





> Written with [StackEdit](https://stackedit.io/).
